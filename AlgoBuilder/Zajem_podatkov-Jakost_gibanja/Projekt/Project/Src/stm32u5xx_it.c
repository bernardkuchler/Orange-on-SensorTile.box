/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_Timers/Src/stm32u5xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "stm32u5xx_it.h"

#if (defined (USE_NUCLEO))
/* No specific include required */
#elif (defined (USE_SENSORTILE))
/* No specific include required */
#elif (defined (USE_SENSORTILEBOX))
#include "SensorTile.box_sd.h"
#include "hci_tl_interface.h"
#elif (defined (USE_STWIN))
#include "STWIN_sd.h"
#include "hci_tl_interface.h"
#elif (defined (USE_STWINBOX))
#include "STWIN.box_sd.h"
#include "hci_tl_interface.h"
#else
#error Not supported platform
#endif

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void TIM_AB_IRQHandler(void);
void TIM_ALGO_IRQHandler(void);

/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M33 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32U5xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32u5xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles TIM_ALGO interrupt request
  * @param  None
  * @retval None
  */
void TIM_ALGO_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&AL_TimHandle);
}

/**
  * @brief This function handles TIM_AB interrupt request
  * @param  None
  * @retval None
  */
void TIM_AB_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&AB_TimHandle);
}

/**
  * @brief This function handles TIMx interrupt request (USB CDC)
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}

/**
  * @brief  This function handles USB-On-The-Go FS global interrupt request.
  * @param  None
  * @retval None
  */
void OTG_FS_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd);
}

/**
  * @brief  This function handles External line 8 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI8_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
}

/**
  * @brief  This function handles External line 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI6_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
}

/**
  * @brief This function handles SMMC1 interrupts.
  * @param  None
  * @retval None
  */
void SDMMC1_IRQHandler(void)
{
  HAL_SD_IRQHandler(&hsd1);
}

/**
  * @brief  This function handles EXTI0_IRQHandler Handler
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(BUTTON_USER_PIN);
}

/**
  * @brief  This function handles EXTI1_IRQHandler Handler
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(HCI_TL_SPI_EXTI_PIN);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
