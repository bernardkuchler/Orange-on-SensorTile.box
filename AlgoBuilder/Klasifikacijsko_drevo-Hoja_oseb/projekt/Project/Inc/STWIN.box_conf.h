/**
******************************************************************************
* @file    STWIN.box_conf.h
* @author  SRA
* @version v1.0.0
* @date    15-Apr-2021
* @brief   This file contains definitions for the components bus interfaces
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
* All rights reserved.</center></h2>
*
* This software component is licensed by ST under BSD 3-Clause license,
* the "License"; You may not use this file except in compliance with the 
* License. You may obtain a copy of the License at:
*                        opensource.org/licenses/BSD-3-Clause
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STWIN_BOX_CONF_H__
#define STWIN_BOX_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"
#include "STWIN.box_bus.h"
#include "STWIN.box_errno.h"

/* Select Analog or digital mics */  

#define ONBOARD_ANALOG_MIC          0
#define ONBOARD_DIGITAL_MIC         1


/********* TO BE CHECKED: usare due frequenze diverse per acquisire sia digital che analog mic? ******/  
 
#define MIC_DIGITAL                     0x01
#define MIC_ANALOG                      0x02

#if ONBOARD_DIGITAL_MIC  
#define MIC_TYPE                        MIC_DIGITAL
#elif ONBOARD_ANALOG_MIC
#define MIC_TYPE                        MIC_ANALOG
#endif
  
/* Select the sampling frequencies for the microphones
   If the digital microphone is enabled then the max frequency is 48000Hz,
   otherwise is 192000Hz.  */
#if (MIC_TYPE == MIC_DIGITAL)
  #define AUDIO_IN_SAMPLING_FREQUENCY   48000
#else
  #define AUDIO_IN_SAMPLING_FREQUENCY   192000
#endif

  
#define AUDIO_IN_CHANNELS     (ONBOARD_ANALOG_MIC+ONBOARD_DIGITAL_MIC)

#if (AUDIO_IN_CHANNELS==0)
  #error "Please enable at least one of the microphones"
#endif
 
/* The default value of the N_MS_PER_INTERRUPT directive in the driver is set to 1, 
for backward compatibility: leaving this values as it is allows to avoid any 
modification in the application layer developed with older versions of the driver */  
/*Number of millisecond of audio at each DMA interrupt*/
#define N_MS_PER_INTERRUPT               (1U)

#define AUDIO_VOLUME_INPUT              4U

/********* TO BE CHECKED: perchè instanza 1, la 0 cos'è? ****/

#define BSP_AUDIO_IN_INSTANCE           1U   /* Define the audio peripheral used: 1U = MDF */  
#define BSP_AUDIO_IN_IT_PRIORITY        6U


/* Battery Charger */

/* Define 1 to use already implemented callback; 0 to implement callback
   into an application file */ 
   
#define USE_BC_TIM_IRQ_CALLBACK         0U  
#define USE_BC_GPIO_IRQ_HANDLER         1U  
#define USE_BC_GPIO_IRQ_CALLBACK        1U    
  
#define USE_MOTION_SENSOR_IIS2DLPC_0    0U
#define USE_MOTION_SENSOR_IIS2MDC_0     1U
#define USE_MOTION_SENSOR_IIS3DWB_0     0U
#define USE_MOTION_SENSOR_IIS2ICLX_0    0U

#ifdef USE_ISM330IS
#define USE_MOTION_SENSOR_ISM330IS_0    1U
#define USE_MOTION_SENSOR_ISM330DHCX_0  0U
#define SELECTED_6AXIS_SENSOR ISM330IS_0
#else
#define USE_MOTION_SENSOR_ISM330IS_0    0U  
#define USE_MOTION_SENSOR_ISM330DHCX_0  1U
#define SELECTED_6AXIS_SENSOR ISM330DHCX_0
#endif

#define USE_ENV_SENSOR_HTS221_0         0U
#define USE_ENV_SENSOR_ILPS22QS_0       1U
#define USE_ENV_SENSOR_STTS22H_0        1U

 
/* IIS2DLP */
#define BSP_IIS2DLPC_CS_GPIO_CLK_ENABLE()       __GPIOH_CLK_ENABLE()  
#define BSP_IIS2DLPC_CS_PORT                    GPIOH
#define BSP_IIS2DLPC_CS_PIN                     GPIO_PIN_6
  
#define BSP_IIS2DLPC_INT1_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
#define BSP_IIS2DLPC_INT1_PORT                  GPIOF
#define BSP_IIS2DLPC_INT1_PIN                   GPIO_PIN_1
#define BSP_IIS2DLPC_INT1_EXTI_IRQn             EXTI1_IRQn
#define BSP_IIS2DLPC_INT1_EXTI_IRQ_PP           1
#define BSP_IIS2DLPC_INT1_EXTI_IRQ_SP           0
#define BSP_IIS2DLPC_INT1_EXTI_IRQHandler       EXTI1_IRQHandler

#define BSP_IIS2DLPC_INT2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
#define BSP_IIS2DLPC_INT2_PORT                  GPIOF
#define BSP_IIS2DLPC_INT2_PIN                   GPIO_PIN_2
#define BSP_IIS2DLPC_INT2_EXTI_IRQn             EXTI2_IRQn
#define BSP_IIS2DLPC_INT2_EXTI_IRQ_PP           1
#define BSP_IIS2DLPC_INT2_EXTI_IRQ_SP           0
#define BSP_IIS2DLPC_INT2_EXTI_IRQHandler       EXTI2_IRQHandler  


/* IIS3DWB */
#define BSP_IIS3DWB_CS_GPIO_CLK_ENABLE()        __GPIOF_CLK_ENABLE()
#define BSP_IIS3DWB_CS_PORT                     GPIOF
#define BSP_IIS3DWB_CS_PIN                      GPIO_PIN_12

#define BSP_IIS3DWB_INT1_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define BSP_IIS3DWB_INT1_PORT                   GPIOF
#define BSP_IIS3DWB_INT1_PIN                    GPIO_PIN_15
#define BSP_IIS3DWB_INT1_EXTI_IRQn              EXTI15_IRQn
#define BSP_IIS3DWB_INT1_EXTI_IRQ_PP            1
#define BSP_IIS3DWB_INT1_EXTI_IRQ_SP            0
#define BSP_IIS3DWB_INT1_EXTI_IRQHandler        EXTI15_IRQHandler

  
/* ISM330DHCX */
#define BSP_ISM330DHCX_CS_GPIO_CLK_ENABLE() 	__GPIOH_CLK_ENABLE()
#define BSP_ISM330DHCX_CS_PORT                  GPIOH
#define BSP_ISM330DHCX_CS_PIN                   GPIO_PIN_15

#define BSP_ISM330DHCX_INT1_GPIO_CLK_ENABLE()   __GPIOB_CLK_ENABLE()
#define BSP_ISM330DHCX_INT1_PORT                GPIOB
#define BSP_ISM330DHCX_INT1_PIN                 GPIO_PIN_8  
#define BSP_ISM330DHCX_INT1_EXTI_IRQn           EXTI8_IRQn
#define BSP_ISM330DHCX_INT1_EXTI_IRQ_PP         1
#define BSP_ISM330DHCX_INT1_EXTI_IRQ_SP         0
#define BSP_ISM330DHCX_INT1_EXTI_IRQHandler     EXTI18_IRQHandler
 
#define BSP_ISM330DHCX_INT2_GPIO_CLK_ENABLE()   __GPIOF_CLK_ENABLE()
#define BSP_ISM330DHCX_INT2_PORT                GPIOF
#define BSP_ISM330DHCX_INT2_PIN                 GPIO_PIN_4  
#define BSP_ISM330DHCX_INT2_EXTI_IRQn           EXTI4_IRQn
#define BSP_ISM330DHCX_INT2_EXTI_IRQ_PP         1
#define BSP_ISM330DHCX_INT2_EXTI_IRQ_SP         0
#define BSP_ISM330DHCX_INT2_EXTI_IRQHandler     EXTI14_IRQHandler  
  
  
/* IIS2ICLX */
#define BSP_IIS2ICLX_CS_GPIO_CLK_ENABLE()       __GPIOI_CLK_ENABLE()
#define BSP_IIS2ICLX_CS_PORT                    GPIOI
#define BSP_IIS2ICLX_CS_PIN                     GPIO_PIN_7

#define BSP_IIS2ICLX_INT1_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
#define BSP_IIS2ICLX_INT1_PORT                  GPIOF
#define BSP_IIS2ICLX_INT1_PIN                   GPIO_PIN_3
#define BSP_IIS2ICLX_INT1_EXTI_IRQn             EXTI3_IRQn
#define BSP_IIS2ICLX_INT1_EXTI_IRQ_PP           1
#define BSP_IIS2ICLX_INT1_EXTI_IRQ_SP           0
#define BSP_IIS2ICLX_INT1_EXTI_IRQHandler       EXTI3_IRQHandler

#define BSP_IIS2ICLX_INT2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
#define BSP_IIS2ICLX_INT2_PORT                  GPIOF
#define BSP_IIS2ICLX_INT2_PIN                   GPIO_PIN_11
#define BSP_IIS2ICLX_INT2_EXTI_IRQn             EXTI11_IRQn
#define BSP_IIS2ICLX_INT2_EXTI_IRQ_PP           1
#define BSP_IIS2ICLX_INT2_EXTI_IRQ_SP           0
#define BSP_IIS2ICLX_INT2_EXTI_IRQHandler       EXTI11_IRQHandler

  
/* HTS221 */  
#define BSP_HTS221_INT_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOI_CLK_ENABLE()
#define BSP_HTS221_INT_PORT                     GPIOI
#define BSP_HTS221_INT_PIN                      GPIO_PIN_6
#define BSP_HTS221_INT_EXTI_IRQn                EXTI6_IRQn
#define BSP_HTS221_INT_EXTI_IRQ_PP              1
#define BSP_HTS221_INT_EXTI_IRQ_SP              0
#define BSP_HTS221_INT_EXTI_IRQHandler          EXTI6_IRQHandler


/* ILPS22QS */
#define BSP_ILPS22QS_CS_GPIO_CLK_ENABLE()       __GPIOE_CLK_ENABLE()
#define BSP_ILPS22QS_CS_PORT                    GPIOE
#define BSP_ILPS22QS_CS_PIN                     GPIO_PIN_15
  
#define BSP_ILPS22QS_INT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOG_CLK_ENABLE()
#define BSP_ILPS22QS_INT_PORT                   GPIOG
#define BSP_ILPS22QS_INT_PIN                    GPIO_PIN_12
#define BSP_ILPS22QS_INT_EXTI_IRQn              EXTI12_IRQn
#define BSP_ILPS22QS_INT_EXTI_IRQ_PP            1
#define BSP_ILPS22QS_INT_EXTI_IRQ_SP            0
#define BSP_ILPS22QS_INT_EXTI_IRQHandler        EXTI12_IRQHandler


/* STTS22H */  
#define BSP_STTS22H_INT_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOF_CLK_ENABLE()
#define BSP_STTS22H_INT_PORT                    GPIOF
#define BSP_STTS22H_INT_PIN                     GPIO_PIN_5
#define BSP_STTS22H_INT_EXTI_IRQn               EXTI5_IRQn
#define BSP_STTS22H_INT_EXTI_IRQ_PP             1
#define BSP_STTS22H_INT_EXTI_IRQ_SP             0
#define BSP_STTS22H_INT_EXTI_IRQHandler         EXTI5_IRQHandler
  
/* DIL24 */
#define BSP_DIL24_CS_GPIO_CLK_ENABLE()          __GPIOI_CLK_ENABLE()
#define BSP_DIL24_CS_PORT                       GPIOI
#define BSP_DIL24_CS_PIN                        GPIO_PIN_0
  
#define BSP_DIL24_INT1_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOG_CLK_ENABLE()
#define BSP_DIL24_INT1_PORT                     GPIOG
#define BSP_DIL24_INT1_PIN                      GPIO_PIN_6
#define BSP_DIL24_INT1_EXTI_IRQn                EXTI6_IRQn
#define BSP_DIL24_INT1_EXTI_IRQ_PP              1
#define BSP_DIL24_INT1_EXTI_IRQ_SP              0
#define BSP_DIL24_INT1_EXTI_IRQHandler          EXTI6_IRQHandler
  
#define BSP_DIL24_INT2_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define BSP_DIL24_INT2_PORT                     GPIOG
#define BSP_DIL24_INT2_PIN                      GPIO_PIN_1
#define BSP_DIL24_INT2_EXTI_IRQn                EXTI1_IRQn
#define BSP_DIL24_INT2_EXTI_IRQ_PP              1
#define BSP_DIL24_INT2_EXTI_IRQ_SP              0
#define BSP_DIL24_INT2_EXTI_IRQHandler          EXTI2_IRQHandler

#ifdef __cplusplus
}
#endif

#endif /* STWIN_BOX_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

