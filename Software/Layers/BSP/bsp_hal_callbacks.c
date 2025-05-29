/**
 **************************************************************************************************
 * @file           : bsp_hal_callbacks.c
 * @brief          : <Short description of the file>
 **************************************************************************************************
 * @author         : Lucas Noce
 * @date           : 2025/05/29
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

#include "bsp_hal_callbacks.h"
#include "stm32f4xx_hal.h"

#include <stdint.h>
#include <stdbool.h>

#include "../Utilities/brs_errno.h"
#include "../Modules/leds/leds.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */



/* Local Function Prototypes =================================================================== */



/* Global Functions Implementation ============================================================= */

void HAL_TIM_OC_DelayElapsedCallback( TIM_HandleTypeDef *htim ){
	uint8_t led = 0;

//	if( htim->Instance == TIM1 ){
//		return;
//	}
	if( htim->Instance == TIM2 ){  // LEDs
		switch( htim->Channel ){
			case HAL_TIM_ACTIVE_CHANNEL_1:
				led = LEDS_TIM_CHANNEL_1_LED_0;
				break;

			case HAL_TIM_ACTIVE_CHANNEL_2:
				led = LEDS_TIM_CHANNEL_2_LED_1;
				break;

			case HAL_TIM_ACTIVE_CHANNEL_3:
				led = LEDS_TIM_CHANNEL_3_LED_2;
				break;

			case HAL_TIM_ACTIVE_CHANNEL_4:
				led = LEDS_TIM_CHANNEL_4_LED_3;
				break;

			default:
				led = LEDS_TIM_CHANNEL_ALL;
				break;
		}

		leds_tim_callback_handler( led );
	}

    return;
}

/* Local Functions Implementation ============================================================== */


