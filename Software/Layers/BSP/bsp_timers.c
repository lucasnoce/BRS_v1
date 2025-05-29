/**
 **************************************************************************************************
 * @file           : bsp_timers.c
 * @brief          : Timers board support layer
 **************************************************************************************************
 * @author         : Lucas Noce
 * @date           : 2025/05/28
 * @version        : v1.0
 **************************************************************************************************
 * @copyright
 * MIT License
 *
 * Copyright (c) 2025 Lucas Noce
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **************************************************************************************************
 * @note
 * - STM32 Series: STM32F411xx (Update as needed)
 * - Toolchain: STM32CubeMX / STM32CubeIDE
 **************************************************************************************************
 */


/* Includes ==================================================================================== */

#include "bsp_timers.h"

#include <stdint.h>
#include <stdbool.h>

#include "../Utilities/brs_errno.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */

static TIM_HandleTypeDef *bsp_htim[BSP_TIMER_COUNT] = { 0 };

static bool bsp_tim_init_flag = false;

/* Local Function Prototypes =================================================================== */

/*!
  @brief        Converts `HAL_[]` returns in `BRS_[]` returns.

  @param[in]    r: pointer to the `HAL_[]` return to be evaluated.

  @returns      `BRS_[]` returns (see brs_errno.h).
*/
static inline void _bsp_timer_check_ret_hal( int8_t *r ){
	switch( *r ){
		case HAL_OK:      *r = BRS_RET_OK; break;
		case HAL_ERROR:   *r = BRS_ERR_GENERIC; break;
		case HAL_BUSY:    *r = BRS_ERR_BUSY; break;
		case HAL_TIMEOUT: *r = BRS_ERR_TIMEOUT; break;
		default:          *r = BRS_ERR_GENERIC; break;
	}
	return;
}

/* Global Functions Implementation ============================================================= */

int8_t bsp_tim_init( TIM_HandleTypeDef *htim[BSP_TIMER_COUNT] ){
	int8_t ret = BRS_RET_OK;

	if( bsp_tim_init_flag )
		return BRS_RET_OK;

	for( uint8_t i=0; i<BSP_TIMER_COUNT; i++ ){
		if( htim[i] == NULL )
			return BRS_ERR_NULL_POINTER;

		bsp_htim[i] = htim[i];

		ret = HAL_TIM_Base_Start_IT( bsp_htim[i] );
		if( ret != HAL_OK ){
			_bsp_timer_check_ret_hal( &ret );
			return ret;
		}
		else{
			for( int j=0; j<BSP_TIMER_CHANNEL_COUNT; j++ ){
				ret += HAL_TIM_OC_Stop_IT( bsp_htim[i], j );
				if( ret != HAL_OK ){
					_bsp_timer_check_ret_hal( &ret );
					return ret;
				}
			}
		}
	}

	bsp_tim_init_flag = true;

	return BRS_RET_OK;
}

int8_t bsp_tim_base_start_it( uint8_t timer_id ){
	int8_t ret = BRS_RET_OK;

	if( !bsp_tim_init_flag )
		return BRS_ERR_NOT_INIT;

	if( timer_id >= BSP_TIMER_ID_ALL )
		return BRS_ERR_INVALID_PARAM;

	ret = HAL_TIM_Base_Start_IT( bsp_htim[timer_id] );
	_bsp_timer_check_ret_hal( &ret );

	return ret;
}

int8_t bsp_tim_base_stop_it( uint8_t timer_id ){
	int8_t ret = BRS_RET_OK;

	if( !bsp_tim_init_flag )
		return BRS_ERR_NOT_INIT;

	if( timer_id >= BSP_TIMER_ID_ALL )
		return BRS_ERR_INVALID_PARAM;

	ret = HAL_TIM_Base_Stop_IT( bsp_htim[timer_id] );
	_bsp_timer_check_ret_hal( &ret );

	return ret;
}

int8_t bsp_tim_oc_start_it( uint8_t timer_id, uint8_t channel_num ){
	int8_t ret = BRS_RET_OK;

	if( !bsp_tim_init_flag )
		return BRS_ERR_NOT_INIT;

	if( timer_id >= BSP_TIMER_ID_ALL || channel_num >= BSP_TIMER_CHANNEL_COUNT )
		return BRS_ERR_INVALID_PARAM;

	ret = HAL_TIM_OC_Start_IT( bsp_htim[timer_id], channel_num );
	_bsp_timer_check_ret_hal( &ret );

	return ret;
}

int8_t bsp_tim_oc_stop_it( uint8_t timer_id, uint8_t channel_num ){
	int8_t ret = BRS_RET_OK;

	if( !bsp_tim_init_flag )
		return BRS_ERR_NOT_INIT;

	if( timer_id >= BSP_TIMER_ID_ALL || channel_num >= BSP_TIMER_CHANNEL_COUNT )
		return BRS_ERR_INVALID_PARAM;

	ret = HAL_TIM_OC_Stop_IT( bsp_htim[timer_id], channel_num );
	_bsp_timer_check_ret_hal( &ret );

	return ret;
}

int8_t bsp_tim_get_next_channel_num( uint8_t timer_id, uint8_t *channel_num ){
	int8_t ret = BRS_RET_OK;

	if( !bsp_tim_init_flag )
		return BRS_ERR_NOT_INIT;

	if( timer_id >= BSP_TIMER_ID_ALL )
		return BRS_ERR_INVALID_PARAM;

	for( uint8_t i=0; i<BSP_TIMER_CHANNEL_COUNT; i++ ){
		if( bsp_htim[timer_id]->ChannelState[i] == HAL_TIM_CHANNEL_STATE_READY ){
			*channel_num = i;
			ret = BRS_RET_OK;
			break;
		}
		else
			ret = BRS_ERR_BUSY;
	}

	return ret;
}

int8_t bsp_tim_set_it_period( uint8_t timer_id, uint8_t channel_num, uint32_t period_ms ){
	int8_t ret = BRS_RET_OK;

	uint32_t current_count = 0;
	uint32_t new_count = 0;

	if( !bsp_tim_init_flag )
		return BRS_ERR_NOT_INIT;

	if( timer_id >= BSP_TIMER_ID_ALL || channel_num >= BSP_TIMER_CHANNEL_COUNT || period_ms == 0 )
		return BRS_ERR_INVALID_PARAM;

	current_count = __HAL_TIM_GET_COUNTER( bsp_htim[timer_id] );
	new_count = current_count + period_ms;
	__HAL_TIM_SET_COMPARE( bsp_htim[timer_id], channel_num, new_count );

	return ret;
}

/* Local Functions Implementation ============================================================== */


