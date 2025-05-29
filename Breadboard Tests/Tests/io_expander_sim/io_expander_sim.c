/**
 **************************************************************************************************
 * @file           : io_expander_sim.c
 * @brief          : IO Expander simulator using another STM32 MCU
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

#include "io_expander_sim.h"

#include <stdint.h>
#include <stdbool.h>

/* Definitions ================================================================================= */

#define IO_EXPANDER_SIM_BUFF_SIZE	4

/* Enums ======================================================================================= */



/* Typedefs ==================================================================================== */



/* Static Variables ============================================================================ */

static I2C_HandleTypeDef *sim_hi2c;

//static uint8_t tx_buff[IO_EXPANDER_SIM_BUFF_SIZE];
static uint8_t rx_buff[IO_EXPANDER_SIM_BUFF_SIZE];
static uint8_t address;
static uint8_t command;
static uint8_t value;

static bool xfer_complete;

/* Local Function Prototypes =================================================================== */



/* Global Functions Implementation ============================================================= */

void io_expander_sim_init( I2C_HandleTypeDef *hi2c1 ){
	if( hi2c1 == NULL )
		return;

	sim_hi2c = hi2c1;
	xfer_complete = false;
	command = 0;
	value = 0;

	for( uint8_t i=0; i<IO_EXPANDER_SIM_BUFF_SIZE; i++ ){
//		tx_buff[i] = 0;
		rx_buff[i] = 0;
	}

	if( HAL_I2C_EnableListen_IT( sim_hi2c ) != HAL_OK ){
		while( 1 ){
			HAL_Delay( 10 );
		}
	}
}

void io_expander_sim_loop( void ){
	if( xfer_complete ){
		xfer_complete = false;
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_1, ( ( value >> 0 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_2, ( ( value >> 1 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_3, ( ( value >> 2 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, ( ( value >> 3 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, ( ( value >> 4 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_6, ( ( value >> 5 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_7, ( ( value >> 6 ) & 0x01 ) );
		HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0, ( ( value >> 7 ) & 0x01 ) );
	}
}

void HAL_I2C_AddrCallback( I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode ){
	if( TransferDirection == I2C_DIRECTION_TRANSMIT ){  // Master wants to write to slave
		HAL_I2C_Slave_Receive_IT( hi2c, rx_buff, IO_EXPANDER_SIM_BUFF_SIZE );
	}
}

void HAL_I2C_ListenCpltCallback( I2C_HandleTypeDef *hi2c ){  // Ready to listen again
	xfer_complete = true;
	HAL_I2C_EnableListen_IT( hi2c );
}

void HAL_I2C_SlaveRxCpltCallback( I2C_HandleTypeDef *hi2c ){
	if( hi2c->Instance == I2C1 ){
		address = rx_buff[0];
		command = rx_buff[1];
		value = rx_buff[2];
	}
}

/* Local Functions Implementation ============================================================== */


