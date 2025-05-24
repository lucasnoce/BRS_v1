/**
 **************************************************************************************************
 * @file           : <leds.h>
 * @brief          : <brief>
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
 * - Toolchain: STM32CubeMX / VS Code + STM32 VS Code Extension + CMake
 **************************************************************************************************
 */


#ifndef __LEDS_H__
#define __LEDS_H__

/* Includes ==================================================================================== */

#include <stdbool.h>
#include "stm32f4xx_hal.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */

/*!
  @brief        Enumerates all the available LEDs.
*/
typedef enum{
	LEDS_LED_0 = 0,
	LEDS_LED_1,
	LEDS_LED_2,
	LEDS_LED_3,
	LEDS_LED_4,
	LEDS_LED_5,
	LEDS_LED_6,
	LEDS_LED_7,
	LEDS_ALL_LEDS,
} LEDS_LED_E;

/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */



/* Global Functions ============================================================================ */

int8_t leds_init( TIM_HandleTypeDef *htim );
int8_t leds_on( uint8_t led );
int8_t leds_off( uint8_t led );
int8_t leds_toggle( uint8_t led );
int8_t leds_blink( uint8_t led, bool fast );

#endif /* __LEDS_H__ */
