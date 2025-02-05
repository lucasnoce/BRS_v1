/**
 **************************************************************************************************
 * @file           : tca9534a_reg_map.h
 * @brief          : Register map of the TCA9534A IO Expander
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


#ifndef __TCA9534A_REG_MAP_H__
#define __TCA9534A_REG_MAP_H__


/* I2C address */
#define TCA9534A_I2C_ADDR_HW_A0   0
#define TCA9534A_I2C_ADDR_HW_A1   0
#define TCA9534A_I2C_ADDR_HW_A2   0
#define TCA9534A_I2C_ADDR         ( 0b0111000 |\
                                  ( ( TCA9534A_I2C_ADDR_HW_A0 << 0 ) & 0x01 ) |\
                                  ( ( TCA9534A_I2C_ADDR_HW_A1 << 1 ) & 0x02 ) |\
                                  ( ( TCA9534A_I2C_ADDR_HW_A2 << 2 ) & 0x04 ) )


/* Command byte */
#define TCA9534A_CMD_REG_INPUT_PORT       0x00
#define TCA9534A_CMD_REG_INPUT_PORT_DEF   0x00  // Initial state unknown, HW dependent

#define TCA9534A_CMD_REG_OUTPUT_PORT      0x01
#define TCA9534A_CMD_REG_OUTPUT_PORT_DEF  0xFF

#define TCA9534A_CMD_REG_POLARITY         0x02
#define TCA9534A_CMD_REG_POLARITY_DEF     0x00

#define TCA9534A_CMD_REG_CONFIG           0x03
#define TCA9534A_CMD_REG_CONFIG_DEF       0xFF


/* Register values description */
#define TCA9534A_REG_VAL_INPUT_LOW          0
#define TCA9534A_REG_VAL_INPUT_HIGH         1

#define TCA9534A_REG_VAL_OUTPUT_LOW         0
#define TCA9534A_REG_VAL_OUTPUT_HIGH        1

#define TCA9534A_REG_VAL_POLARITY_NORMAL    0
#define TCA9534A_REG_VAL_POLARITY_INVERTED  1

#define TCA9534A_REG_VAL_CONFIG_OUTPUT      0
#define TCA9534A_REG_VAL_CONFIG_INPUT       1


#endif /* __TCA9534A_REG_MAP_H__ */