/**
 **************************************************************************************************
 * @file           : io_expander.c
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


#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal_i2c.h"

#include "Layers/Utilities/brs_errno.h"
#include "io_expander.h"


/* Definitions ================================================================================= */

#define IO_EXPANDER_STD_TIMEOUT 100

/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */

/*!
  @brief        Current state of IO Expander.

  @param        input: input value of each GPIO.
  @param        output: output value of each GPIO.
  @param        polarity: polarity value of each GPIO.
  @param        direction: direction value of each GPIO.
*/
typedef struct IO_EXPANDER_DATA_TAG{
  uint8_t input;
  uint8_t output;
  uint8_t polarity;
  uint8_t direction;
} IO_EXPANDER_DATA_T;

/* Static Variables ============================================================================ */

static I2C_HandleTypeDef *io_expander_hi2c = NULL;

static IO_EXPANDER_DATA_T io_expander_data;

static bool io_expander_driver_init = false;

/* Local Function Prototypes =================================================================== */

/*!
  @brief        Change a specific bit on a data byte.

  @param[out]   p_data: pointer to the variable to be changed.
  @param[in]    val: value to be written on the data variable's bit position.
  @param[in]    bit: the bit position.

  @returns      void.
*/
static inline void _io_expander_set_data_bit( uint8_t *p_data, uint8_t val, uint8_t bit );

/*!
  @brief        Writes a byte to a register through STM32 HAL_I2C.

  @param[in]    reg: the IO Expander register to be written.
  @param[in]    p_data: pointer to the data to be written.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).
*/
static inline int8_t _io_expander_i2c_write( uint8_t reg, uint8_t *p_data );

/* Global Functions Implementation ============================================================= */

int8_t io_expander_init( I2C_HandleTypeDef *hi2c ){
  int8_t ret = BRS_RET_OK;

  if( hi2c == NULL )
    return BRS_ERR_NULL_POINTER;
  
  if( io_expander_driver_init )
    return BRS_RET_OK;

  io_expander_hi2c = hi2c;
  ret = io_expander_config( IO_EXPANDER_ALL_GPIOS,
                            ~( IO_EXPANDER_REG_VAL_DIRECTION_INPUT - 1 ),
                            ~( IO_EXPANDER_REG_VAL_POLARITY_NORMAL - 1 ) );  // ~0 = 0xFF and ~(-1) = 0x00
  
  if( ret == 0 )
    io_expander_driver_init = true;
  
  return ret;
}

int8_t io_expander_config( uint8_t gpio, uint8_t direction, uint8_t polarity ){
  int8_t ret = BRS_RET_OK;

  if( io_expander_hi2c == NULL )
    return BRS_ERR_NULL_POINTER;
  
  if( !io_expander_driver_init )
    return BRS_ERR_NOT_INIT;
  
  if( gpio > IO_EXPANDER_ALL_GPIOS ){
    return BRS_ERR_INVALID_PARAM;
  }
  else if( gpio == IO_EXPANDER_ALL_GPIOS ){
    io_expander_data.direction = direction;
    io_expander_data.polarity  = polarity;
  }
  else{
    _io_expander_set_data_bit( &io_expander_data.direction, ( direction & 0x01 ), gpio );
    _io_expander_set_data_bit( &io_expander_data.polarity, ( polarity & 0x01 ), gpio );
  }

  ret += _io_expander_i2c_write( IO_EXPANDER_CMD_REG_DIRECTION, &io_expander_data.direction );
  ret += _io_expander_i2c_write( IO_EXPANDER_CMD_REG_POLARITY, &io_expander_data.polarity );
  
  return ret;
}

int8_t io_expander_write( uint8_t gpio, uint8_t value ){
  int8_t ret = BRS_RET_OK;

  if( io_expander_hi2c == NULL )
    return BRS_ERR_NULL_POINTER;
  
  if( !io_expander_driver_init )
    return BRS_ERR_NOT_INIT;
  
  if( gpio > IO_EXPANDER_ALL_GPIOS ){
    return BRS_ERR_INVALID_PARAM;
  }
  else if( gpio == IO_EXPANDER_ALL_GPIOS ){
    io_expander_data.output = value;
  }
  else{
    _io_expander_set_data_bit( &io_expander_data.output, ( value & 0x01 ), gpio );
  }
  
  ret = _io_expander_i2c_write( IO_EXPANDER_CMD_REG_DIRECTION, &io_expander_data.output );
  
  return ret;
}

/* Local Functions Implementation ============================================================== */

static inline void _io_expander_set_data_bit( uint8_t *p_data, uint8_t val, uint8_t bit ){
  *p_data = ( *p_data & ~( 1 << bit ) | ( ( val & 0x01 ) << bit ) );
}

static inline int8_t _io_expander_i2c_write( uint8_t reg, uint8_t *p_data ){
  return HAL_I2C_Mem_Write( io_expander_hi2c, IO_EXPANDER_I2C_ADDR,
                            reg, I2C_MEMADD_SIZE_8BIT,
                            p_data, sizeof(uint8_t),
                            IO_EXPANDER_STD_TIMEOUT );
}
