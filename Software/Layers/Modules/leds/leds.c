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

#include "../../BSP/bsp_timers.h"
#include "../../Utilities/brs_errno.h"
#include "../io_expander/io_expander.h"

/* Definitions ================================================================================= */

#define LEDS_BLINK_SINGLE_T_TOTAL_MS	(uint16_t) 200
#define LEDS_BLINK_SLOW_T_TOTAL_MS		(uint16_t) 5000
#define LEDS_BLINK_NORMAL_T_TOTAL_MS	(uint16_t) 1000
#define LEDS_BLINK_FAST_T_TOTAL_MS		(uint16_t) 200

#define LEDS_BLINK_SINGLE_T_ON_MS		(uint16_t) 200
#define LEDS_BLINK_SLOW_T_ON_MS			(uint16_t) 200
#define LEDS_BLINK_NORMAL_T_ON_MS		(uint16_t) 200
#define LEDS_BLINK_FAST_T_ON_MS			(uint16_t) 100

/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */

typedef struct LEDS_DATA_TAG{
	uint8_t state;
	uint8_t blink_en;
	uint8_t blink_speed[BSP_TIMER_CHANNEL_COUNT];
} LEDS_DATA_T;

/* Static Variables ============================================================================ */

static bool leds_init_flag = false;
static LEDS_DATA_T leds_data;

static uint16_t leds_blink_period[4][2] = {
	{ LEDS_BLINK_SINGLE_T_TOTAL_MS,	LEDS_BLINK_SINGLE_T_ON_MS },
	{ LEDS_BLINK_SLOW_T_TOTAL_MS,	LEDS_BLINK_SLOW_T_ON_MS   },
	{ LEDS_BLINK_NORMAL_T_TOTAL_MS,	LEDS_BLINK_NORMAL_T_ON_MS },
	{ LEDS_BLINK_FAST_T_TOTAL_MS,	LEDS_BLINK_FAST_T_ON_MS   }
};

/* Local Function Prototypes =================================================================== */

static inline int8_t _leds_stop_tim_oc_it( uint8_t led ){
	int8_t ret = BRS_RET_OK;

	if( led > LEDS_TIM_CHANNEL_ALL ){
		return BRS_RET_OK;
	}
	else if( led == LEDS_TIM_CHANNEL_ALL ){
		for( uint8_t i=0; i<LEDS_TIM_CHANNEL_ALL; i++ ){
			ret += bsp_tim_oc_stop_it( BSP_TIMER_ID_LEDS, i );
		}
	}
	else{
		ret = bsp_tim_oc_stop_it( BSP_TIMER_ID_LEDS, led );
	}

	return ret;
}

static inline int8_t _leds_start_tim_oc_it( uint8_t led ){
	int8_t ret = BRS_RET_OK;

	if( led > LEDS_TIM_CHANNEL_ALL ){
		return BRS_RET_OK;
	}
	else if( led == LEDS_TIM_CHANNEL_ALL ){
		for( uint8_t i=0; i<LEDS_TIM_CHANNEL_ALL; i++ ){
			ret += bsp_tim_oc_start_it( BSP_TIMER_ID_LEDS, i );
		}
	}
	else{
		ret = bsp_tim_oc_start_it( BSP_TIMER_ID_LEDS, led );
	}

	return ret;
}

static inline int8_t _leds_set_initial_tim_period( uint8_t led, uint8_t speed ){
	int8_t ret = BRS_RET_OK;

	switch( speed ){
		case LEDS_BLINK_SPEED_SINGLE:
			ret = bsp_tim_set_it_period( BSP_TIMER_ID_LEDS, led, LEDS_BLINK_SLOW_T_ON_MS );
			break;

		case LEDS_BLINK_SPEED_SLOW:
			ret = bsp_tim_set_it_period( BSP_TIMER_ID_LEDS, led, LEDS_BLINK_SLOW_T_ON_MS );
			break;

		case LEDS_BLINK_SPEED_NORMAL:
			ret = bsp_tim_set_it_period( BSP_TIMER_ID_LEDS, led, LEDS_BLINK_NORMAL_T_ON_MS );
			break;

		case LEDS_BLINK_SPEED_FAST:
			ret = bsp_tim_set_it_period( BSP_TIMER_ID_LEDS, led, LEDS_BLINK_FAST_T_ON_MS );
			break;

		case LEDS_BLINK_SPEED_ALL:
		default:
			ret = BRS_ERR_INVALID_PARAM;
			break;
	}

	return ret;
}

/* Global Functions Implementation ============================================================= */

int8_t leds_init( void ){
	int8_t ret = BRS_RET_OK;

	if( leds_init_flag )
		return BRS_RET_OK;

	leds_data.state = 0;
	leds_data.blink_en = 0;

	for( uint8_t i=0; i<BSP_TIMER_CHANNEL_COUNT; i++ ){
		leds_data.blink_speed[i] = 0;
	}

//	ret = io_expander_config( IO_EXPANDER_ALL_GPIOS,
//			IO_EXPANDER_MOD_ALL( IO_EXPANDER_REG_VAL_DIRECTION_OUTPUT ),
//			IO_EXPANDER_MOD_ALL( IO_EXPANDER_REG_VAL_POLARITY_NORMAL ) );

	if( ret == BRS_RET_OK )
		leds_init_flag = true;

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
		leds_data.blink_en &= ~( 1 << led );
		ret = io_expander_write( led, IO_EXPANDER_REG_VAL_OUTPUT_HIGH );
	}
	else{
		leds_data.state = 0xFF;
		leds_data.blink_en = 0x00;
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
		leds_data.state &= ~( 1 << led );
		leds_data.blink_en &= ~( 1 << led );
		ret = io_expander_write( led, IO_EXPANDER_REG_VAL_OUTPUT_LOW );
		ret += _leds_stop_tim_oc_it( led );
	}
	else{
		leds_data.state = 0x00;
		leds_data.blink_en = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );
		ret += _leds_stop_tim_oc_it( LEDS_TIM_CHANNEL_ALL );
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
		leds_data.blink_en &= ~( 1 << led );
		ret = io_expander_write( led, ( ( leds_data.state >> led ) & 0x01 ) );
	}
	else{
		leds_data.state ^= 0xFF;
		leds_data.blink_en = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );
	}

	return ret;
}

int8_t leds_blink( uint8_t led, uint8_t speed ){
	int8_t ret = BRS_RET_OK;

	if( !leds_init_flag )
		return BRS_ERR_NOT_INIT;

	if( led > LEDS_ALL_LEDS || ( led >= LEDS_LED_4 && led <= LEDS_LED_7 ) ||
		speed >= LEDS_BLINK_SPEED_ALL ){
		return BRS_ERR_INVALID_PARAM;
	}
	else if( led < LEDS_ALL_LEDS ){
		leds_data.state ^= ( 1 << led );
		leds_data.blink_en &= ~( 1 << led );
		leds_data.blink_speed[led] = speed;
		ret = io_expander_write( led, ( ( leds_data.state >> led ) & 0x01 ) );
		ret += _leds_set_initial_tim_period( led, speed );
		ret += _leds_start_tim_oc_it( led );
	}
	else{
		leds_data.state ^= 0xFF;
		leds_data.blink_en = 0x00;
		ret = io_expander_write( IO_EXPANDER_ALL_GPIOS, leds_data.state );

		for( uint8_t i=0; i<BSP_TIMER_CHANNEL_COUNT; i++ ){
			leds_data.blink_speed[i] = speed;
			ret += _leds_set_initial_tim_period( i, speed );
		}

		ret += _leds_start_tim_oc_it( LEDS_TIM_CHANNEL_ALL );
	}

	return ret;
}

void leds_tim_callback_handler( uint8_t led ){
	leds_data.state ^= ( 1 << led );
	io_expander_write( led, ( ( leds_data.state >> led ) & 0x01 ) );

	if( leds_data.blink_speed[led] == LEDS_BLINK_SPEED_SINGLE ){
		bsp_tim_oc_stop_it( BSP_TIMER_ID_LEDS, led );
	}
	else{
		bsp_tim_set_it_period( BSP_TIMER_ID_LEDS, led,
				leds_blink_period[leds_data.blink_speed[led]][( leds_data.state >> led ) & 0x01] );
	}

	return;
}

/* Local Functions Implementation ============================================================== */


