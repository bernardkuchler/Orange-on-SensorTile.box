/**
 ******************************************************************************
 * @file    iks01a3_conf.h
 * @author  MEMS Application Team
 * @brief   This file contains definitions for the MEMS components bus interfaces
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#ifdef USE_STM32F4XX_NUCLEO
#include "stm32f4xx_hal.h"
#include "nucleo_f401re_bus.h"
#include "nucleo_f401re_errno.h"
#endif

#ifdef USE_STM32L4XX_NUCLEO
#include "stm32l4xx_hal.h"
#include "nucleo_l476rg_bus.h"
#include "nucleo_l476rg_errno.h"
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IKS01A3_CONF_H__
#define __IKS01A3_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define USE_IKS01A3_ENV_SENSOR_HTS221_0                1U
#define USE_IKS01A3_ENV_SENSOR_LPS22HH_0               1U
#define USE_IKS01A3_ENV_SENSOR_STTS751_0               1U

#ifdef USE_LSM6DSO16IS
#define USE_IKS01A3_MOTION_SENSOR_LSM6DSO16IS_0        1U
#define USE_IKS01A3_MOTION_SENSOR_LSM6DSO_0            0U
#define SELECTED_6AXIS_SENSOR IKS01A3_LSM6DSO16IS_0
#else
#define USE_IKS01A3_MOTION_SENSOR_LSM6DSO16IS_0        0U  
#define USE_IKS01A3_MOTION_SENSOR_LSM6DSO_0            1U
#define SELECTED_6AXIS_SENSOR IKS01A3_LSM6DSO_0
#endif

#define USE_IKS01A3_MOTION_SENSOR_LIS2DW12_0           1U
#define USE_IKS01A3_MOTION_SENSOR_LIS2MDL_0            1U

#define USE_IKS01A3_MOTION_SENSOR_LSM6DSR_0            0U
#define USE_IKS01A3_MOTION_SENSOR_ISM330DLC_0          0U

#define IKS01A3_I2C_Init BSP_I2C1_Init
#define IKS01A3_I2C_DeInit BSP_I2C1_DeInit
#define IKS01A3_I2C_ReadReg BSP_I2C1_ReadReg
#define IKS01A3_I2C_WriteReg BSP_I2C1_WriteReg
#define IKS01A3_GetTick BSP_GetTick

#ifdef __cplusplus
}
#endif

#endif /* __IKS01A3_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

