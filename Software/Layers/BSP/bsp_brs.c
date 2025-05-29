/**
 **************************************************************************************************
 * @file           : bsp_brs.c
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

#include "bsp_brs.h"

#include <stdint.h>
#include <stdbool.h>

#include "../Utilities/brs_errno.h"

#include "bsp_i2c.h"
#include "bsp_timers.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */

static BSP_BRS_PERIPH_HANDLES_T bsp_brs_ph = { 0 };

static bool bsp_brs_init_flag = false;

/* Local Function Prototypes =================================================================== */



/* Global Functions Implementation ============================================================= */

int8_t bsp_brs_init( BSP_BRS_PERIPH_HANDLES_T *ph ){
	int8_t ret = BRS_RET_OK;

	if( ph == NULL )
		return BRS_ERR_NULL_POINTER;

	if( bsp_brs_init_flag )
		return BRS_RET_OK;

	for( uint8_t j=0; j<BSP_BRS_HANDLE_COUNT_ADC; j++ ){
		bsp_brs_ph.hadc[j] = ph->hadc[j];
	}
	for( uint8_t j=0; j<BSP_BRS_HANDLE_COUNT_I2C; j++ ){
		bsp_brs_ph.hi2c[j] = ph->hi2c[j];
	}
	for( uint8_t j=0; j<BSP_BRS_HANDLE_COUNT_SPI; j++ ){
		bsp_brs_ph.hspi[j] = ph->hspi[j];
	}
	for( uint8_t j=0; j<BSP_BRS_HANDLE_COUNT_TIM; j++ ){
		bsp_brs_ph.htim[j] = ph->htim[j];
	}
	for( uint8_t j=0; j<BSP_BRS_HANDLE_COUNT_UART; j++ ){
		bsp_brs_ph.huart[j] = ph->huart[j];
	}

	/*
	 * @note: same i2c bus is shared between IO Expander and Barometer.
	 */
	bsp_i2c_init( bsp_brs_ph.hi2c[BSP_BRS_HI2C_IO_EXPANDER] );

	/*
	 * @note: same i2c bus is shared between IO Expander and Barometer.
	 */
	bsp_tim_init( bsp_brs_ph.htim );

	bsp_brs_init_flag = true;

	return ret;
}

/* Local Functions Implementation ============================================================== */


