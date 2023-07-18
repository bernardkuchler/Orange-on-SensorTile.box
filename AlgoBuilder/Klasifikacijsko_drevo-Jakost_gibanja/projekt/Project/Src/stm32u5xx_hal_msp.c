/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_Timers/Src/stm32u5xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   This file provides code for the MSP Initialization
  *                      and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions ------------------------------------------------------- */

int use_LSI = 0;

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  __HAL_RCC_PWR_CLK_ENABLE();
  
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* System interrupt init*/

  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  */
  HAL_PWREx_DisableUCPDDeadBattery();
}

/**
* @brief PCD MSP Initialization
* This function configures the hardware resources used in this example
* @param hpcd: PCD handle pointer
* @retval None
*/
void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hpcd->Instance==USB_OTG_FS)
  {
  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
    PeriphClkInit.Clk48ClockSelection = RCC_CLK48CLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USB_OTG_FS GPIO Configuration
    PA12     ------> USB_OTG_FS_DP
    PA11     ------> USB_OTG_FS_DM
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_USB;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_USB_CLK_ENABLE();

    /* Enable VDDUSB */
    if(__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      HAL_PWREx_EnableVddUSB();
      __HAL_RCC_PWR_CLK_DISABLE();
    }
    else
    {
      HAL_PWREx_EnableVddUSB();
    }

    /* Set USB FS Interrupt priority */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 0, 0);

    /* Enable USB FS Interrupt */
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
  }
}

/**
* @brief PCD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hpcd: PCD handle pointer
* @retval None
*/
void HAL_PCD_MspDeInit(PCD_HandleTypeDef* hpcd)
{
  if(hpcd->Instance==USB_OTG_FS)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USB_CLK_DISABLE();

    /**USB_OTG_FS GPIO Configuration
    PA12     ------> USB_OTG_FS_DP
    PA11     ------> USB_OTG_FS_DM
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12|GPIO_PIN_11);
  }
}

/**
* @brief RTC MSP Initialization
* This function configures the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hrtc->Instance==RTC)
  {
  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE();
    __HAL_RCC_RTCAPB_CLK_ENABLE();
  }
}

/**
* @brief RTC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
    __HAL_RCC_RTCAPB_CLK_DISABLE();
  }
}

/**
  * @brief CRC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
  if (hcrc->Instance == CRC)
  {
    /* Peripheral clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  }
}

/**
  * @brief CRC MSP DeInitialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock disable
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
  if (hcrc->Instance == CRC)
  {
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  }
}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance == TIM_AB)
  {
    /* Peripheral clock enable */
    TIM_AB_CLK_ENABLE();
    /* System interrupt init */
    HAL_NVIC_SetPriority(TIM_AB_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(TIM_AB_IRQn);
  }
}

/**
  * @brief TIM MSP DeInitialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
   * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance == TIM_AB)
  {
    /* Peripheral clock disable */
    TIM_AB_CLK_DISABLE();
    /* Peripheral interrupt DeInit */
    HAL_NVIC_DisableIRQ(TIM_AB_IRQn);
  }
}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance == TIM_ALGO)
  {
	  /* Peripheral clock enable */
	  TIM_ALGO_CLK_ENABLE();
	  /* System interrupt init */
	  HAL_NVIC_SetPriority(TIM_ALGO_IRQn, 0x0E, 0);
	  HAL_NVIC_EnableIRQ(TIM_ALGO_IRQn);
  }
}

/**
  * @brief TIM MSP DeInitialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance == TIM_ALGO)
  {
	  /* Peripheral clock disable */
	  TIM_ALGO_CLK_DISABLE();
	  /* Peripheral interrupt DeInit */
	  HAL_NVIC_DisableIRQ(TIM_ALGO_IRQn);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
