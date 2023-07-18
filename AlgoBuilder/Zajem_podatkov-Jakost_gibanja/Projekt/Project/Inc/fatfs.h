/**
  ******************************************************************************
  * @file   fatfs.h
  * @brief  Header for fatfs applications
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __fatfs_H
#define __fatfs_H
#ifdef __cplusplus
 extern "C" {
#endif

#if (defined (USE_SENSORTILEBOX) || defined (USE_STWIN) || defined (USE_STWINBOX))
#include "ff.h"
#include "ff_gen_drv.h"
#if (defined (USE_SENSORTILEBOX))
#include "SensorTile.box_sd.h"
#include "sd_diskio_SensorTile.box.h"
#elif (defined (USE_STWIN))
#include "STWIN_sd.h"
#include "sd_diskio_STWIN.h"
#elif (defined (USE_STWINBOX))
#include "STWIN.box_sd.h"
#include "sd_diskio_STWIN.box.h"
#endif

extern char SDPath[4]; /* SD logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern uint8_t SD_Card_Present;

void FATFS_Init(void);
void FATFS_Deinit(void);

#elif (defined (USE_NUCLEO) || defined (USE_SENSORTILE))
#else
#error Not supported platform
#endif

#ifdef __cplusplus
}
#endif
#endif /*__fatfs_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
