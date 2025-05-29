/**
 **************************************************************************************************
 * @file           : leds.c
 * @brief          : <Short description of the file>
 **************************************************************************************************
 * @author         : Lucas Noce
 * @date           : 2025/mm/dd
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

#include "leds.h"

#include <stdint.h>
#include <stdbool.h>

#include "../../Utilities/brs_errno.h"
#include "../io_expander/io_expander.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */

typedef struct LEDS_DATA_TAG{
	uint8_t state;
	uint8_t blink;
	uint8_t blink_spd;
} LEDS_DATA_T;

/* Static Variables ============================================================================ */

static TIM_HandleTypeDef *leds_htim = NULL;

static bool leds_init_flag = false;
static LEDS_DATA_T leds_data;

/* Local Function Prototypes =================================================================== */



/* Global Functions Implementation ============================================================= */

int8_t leds_init( TIM_HandleTypeDef *htim ){
	int8_t ret = BRS_RET_OK;

	if( htim == NULL )
		return BRS_ERR_NULL_POINTER;

	if( leds_init_flag )
		return BRS_RET_OK;

	leds_htim = htim;
	leds_init_flag = true;

	leds_data.state = 0;
	leds_data.blink = 0;
	leds_data.blink_spd = 0;

	ret = io_expander_config( IO_EXPANDER_ALL_GPIOS,
			IO_EXPANDER_MOD_ALL( IO_EXPANDER_REG_VAL_DIRECTION_OUTPUT ),
			IO_EXPANDER_MOD_ALL( IO_EXPANDER_REG_VAL_POLARITY_NORMAL ) );

	return ret;
}

int8_t leds_on( uint8_t led ){
	int8_t ret = BRS_RET_OK;

	if( !leds_init_flag )
		return BRS_ERR_NOT_INIT;

	if( led > LEDS_ALL_LEDS ){
		return BRS_ERR_INVALID_PARAM;
	}
	else if( led < LEDS_ALL_LEDS ){
		leds_data.state |= ( 1 << led );
		leds_data.blink &= ~( 1 << led );
		ret = io_expander_write( led, IO_EXPANDER_REG_VAL_OUTPUT_HIGH );
	}
	else{
		leds_data.state = 0xFF;
		leds_data.blink = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );
	}

	return ret;
}

int8_t leds_off( uint8_t led ){
	int8_t ret = BRS_RET_OK;

	if( !leds_init_flag )
		return BRS_ERR_NOT_INIT;

	if( led > LEDS_ALL_LEDS ){
		return BRS_ERR_INVALID_PARAM;
	}
	else if( led < LEDS_ALL_LEDS ){
		//HAL_TIM_OC_Stop_IT( p_leds_htim, leds_data[led].channel );  // todo
		leds_data.state &= ~( 1 << led );
		leds_data.blink &= ~( 1 << led );
		ret = io_expander_write( led, IO_EXPANDER_REG_VAL_OUTPUT_LOW );
	}
	else{
		leds_data.state = 0x00;
		leds_data.blink = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );
	}

	return ret;
}

int8_t leds_toggle( uint8_t led ){
	int8_t ret = BRS_RET_OK;

	if( !leds_init_flag )
		return BRS_ERR_NOT_INIT;

	if( led > LEDS_ALL_LEDS ){
		return BRS_ERR_INVALID_PARAM;
	}
	else if( led < LEDS_ALL_LEDS ){
		leds_data.state ^= ( 1 << led );
		leds_data.blink &= ~( 1 << led );
		ret = io_expander_write( led, ( ( leds_data.state >> led ) & 0x01 ) );
	}
	else{
		leds_data.state ^= 0xFF;
		leds_data.blink = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );
	}

	return ret;
}

int8_t leds_blink( uint8_t led, bool fast ){
	int8_t ret = BRS_RET_OK;

	if( !leds_init_flag )
		return BRS_ERR_NOT_INIT;

	if( led > LEDS_ALL_LEDS ){
		return BRS_ERR_INVALID_PARAM;
	}
	else if( led < LEDS_ALL_LEDS ){
		//HAL_TIM_OC_Start_IT( p_leds_htim, leds_data[i].channel );  // todo
		leds_data.state ^= ( 1 << led );
		leds_data.blink &= ~( 1 << led );
		ret = io_expander_write( led, ( ( leds_data.state >> led ) & 0x01 ) );
	}
	else{
		leds_data.state ^= 0xFF;
		leds_data.blink = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );
	}

	return ret;
}

/* Local Functions Implementation ============================================================== */


