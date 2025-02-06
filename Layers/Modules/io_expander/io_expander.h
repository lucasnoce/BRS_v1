/**
 **************************************************************************************************
 * @file           : io_expander.h
 * @brief          : IO Expander driver header
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


#include <stdint.h>

#include "tca9534a_reg_map.h"

#ifndef __MODULE_IO_EXPANDER_H__
#define __MODULE_IO_EXPANDER_H__

/* Definitions ================================================================================= */

#define IO_EXPANDER_I2C_ADDR                    TCA9534A_I2C_ADDR


#define IO_EXPANDER_CMD_REG_INPUT_PORT          TCA9534A_CMD_REG_INPUT_PORT
#define IO_EXPANDER_CMD_REG_OUTPUT_PORT         TCA9534A_CMD_REG_OUTPUT_PORT
#define IO_EXPANDER_CMD_REG_POLARITY            TCA9534A_CMD_REG_POLARITY
#define IO_EXPANDER_CMD_REG_DIRECTION           TCA9534A_CMD_REG_CONFIG


#define IO_EXPANDER_REG_VAL_INPUT_LOW           TCA9534A_REG_VAL_INPUT_LOW
#define IO_EXPANDER_REG_VAL_INPUT_HIGH          TCA9534A_REG_VAL_INPUT_HIGH

#define IO_EXPANDER_REG_VAL_OUTPUT_LOW          TCA9534A_REG_VAL_OUTPUT_LOW
#define IO_EXPANDER_REG_VAL_OUTPUT_HIGH         TCA9534A_REG_VAL_OUTPUT_HIGH

#define IO_EXPANDER_REG_VAL_POLARITY_NORMAL     TCA9534A_REG_VAL_POLARITY_NORMAL
#define IO_EXPANDER_REG_VAL_POLARITY_INVERTED   TCA9534A_REG_VAL_POLARITY_INVERTED

#define IO_EXPANDER_REG_VAL_DIRECTION_OUTPUT    TCA9534A_REG_VAL_CONFIG_OUTPUT
#define IO_EXPANDER_REG_VAL_DIRECTION_INPUT     TCA9534A_REG_VAL_CONFIG_INPUT


#define IO_EXPANDER_REG_VAL_INPUT_PORT_DEFAULT  TCA9534A_REG_VAL_INPUT_PORT_DEFAULT
#define IO_EXPANDER_REG_VAL_OUTPUT_PORT_DEFAULT TCA9534A_REG_VAL_OUTPUT_PORT_DEFAULT
#define IO_EXPANDER_REG_VAL_POLARITY_DEFAULT    TCA9534A_REG_VAL_POLARITY_DEFAULT
#define IO_EXPANDER_REG_VAL_DIRECTION_DEFAULT   TCA9534A_REG_VAL_CONFIG_DEFAULT

/* Enums ======================================================================================= */

/*!
  @brief        Enumerates all the available IO Expander GPIOs.
*/
typedef enum{
  IO_EXPANDER_GPIO_0 = 0,
  IO_EXPANDER_GPIO_1,
  IO_EXPANDER_GPIO_2,
  IO_EXPANDER_GPIO_3,
  IO_EXPANDER_GPIO_4,
  IO_EXPANDER_GPIO_5,
  IO_EXPANDER_GPIO_6,
  IO_EXPANDER_GPIO_7,
  IO_EXPANDER_ALL_GPIOS,
} IO_EXPANDER_GPIO_E;

/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */



/* Global Functions ============================================================================ */

/*!
  @brief        Initializes the IO Expander driver.

  @details      Initializes all the GPIOs as inputs.

  @param[in]    hi2c: pointer to the STM32 I2C bus handle to be used.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).
*/
int8_t io_expander_init( I2C_HandleTypeDef *hi2c );

/*!
  @brief        Configures the IO Expander GPIOs.

  @param[in]    gpio: the IO to be configured, use `IO_EXPANDER_GPIO_E`.
  @param[in]    direction: the direction (input/output) to configure the GPIO.
  @param[in]    polarity: the polarity (normal/inverted) to configure the GPIO.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         `IO_EXPANDER_REG_VAL_DIRECTION_[]` macros are provided to facilitate use.
  @note         `IO_EXPANDER_REG_VAL_POLARITY_[]` macros are provided to facilitate use.
  @note         If `gpio` is equal to IO_EXPANDER_ALL_GPIOS, each bit of the `direction` and
                `polarity` parameters is related to the corresponding GPIO, i.e. interpreted as
                a hex value. Otherwise, only the LSB is considered, i.e. interpreted as 1 or 0.
*/
int8_t io_expander_config( uint8_t gpio, uint8_t direction, uint8_t polarity );

// As of BRS_v1, IO Expander will only be used as output, so this method is currently unnecessary
// int8_t io_expander_read( uint8_t gpio, uint8_t *value );

/*!
  @brief        Writes a value to an IO Expander GPIO.

  @param[in]    gpio: the IO to be configured, use `IO_EXPANDER_GPIO_E`.
  @param[in]    value: the value (high/low) to be written.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         `IO_EXPANDER_REG_VAL_OUTPUT_[]` macros are provided to facilitate use.
  @note         If `gpio` is equal to IO_EXPANDER_ALL_GPIOS, each bit of the `gpio` parameter is
                related to the corresponding GPIO, i.e. interpreted as a hex value. Otherwise, only
                the LSB is considered, i.e. interpreted as 1 or 0.
*/
int8_t io_expander_write( uint8_t gpio, uint8_t value );

#endif /* __MODULE_IO_EXPANDER_H__ */