/**
 **************************************************************************************************
 * @file           : brs_errno.h
 * @brief          : Error code macros
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


#ifndef __BRS_ERRNO_H__
#define __BRS_ERRNO_H__


/* Definitions ================================================================================= */

#define BRS_RET_OK              0
#define BRS_ERR_NULL_POINTER   -1
#define BRS_ERR_INVALID_PARAM  -2
#define BRS_ERR_NOT_INIT       -3

#endif /* __BRS_ERRNO_H__ */