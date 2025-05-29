/**
 **************************************************************************************************
 * @file           : bsp_timers.h
 * @brief          : Timers and channels organization
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
 * - Toolchain: STM32CubeMX / VS Code + STM32 VS Code Extension + CMake
 **************************************************************************************************
 */


#ifndef __BSP_TIMERS_H__
#define __BSP_TIMERS_H__

/* Includes ==================================================================================== */

#include <stdint.h>

#include "stm32f4xx_hal.h"

/* Definitions ================================================================================= */

#define BSP_TIMER_COUNT			2	// equal to BSP_TIMER_ID_ALL
#define BSP_TIMER_CHANNEL_COUNT	4

/* Typedefs ==================================================================================== */

typedef enum{
	BSP_TIMER_ID_GENERAL = 0,
	BSP_TIMER_ID_LEDS,
	BSP_TIMER_ID_ALL,
} BSP_TIMER_ID_E;

/* Global Functions ============================================================================ */

/*!
  @brief        Initializes the BSP Timers.

  @param[in]    htim: array of pointers to TIM handles (TIM_HandleTypeDef).

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         Array must have size BSP_TIMER_COUNT.
*/
int8_t bsp_tim_init( TIM_HandleTypeDef *htim[BSP_TIMER_COUNT] );

/*!
  @brief        Start the Timer Base.

  @param[in]    timer_id: which timer group to use, from `BSP_TIMER_ID_E`.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).
*/
int8_t bsp_tim_base_start_it( uint8_t timer_id );

/*!
  @brief        Stop the Timer Base.

  @param[in]    timer_id: which timer group to use, from `BSP_TIMER_ID_E`.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).
*/
int8_t bsp_tim_base_stop_it( uint8_t timer_id );

/*!
  @brief        Start the Output Compare Interrupts.

  @param[in]    timer_id: which timer group to use, from `BSP_TIMER_ID_E`.
  @param[in]    channel_num: which channel from the timer to use (0 to 3).

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         If used, TIM9 has only 2 channels available.
  @note         If used, TIM10 and TIM11 have only 1 channel available each.
*/
int8_t bsp_tim_oc_start_it( uint8_t timer_id, uint8_t channel_num );

/*!
  @brief        Stop the Output Compare Interrupts.

  @param[in]    timer_id: which timer group to use, from `BSP_TIMER_ID_E`.
  @param[in]    channel_num: which channel from the timer to use (0 to 3).

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         If used, TIM9 has only 2 channels available.
  @note         If used, TIM10 and TIM11 have only 1 channel available each.
*/
int8_t bsp_tim_oc_stop_it( uint8_t timer_id, uint8_t channel_num );

/*!
  @brief        Search for the next unused channel in a Timer group.

  @param[in]    timer_id: which timer group to use, from `BSP_TIMER_ID_E`.
  @param[out]   channel_num: the first available channel (0 to 3).

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         If used, TIM9 has only 2 channels available.
  @note         If used, TIM10 and TIM11 have only 1 channel available each.
*/
int8_t bsp_tim_get_next_channel_num( uint8_t timer_id, uint8_t *channel_num );

/*!
  @brief        Set how much time between two consecutive Timer Interrupts.

  @param[in]    timer_id: which timer group to use, from `BSP_TIMER_ID_E`.
  @param[in]    channel_num: which channel from the timer to use (0 to 3).
  @param[in]    period_ms: period of time between interrupts, in milliseconds.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         `period_ms` must be greater than 0.
*/
int8_t bsp_tim_set_it_period( uint8_t timer_id, uint8_t channel_num, uint32_t period_ms );


#endif /* __BSP_TIMERS_H__ */
