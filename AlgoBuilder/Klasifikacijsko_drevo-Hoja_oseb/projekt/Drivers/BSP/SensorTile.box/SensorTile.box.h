/**
******************************************************************************
* @file    SensorTile.box.h
* @author  SRA - Central Labs
* @version V1.2.0
* @date    01-Sept-2019
* @brief   This file contains definitions for SensorTile.c file
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
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENSORTILE_BOX_H
#define __SENSORTILE_BOX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SensorTile.box_conf.h"
   
/** @addtogroup BSP
  * @{
  */

/** @addtogroup SENSORTILE_BOX
  * @{
  */
      
  /** @addtogroup SENSORTILE_BOX_LOW_LEVEL
  * @{
  */

/** @defgroup SENSORTILE_BOX_LOW_LEVEL_Exported_Types SENSORTILE_BOX_LOW_LEVEL Exported Types
  * @{
  */
typedef enum 
{
  LED1 = 0,
  LED_BLUE  = LED1,
  LED2 = 1,
  LED_GREEN = LED2,
  LED3 = 2,
  LED_RED   = LED3,
}Led_TypeDef;

typedef enum
{
  BUTTON_USER = 0,
  /* Alias */
  BUTTON_KEY  = BUTTON_USER
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum
{
  ADC1_NOT_USED      = 0,
  ADC1_FOR_AUDIO     = 1,
  ADC1_FOR_BC        = 2,
  ADC1_FORCE_RESTART = 4
} ADC_InitUsedDef;

/**
  * @}
  */ 

/** @defgroup SENSORTILE_BOX_LOW_LEVEL_Exported_Constants SENSORTILE_BOX_LOW_LEVEL Exported Constants
  * @{
  */ 


/** @defgroup SENSORTILE_BOX_LED LED
  * @{
  */
#define LEDn                             3

/**
  * @brief Key led
  */
#define LED1_PIN                         GPIO_PIN_15
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()  

#define LED2_PIN                         GPIO_PIN_2
#define LED2_GPIO_PORT                   GPIOF
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()

#define LED3_PIN                         GPIO_PIN_10
#define LED3_GPIO_PORT                   GPIOG
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOG_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOG_CLK_DISABLE()  

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == LED1) LED1_GPIO_CLK_ENABLE(); \
                                            if((__INDEX__) == LED2) LED2_GPIO_CLK_ENABLE(); \
                                            if((__INDEX__) == LED3) {__HAL_RCC_PWR_CLK_ENABLE(); HAL_PWREx_EnableVddIO2(); LED3_GPIO_CLK_ENABLE();} \
                                            }while(0)
												
#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == LED1) LED1_GPIO_CLK_DISABLE(); \
                                            if((__INDEX__) == LED2) LED2_GPIO_CLK_DISABLE(); \
                                            if((__INDEX__) == LED3) LED3_GPIO_CLK_DISABLE(); \
                                            }while(0)
/**
  * @}
  */


/** @defgroup SENSORTILE_BOX_BUTTON BUTTON
  * @{
  */
#define BUTTONn                            1

/**
  * @brief Key User button
  */
#define USER_BUTTON_PIN                         GPIO_PIN_1
#define USER_BUTTON_GPIO_PORT                   GPIOG
#define USER_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOG_CLK_ENABLE()
#define USER_BUTTON_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOG_CLK_DISABLE()
#define USER_BUTTON_EXTI_LINE                   GPIO_PIN_1
#define USER_BUTTON_EXTI_IRQn                   EXTI1_IRQn
/* Aliases */
#define KEY_BUTTON_PIN                          USER_BUTTON_PIN
#define KEY_BUTTON_GPIO_PORT                    USER_BUTTON_GPIO_PORT
#define KEY_BUTTON_GPIO_CLK_ENABLE()            USER_BUTTON_GPIO_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()           USER_BUTTON_GPIO_CLK_DISABLE()
#define KEY_BUTTON_EXTI_LINE                    USER_BUTTON_EXTI_LINE
#define KEY_BUTTON_EXTI_IRQn                    USER_BUTTON_EXTI_IRQn


#define BUTTONx_GPIO_CLK_ENABLE(__BUTTON__)    do { if((__BUTTON__) == BUTTON_USER) { USER_BUTTON_GPIO_CLK_ENABLE(); } } while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__BUTTON__)   do { if((__BUTTON__) == BUTTON_USER) { USER_BUTTON_GPIO_CLK_DISABLE(); } } while(0)
                                              
/**
  * @brief Key POWER button
  */
#define POWER_BUTTON_PIN                         GPIO_PIN_2
#define POWER_BUTTON_GPIO_PORT                   GPIOG
#define POWER_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOG_CLK_ENABLE()
#define POWER_BUTTON_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOG_CLK_DISABLE()
#define POWER_BUTTON_EXTI_LINE                   GPIO_PIN_2
#define POWER_BUTTON_EXTI_IRQn                   EXTI2_IRQn

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup SENSORTILE_BOX_LOW_LEVEL_Exported_Macros SENSORTILE_BOX_LOW_LEVEL Exported Macros
  * @{
  */  
/**
  * @}
  */ 
/** @defgroup SENSORTILE_BOX_LOW_LEVEL_Exported_Functions SENSORTILE_BOX_LOW_LEVEL Exported Functions
  * @{
  */
uint32_t BSP_GetVersion(void);
void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_DeInit(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);
void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void     BSP_PB_DeInit(Button_TypeDef Button);
uint32_t BSP_PB_GetState(Button_TypeDef Button);

void     BSP_PowerButton_Init(void);
void     BSP_PowerButton_DeInit(void);

int32_t BSP_ADC1_Initialization(ADC_InitUsedDef ADC_InitFor);
int32_t BSP_ADC1_DeInitialization(ADC_InitUsedDef ADC_InitFor);

/**
  * @}
  */
    
/** @defgroup SENSORTILE_BOX_LOW_LEVEL_Exported_Variables SENSORTILE_BOX_LOW_LEVEL Exported Variables
  * @{
  */
extern ADC_HandleTypeDef SensorTileADC;
/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __SENSORTILE_BOX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
