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

#include <stdint.h>
#include <stdbool.h>

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */

/*!
  @brief	Enumerates all the available LEDs.

  @note 	A total of 8 LEDs are used together with the IO Expander.
  @note 	The LED number (LEDn) directly corresponds to the IO Expander GPIO number.
  @note 	The State Machine is encoded as 4 bit binary number (e.g. state 5 is 0b0101).
  @note 	The LEDs related to State Machine indication will not have access to blink functions.
*/
typedef enum{
	LEDS_LED_0 = 0,	// DEBUG: For general use
	LEDS_LED_1,		// DEBUG: For general use
	LEDS_LED_2,		// RCV: Used to indicate vehicle Recovery
	LEDS_LED_3,		// LOW_BAT: Used to indicate BRS low battery
	LEDS_LED_4,		// SM0: State Machine state, bit 0
	LEDS_LED_5,		// SM1: State Machine state, bit 1
	LEDS_LED_6,		// SM2: State Machine state, bit 2
	LEDS_LED_7,		// SM3: State Machine state, bit 3
	LEDS_ALL_LEDS,
} LEDS_LED_E;

/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */



/* Global Functions ============================================================================ */

int8_t leds_init( void );
int8_t leds_on( uint8_t led );
int8_t leds_off( uint8_t led );
int8_t leds_toggle( uint8_t led );
int8_t leds_blink( uint8_t led, bool fast );

#endif /* __LEDS_H__ */
