/**
 ******************************************************************************
 * @file       ab_display.c
 * @author     MEMS Application Team
 * @brief      AlgoBuilder display function block control 
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

/* Includes ------------------------------------------------------------------*/
#include "ab_display.h"
#include "main.h"
#include "serial_protocol.h"
#include "ab_sensor_hub.h"

#if (defined (USE_NUCLEO))
#include "com.h"
#elif ((defined (USE_SENSORTILE)) || (defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
  #if (defined (USE_BLE_OUTPUT))
#include "ab_ble.h"
  #else
#include "vcom.h"
  #endif
#else
#error Not supported platform
#endif

#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
/* Not supported feature */
#elif  (defined (USE_SENSORTILEBOX))
#include "fatfs.h"
#include "ff_gen_drv.h"
#include "sd_diskio_SensorTile.box.h"
#elif  (defined (USE_STWIN))
#include "fatfs.h"
#include "ff_gen_drv.h"
#include "sd_diskio_STWIN.h"
#elif  (defined (USE_STWINBOX))
#include "fatfs.h"
#include "ff_gen_drv.h"
#include "sd_diskio_STWIN.h"

#else
#error Not supported platform
#endif

/** @addtogroup AlgoBuilder_Firmware
  * @{
  */

/** @addtogroup AlgoBuilder_Display
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern TMsg MsgDat;
extern sensor_hub_data_t sensor_hub_data;

#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
/* Not supported feature */
#elif  ((defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
extern char Identification_String[];
static FIL MyFileMems;                  /* File object for MEMS */
static char file_name[40] = "AB_00001.csv";
static uint8_t datalog_new_data = 0;    /* To indicate if sync is necessary */
static uint8_t datalog_init_ok = 0;     /* To indicate init status of dataloging to SD */
static uint32_t datalog_sync_period = 1000; /* [ms] */
static uint32_t datalog_last_tick = 0;
static char *datalog_header = 0;
static RTC_HandleTypeDef *Rtc_Handle;
extern volatile uint8_t medium_loaded;
static uint8_t file_open = 0;
#else
#error Not supported platform
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief  Display function block update
 */
void Display_Update(void *source, sDISPLAY_INFO *header)
{
  if (header->info_type == INFO_TYPE_FFT)
  {
#if (defined (USE_NUCLEO))
    UART_SendFFT((float*)source, header->variable_count / 2, header->info_index);
#elif ((defined (USE_SENSORTILE)) || (defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
  #if (defined (USE_BLE_OUTPUT))
    BLE_send_FFT((float*)source, header->variable_count / 2, header->info_index);
  #else
    VCOM_send_FFT((float*)source, header->variable_count / 2, header->info_index);
  #endif
#else
#error Not supported platform
#endif
  }
  else
  {
    if (header->variable_type == VAR_TYPE_BIT)
    {
      if (header->variable_count > 8)
      {
        uint16_t tmp = 0;
        uint8_t i;
        for (i = 0; i < header->variable_count; i++)
        {
          if (((uint32_t*)(source))[i] != 0)
          {
            tmp += (1 <<  i);
          }
        }
        SerializeToMsg(STREAM_DATA + header->stream_position, &tmp, 2);
      }
      else
      {
        uint8_t tmp = 0;
        uint8_t i;
        for (i = 0; i < header->variable_count; i++)
        {
          if (((uint32_t*)source)[i] != 0)
          {
            tmp += (1 <<  i);
          }
        }
        SerializeToMsg(STREAM_DATA + header->stream_position, &tmp, 1);
      }
    }
    else
    {
      SerializeToMsg(STREAM_DATA + header->stream_position, source, header->variable_count * 4);
    }
  }
}

void Datalog_Init(char *header, uint32_t sync_period)
{
#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
  /* Not supported feature */
#elif  ((defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
  datalog_init_ok = 0;
  datalog_sync_period = sync_period * 1000; /* to ms */  
  datalog_header = header;
  
  sensor_hub_data.sdcard_enable = 1;
#else
#error Not supported platform
#endif
}

void Datalog_Update(float *data, uint32_t size)
{
#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
  /* Not supported feature */
#elif  ((defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
  if (datalog_init_ok != 0 && medium_loaded == 0)
  {
    uint32_t byteswritten; /* written byte count */
    char str[256];
    char tmp[24];
    str[0] = 0;
    uint32_t i;
    
    sprintf(str, "%lld,", sensor_hub_data.timestamp_us);
    
    for (i = 0; i < size; i++)
    {
      sprintf(tmp, "%f", data[i]);
      strcat(str, tmp);
      strcat(str, ",");
    }

    strcat(str, "\r\n");
    
    if (f_write(&MyFileMems, (const void*)str, strlen(str), (void *)&byteswritten) == FR_OK)
    {
      datalog_new_data = 1;
    }
  }
#else
#error Not supported platform
#endif
}

#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
/* Not supported feature */
#elif  ((defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
void Datalog_Open(void)
{
  FRESULT fr;     /* Return value */
  DIR dj;         /* Directory search object */
  FILINFO fno;    /* File information */
 
  char prefix[32];
  char pattern[40];
  int i;
  for (i=0; i<30; i++)
  {
    char ch = Identification_String[i + 10];
    if (ch == ',' || ch == 0)
    {
      break;
    }
    else
    {
      prefix[i] = ch;
    }
  }
  prefix[i] = 0;
  int len = strlen(prefix);
  char ext[4];
  ext[0] = '.';
  ext[1] = 'x';
  ext[2] = 'm';
  ext[3] = 'l';
 
  if (len > 4)
  {
    if (prefix[len-4] == ext[0] && prefix[len-3] == ext[1] && prefix[len-2] == ext[2] && prefix[len-1] == ext[3])
    {
      prefix[len-4] = 0;
    }
    else if (prefix[len-3] == ext[0] && prefix[len-2] == ext[1] && prefix[len-1] == ext[2])
    {
      prefix[len-3] = 0;
    }
    else if (prefix[len-2] == ext[0] && prefix[len-1] == ext[1])
    {
      prefix[len-2] = 0;
    }
    else if (prefix[len-1] == ext[0])
    {
      prefix[len-1] = 0;
    }
    len = strlen(prefix);
  }
  
  file_open = 0;
  datalog_init_ok = 0;
  if (medium_loaded != 0)
  {
    return;
  }

  sprintf(pattern, "%s_*.csv", prefix);
  fr = f_findfirst(&dj, &fno, "", pattern);
  int32_t max_index = 0;
  int32_t i_tmp = 0;
  char tmp[8];

  while (fr == FR_OK && fno.fname[0])
  {    
    tmp[0] = fno.fname[len + 1];
    tmp[1] = fno.fname[len + 2];
    tmp[2] = fno.fname[len + 3];
    tmp[3] = 0;
    i_tmp = atoi(tmp);

    if (i_tmp > max_index)
    {
      max_index = i_tmp;
    }

    fr = f_findnext(&dj, &fno);
  }

  f_closedir(&dj);

  max_index++;

  if (max_index > 999)
  {
    max_index = 1;
  }

  sprintf(file_name, "%s_%03d.csv", prefix, (int)max_index);

  if (f_open(&MyFileMems, (char const*)file_name, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
  {
    uint32_t byteswritten;
    file_open = 1;

    if (f_write(&MyFileMems, (const void*)datalog_header, strlen(datalog_header), (void *)&byteswritten) == FR_OK)
    {
      f_sync(&MyFileMems);
      datalog_init_ok = 1;
    }
  }
}

void Datalog_Close(void)
{
  datalog_init_ok = 0;
  if (file_open == 1)
  {
    f_close(&MyFileMems);
  }
}

void Datalog_Sync_Handler()
{
  if (datalog_new_data != 0 && datalog_init_ok != 0 && medium_loaded == 0)
  {
    uint32_t tick = HAL_GetTick();
    if (tick - datalog_last_tick >= datalog_sync_period)
    {
      f_sync(&MyFileMems);
      datalog_new_data = 0;
      datalog_last_tick = tick;
    }
  }
}

void Datalog_Set_RTC_Handle(void *handle)
{
  Rtc_Handle = (RTC_HandleTypeDef *)handle;
}

DWORD get_fattime (void)
{
  RTC_DateTypeDef sdatestructure;
  RTC_TimeTypeDef stimestructure;

  HAL_RTC_GetTime(Rtc_Handle, &stimestructure, FORMAT_BIN);
  HAL_RTC_GetDate(Rtc_Handle, &sdatestructure, FORMAT_BIN);

  WORD fdate;
  WORD ftime;  
  fdate = (WORD)(((sdatestructure.Year + 2000 - 1980) * 512U) | sdatestructure.Month * 32U | sdatestructure.Date);
  ftime = (WORD)(stimestructure.Hours * 2048U | stimestructure.Minutes * 32U | stimestructure.Seconds / 2U);
  DWORD fdatetime = fdate << 16 | ftime;
  
  return fdatetime;
}

#else
#error Not supported platform
#endif


/**
 * @}
 */

/**
 * @}
 */
 
 /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
