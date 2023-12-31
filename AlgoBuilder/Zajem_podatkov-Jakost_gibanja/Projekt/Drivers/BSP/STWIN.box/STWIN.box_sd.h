/**
******************************************************************************
* @file    STWIN.box_sd.h
* @author  SRA
* @version v1.0.0
* @date    11-Sep-2020
* @brief   This file contains the common defines and functions prototypes for 
*          the STWIN.box_sd.c driver.
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2021 STMicroelectronics. 
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
#ifndef STWIN_BOX_SD_H
#define STWIN_BOX_SD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* SD IRQ handler */
//#define SDMMCx_IRQHandler           SDMMC1_IRQHandler
//#define SDMMCx_IRQn              SDMMC1_IRQn
   
#define SD_DETECT_GPIO_PORT           GPIOG
#define SD_DETECT_GPIO_PIN            GPIO_PIN_1
#define SD_DETECT_GPIO_CLK_ENABLE()   __GPIOG_CLK_ENABLE()

   /** 
  * @brief SD Card information structure 
  */
#define BSP_SD_CardInfo HAL_SD_CardInfoTypeDef

/* Exported constants --------------------------------------------------------*/ 
/**
  * @brief  SD status structure definition  
  */     
#define MSD_OK                        ((uint8_t)0x00)
#define MSD_ERROR                     ((uint8_t)0x01)
#define MSD_ERROR_SD_NOT_PRESENT      ((uint8_t)0x02)

/** 
  * @brief  SD transfer state definition  
  */     
#define SD_TRANSFER_OK                ((uint8_t)0x00)
#define SD_TRANSFER_BUSY              ((uint8_t)0x01)
#define SD_TRANSFER_ERROR             ((uint8_t)0x02)

#define SD_DATATIMEOUT                ((uint32_t)100000000)

#define SD_PRESENT                    ((uint8_t)0x01)
#define SD_NOT_PRESENT                ((uint8_t)0x00)

/* USER CODE BEGIN BSP_H_CODE */
/* Exported functions --------------------------------------------------------*/   
uint8_t BSP_SD_Init(void);
void    BSP_SD_DetectIT(void);
void    BSP_SD_DetectCallback(void);
uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_Erase(uint32_t StartAddr, uint32_t EndAddr);
uint8_t BSP_SD_GetCardState(void);
void    BSP_SD_GetCardInfo(BSP_SD_CardInfo *CardInfo);
uint8_t BSP_SD_IsDetected(void);
void    BSP_SD_MspInit(SD_HandleTypeDef* hsd);
void    BSP_SD_MspDeInit(SD_HandleTypeDef* hsd);
void    BSP_SD_IRQHandler(void);
void    BSP_SD_Detect_Init(void);

/* USER CODE END BSP_H_CODE */

extern SD_HandleTypeDef hsd1;

/* USER CODE BEGIN CallBacksSection_H */
/* These functions can be modified in case the current settings (eg. interrupt priority)
   need to be changed for specific application needs */
void    BSP_SD_AbortCallback(void);
void    BSP_SD_WriteCpltCallback(void);
void    BSP_SD_ReadCpltCallback(void);
/* USER CODE END CallBacksSection_H */   
#ifdef __cplusplus
}
#endif

#endif /* STWIN_BOX_SD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
