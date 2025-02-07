/**
 **************************************************************************************************
 * @file           : bsp_i2c.h
 * @brief          : <Short description of the file>
 **************************************************************************************************
 * @author         : Lucas Noce
 * @date           : 2025/02/06
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


#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__

/* Includes ==================================================================================== */

#include "stm32f4xx_hal_i2c.h"

/* Definitions ================================================================================= */



/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */



/* Global Functions ============================================================================ */

int8_t bsp_i2c_init( I2C_HandleTypeDef *hi2c );
int8_t bsp_i2c_write_reg( uint8_t addr, uint8_t reg, uint8_t *p_data );
int8_t bsp_i2c_read_reg( uint8_t addr, uint8_t reg, uint8_t *p_data );

#endif /* __BSP_I2C_H__ */