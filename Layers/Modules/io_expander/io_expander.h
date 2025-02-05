/**
 **************************************************************************************************
 * @file           : io_expander.h
 * @brief          : IO Expander driver
 **************************************************************************************************
 * @author         : Lucas Noce
 * @date           : 2025/02/05
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


#include "tca9534a_reg_map.h"

#ifndef __MODULE_IO_EXPANDER_H__
#define __MODULE_IO_EXPANDER_H__

/* Definitions ================================================================================= */

#define IO_EXPANDER_I2C_ADDR                    TCA9534A_I2C_ADDR

#define IO_EXPANDER_CMD_REG_INPUT_PORT          TCA9534A_CMD_REG_INPUT_PORT
#define IO_EXPANDER_CMD_REG_INPUT_PORT_DEF      TCA9534A_CMD_REG_INPUT_PORT_DEF

#define IO_EXPANDER_CMD_REG_OUTPUT_PORT         TCA9534A_CMD_REG_OUTPUT_PORT
#define IO_EXPANDER_CMD_REG_OUTPUT_PORT_DEF     TCA9534A_CMD_REG_OUTPUT_PORT_DEF

#define IO_EXPANDER_CMD_REG_POLARITY            TCA9534A_CMD_REG_POLARITY
#define IO_EXPANDER_CMD_REG_POLARITY_DEF        TCA9534A_CMD_REG_POLARITY_DEF

#define IO_EXPANDER_CMD_REG_CONFIG              TCA9534A_CMD_REG_CONFIG
#define IO_EXPANDER_CMD_REG_CONFIG_DEF          TCA9534A_CMD_REG_CONFIG_DEF

#define IO_EXPANDER__REG_VAL_INPUT_LOW          TCA9534A_REG_VAL_INPUT_LOW
#define IO_EXPANDER__REG_VAL_INPUT_HIGH         TCA9534A_REG_VAL_INPUT_HIGH
#define IO_EXPANDER__REG_VAL_OUTPUT_LOW         TCA9534A_REG_VAL_OUTPUT_LOW
#define IO_EXPANDER__REG_VAL_OUTPUT_HIGH        TCA9534A_REG_VAL_OUTPUT_HIGH
#define IO_EXPANDER__REG_VAL_POLARITY_NORMAL    TCA9534A_REG_VAL_POLARITY_NORMAL
#define IO_EXPANDER__REG_VAL_POLARITY_INVERTED  TCA9534A_REG_VAL_POLARITY_INVERTED
#define IO_EXPANDER__REG_VAL_CONFIG_OUTPUT      TCA9534A_REG_VAL_CONFIG_OUTPUT
#define IO_EXPANDER__REG_VAL_CONFIG_INPUT       TCA9534A_REG_VAL_CONFIG_INPUT

/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */



/* Local Function Prototypes =================================================================== */



/* Global Functions Implementation ============================================================= */



/* Local Functions Implementation ============================================================== */




#endif /* __MODULE_IO_EXPANDER_H__ */