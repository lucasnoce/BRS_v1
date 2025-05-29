/**
 **************************************************************************************************
 * @file           : bsp_brs.h
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


#ifndef __BSP_BRS_H__
#define __BSP_BRS_H__

/* Includes ==================================================================================== */

#include "stm32f4xx_hal.h"

#include "bsp_i2c.h"
#include "bsp_timers.h"

/* Definitions ================================================================================= */

#define BSP_BRS_PERIPH_COUNT		5	// Total number of peripheral types used

#define BSP_BRS_HANDLE_COUNT_ADC	1
#define BSP_BRS_HANDLE_COUNT_I2C	1
#define BSP_BRS_HANDLE_COUNT_SPI	2
#define BSP_BRS_HANDLE_COUNT_TIM	2
#define BSP_BRS_HANDLE_COUNT_UART	1

/* Enums ======================================================================================= */

/*!
  @brief        Enumerates all the ADC handles used.
*/
typedef enum{
	BSP_BRS_HADC_BATT = 0,
	BSP_BRS_HADC_ALL,
} BSP_BRS_HADC_E;

/*!
  @brief        Enumerates all the I2C handles used.
*/
typedef enum{
	BSP_BRS_HI2C_IO_EXPANDER = 0,
	BSP_BRS_HI2C_BAROMETER = 0,
	BSP_BRS_HI2C_ALL,
} BSP_BRS_HI2C_E;

/*!
  @brief        Enumerates all the SPI handles used.
*/
typedef enum{
	BSP_BRS_HSPI_IMU = 0,
	BSP_BRS_HSPI_EXT_FLASH,
	BSP_BRS_HSPI_ALL,
} BSP_BRS_HSPI_E;

/*!
  @brief        Enumerates all the TIM handles used.
*/
typedef enum BSP_TIMER_ID_E BSP_BRS_HTIM_E;
//typedef enum{
//	BSP_BRS_HTIM_GENERAL = 0,
//	BSP_BRS_HTIM_LEDS,
//	BSP_BRS_HTIM_ALL,
//} BSP_BRS_HTIM_E;

/*!
  @brief        Enumerates all the UART handles used.
*/
typedef enum{
	BSP_BRS_HUART_USB = 0,
	BSP_BRS_HUART_ALL,
} BSP_BRS_HUART_E;

/* Typedefs ==================================================================================== */

typedef struct BSP_BRS_PERIPH_HANDLES_TAG{
	ADC_HandleTypeDef  *hadc[BSP_BRS_HANDLE_COUNT_ADC];
	I2C_HandleTypeDef  *hi2c[BSP_BRS_HANDLE_COUNT_I2C];
	SPI_HandleTypeDef  *hspi[BSP_BRS_HANDLE_COUNT_SPI];
	TIM_HandleTypeDef  *htim[BSP_BRS_HANDLE_COUNT_TIM];
	UART_HandleTypeDef *huart[BSP_BRS_HANDLE_COUNT_UART];
} BSP_BRS_PERIPH_HANDLES_T;

/* Static Variables ============================================================================ */



/* Global Functions ============================================================================ */

/*!
  @brief        Initializes the BSP layer.

  @param[in]    ph: pointer to BSP_BRS_PERIPH_HANDLES_T struct that holds the pointers to all
  	  	  	  	 	peripheral handles used.

  @returns      0 if success, `BRS_ERR_[]` otherwise (see brs_errno.h).

  @note         Array must have size BSP_TIMER_COUNT.
*/
int8_t bsp_brs_init( BSP_BRS_PERIPH_HANDLES_T *ph );

ADC_HandleTypeDef *bsp_brs_get_hadc( uint8_t id );
I2C_HandleTypeDef *bsp_brs_get_hi2c( uint8_t id );
SPI_HandleTypeDef *bsp_brs_get_hspi( uint8_t id );
TIM_HandleTypeDef *bsp_brs_get_htim( uint8_t id );
UART_HandleTypeDef *bsp_brs_get_huart( uint8_t id );

#endif /* __BSP_BRS_H__ */
