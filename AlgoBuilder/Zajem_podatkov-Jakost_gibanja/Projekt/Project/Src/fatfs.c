/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
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

#if (defined (USE_SENSORTILEBOX) || defined (USE_STWIN) || defined (USE_STWINBOX))

#include "fatfs.h"

char SDPath[4];   /* SD logical drive path */
FATFS SDFatFs;    /* File system object for SD logical drive */
uint8_t SD_Card_Present = 0;
volatile uint8_t medium_loaded = 0;

void FATFS_Init(void) 
{
  /*## FatFS: Link the SD driver ###########################*/
  if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
  {
    /* Register the file system object to the FatFs module */
    if (f_mount(&SDFatFs, (TCHAR const*)SDPath, 1) == FR_OK)
    {
      SD_Card_Present = 1;
      medium_loaded = 1;
    }
  }
}

void FATFS_Deinit(void) 
{
  /*## FatFS: Un Link the SD driver ###########################*/
  FATFS_UnLinkDriver(SDPath);
  SD_Card_Present = 0;
  medium_loaded = 0;
}


#elif (defined (USE_NUCLEO) || defined (USE_SENSORTILE))
#else
#error Not supported platform
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
