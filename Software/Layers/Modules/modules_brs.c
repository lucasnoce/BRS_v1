/**
 **************************************************************************************************
 * @file           : modules_brs.c
 * @brief          : <Short description of the file>
 **************************************************************************************************
 * @author         : Lucas Noce
 * @date           : 2025/05/2
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

#include "modules_brs.h"

#include <stdint.h>
#include <stdbool.h>

#include "../Utilities/brs_errno.h"

#include "io_expander/io_expander.h"
#include "leds/leds.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */

static bool modules_brs_init_flag = false;

/* Local Function Prototypes =================================================================== */



/* Global Functions Implementation ============================================================= */

int8_t modules_brs_init( void ){
	int8_t ret = BRS_RET_OK;

	if( modules_brs_init_flag )
		return BRS_RET_OK;

	io_expander_init();
	leds_init();

	modules_brs_init_flag = true;

	return ret;
}

/* Local Functions Implementation ============================================================== */


