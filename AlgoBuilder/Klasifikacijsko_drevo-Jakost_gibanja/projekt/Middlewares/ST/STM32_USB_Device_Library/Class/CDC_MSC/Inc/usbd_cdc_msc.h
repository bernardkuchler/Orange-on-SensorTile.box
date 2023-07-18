/**
  ******************************************************************************
  * @file    usbd_cdc.h
  * @author  MCD Application Team
  * @brief   header file for the usbd_cdc.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CDC_MSC_H
#define __USB_CDC_MSC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"
#include "usbd_cdc.h"
#include "usbd_msc.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup usbd_cdc
  * @brief This file is the Header file for usbd_cdc.c
  * @{
  */


/** @defgroup usbd_cdc_Exported_Defines
  * @{
  */
#define MSC_INTERFACE_INDEX          0x00   
#define CDC_INTERFACE_INDEX          0x01   
 

#define USB_CDC_MSC_CONFIG_DESC_SIZ                 98U


/**
  * @}
  */


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */

extern USBD_ClassTypeDef  USBD_CDC_MSC;
#define USBD_CDC_MSC_CLASS    &USBD_CDC_MSC
/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_CDC_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
