/**
 *******************************************************************************
 * @file       vcom.c
 * @author     MEMS Application Team
 * @brief      VCOM message handler
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
#include "cube_hal.h"
#include "vcom.h"
#include "ab_sensor_hub.h"

#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
/* Not supported feature */
#elif ((defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
#include "usbd_cdc_msc.h"
#include "usbd_storage_if.h"
#include "fatfs.h"
#else
#error Not supported platform
#endif

extern sensor_hub_data_t sensor_hub_data;
extern int RTC_SYNCH_PREDIV;
extern RTC_HandleTypeDef RtcHandle;

/** @addtogroup AlgoBuilder_Firmware
  * @{
  */

/** @addtogroup VCP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define DATA_SIZE  (2 * TMsg_MaxLen)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint8_t VCOM_RxData    = 0;    /* Data received from USB (Yes = 1, No = 0). */
volatile uint8_t *VCOM_RxBuffer = NULL; /* Pointer to data buffer (received from USB). */
volatile uint32_t VCOM_RxLength = 0;    /* Data length (received from USB). */

USBD_HandleTypeDef USBD_Device;

static uint8_t dataOut[DATA_SIZE]; /*!< DataOut buffer */

/* Shared function prototypes ------------------------------------------------*/
extern void Error_Handler(void);

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Initialize VCOM (Virtual COM Port)
  * @param  None
  * @retval Init OK: 0, Init ERROR: 1 (_TODO_: implement this)
  */
int VCOM_init(void)
{
  /* Enable USB power on Pwrctrl CR2 register */
  HAL_PWREx_EnableVddUSB();

#if ((defined (USE_NUCLEO)) || (defined (USE_SENSORTILE)))
  
  /*** USB CDC Configuration ***/
  /* Init Device Library */
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, &USBD_CDC);
  
#elif ((defined (USE_SENSORTILEBOX)) || (defined (USE_STWIN)) || (defined (USE_STWIN)) || (defined (USE_STWINBOX)))
  
  FATFS_Init();

  if (SD_Card_Present)
  {
    FATFS_Deinit();
    /*** USB CDC MSC Configuration ***/
    /* Init Device Library */
    USBD_Init(&USBD_Device, &Composite_Desc, 0);
    /* Add Supported Class */
    USBD_RegisterClass(&USBD_Device, &USBD_CDC_MSC);
    /* Register storage callbacks for MSC Class */
    USBD_MSC_RegisterStorage(&USBD_Device, &USBD_Storage_Interface_fops_FS);
    FATFS_Init();
  }
  else
  {
    /*** USB CDC Configuration ***/
    /* Init Device Library */
    USBD_Init(&USBD_Device, &VCP_Desc, 0);
    /* Add Supported Class */
    USBD_RegisterClass(&USBD_Device, &USBD_CDC);
  }
  
#else
#error Not supported platform
#endif

  /* Add Interface callbacks for CDC Class */
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);

  /* Start Device Process */
  USBD_Start(&USBD_Device);

  return 0;
}

/**
  * @brief  De Initialize VCOM (Virtual COM Port)
  * @param  None
  * @retval Init OK: 0, Init ERROR: 1 (_TODO_: implement this)
  */
int VCOM_deinit(void)
{
  /* Stop Device Process */
  USBD_Stop(&USBD_Device);
  
  /* DeInit Device Library */
  USBD_DeInit(&USBD_Device);

  return 0;
}

/**
  * @brief  Check if a message is received via VCOM and read it.
  * @param  Msg the pointer to the message to be received
  * @param  len_max Max. length of message.
  * @retval Message status.
  */
vcom_msg_status_t VCOM_receive_MSG(TMsg *Msg, uint32_t len_max)
{
  vcom_msg_status_t status;

  /* VCOM data receive not completed or no VCOM data received at all. */
  if (VCOM_RxData == 0)
  {
    return NO_DATA;
  }

  /* ERROR: No VCOM data ready. */
  if (VCOM_RxLength == 0 || VCOM_RxBuffer == NULL)
  {
    Error_Handler();
  }

  /* Read message. */
  uint32_t s0_index = 0;
  uint32_t s1_index = 1;
  uint32_t d_index  = 0;
  uint32_t incr     = 0;
  while (1)
  {
    uint8_t  source[2];
    uint8_t* dest;

    /* End of VCOM recieve buffer.
       ERROR: Unexpected end of message. */
    if (s0_index >= VCOM_RxLength)
    {
      status = UNEXP_END_ERR;
      break;
    }

    source[0] = VCOM_RxBuffer[s0_index];

    /* End of message found. */
    if (source[0] == TMsg_EOF)
    {
      status = OK;
      break;
    }

    /* Message length exceeded */
    if (d_index >= len_max)
    {
      status = MSG_LEN_ERR;
      break;
    }

    /* End of VCOM recieve buffer.
       ERROR: Unexpected end of message. */
    if (s1_index >= VCOM_RxLength)
    {
      status = UNEXP_END_ERR;
      break;
    }

    source[1] = VCOM_RxBuffer[s1_index];
    dest      = &Msg->Data[d_index];

    incr = ReverseByteStuffCopyByte2(source[0], source[1], dest);
    Msg->Len = d_index + 1;

    /* ERROR: Invalid sequence found. */
    if (incr == 0)
    {
      status = WRONG_SEQ_ERR;
      break;
    }

    s0_index += incr;
    s1_index = s0_index + 1;
    d_index++;
  }

  switch (status)
  {
  case OK:
    {
      /* More data in VCOM recieve buffer. */
      if (s1_index < VCOM_RxLength)
      {
        VCOM_RxBuffer += s1_index;
        VCOM_RxLength -= s1_index;
      }

      /* End of VCOM recieve buffer. */
      else
      {
        VCOM_RxData   = 0;
        VCOM_RxBuffer = NULL;
        VCOM_RxLength = 0;

        CDC_Next_Packet_Rx();
      }

      /* Check message integrity. */
      if (CHK_CheckAndRemove(Msg))
      {
        return OK;
      }

      else
      {
        return WRONG_CHECK_ERR;
      }
    }

  case UNEXP_END_ERR:
    {
      VCOM_RxData   = 0;
      VCOM_RxBuffer = NULL;
      VCOM_RxLength = 0;

      CDC_Next_Packet_Rx();

      return UNEXP_END_ERR;
    }

  case WRONG_SEQ_ERR:
    {
      VCOM_RxBuffer += s1_index;
      VCOM_RxLength -= s1_index;

      return WRONG_SEQ_ERR;
    }

  case MSG_LEN_ERR:
    {
      VCOM_RxBuffer += s0_index;
      VCOM_RxLength -= s0_index;

      return MSG_LEN_ERR;
    }

  default:
    return UNKNOWN_ERROR;
  }
}

/**
  * @brief  Send a message via VCOM
  * @param  Msg the pointer to the message to be sent
  * @retval None
  */
vcom_msg_status_t VCOM_send_MSG(TMsg *Msg)
{
  uint32_t length;
  uint32_t written;

  if (USBD_Device.dev_state == 0x03)
  {
    CHK_ComputeAndAdd(Msg);
    length = ByteStuffCopy(dataOut, Msg);

    if (CDC_Fill_Buffer(dataOut, length, &written) == USBD_OK)
    {
      return OK;
    }
  }
  return UNKNOWN_ERROR;
}

#if (defined (USE_BLE_OUTPUT))
vcom_msg_status_t VCOM_send_DBG(TMsg *Msg)
{
  uint32_t length;
  uint32_t written;

  uint8_t subSec = 0;
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructure;

  HAL_RTC_GetTime(&RtcHandle, &stimestructure, FORMAT_BIN);
  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, FORMAT_BIN);
  subSec = ((((((int) RTC_SYNCH_PREDIV) - ((int) stimestructure.SubSeconds)) * 100) / (RTC_SYNCH_PREDIV + 1)) & 0xff);

  Msg->Data[Msg->Len] = (uint8_t)stimestructure.Hours;
  Msg->Data[Msg->Len+1] = (uint8_t)stimestructure.Minutes;
  Msg->Data[Msg->Len+2] = (uint8_t)stimestructure.Seconds;
  Msg->Data[Msg->Len+3] = subSec;
  Msg->Len+=4;

  CHK_ComputeAndAdd(Msg);
  length = ByteStuffCopy(dataOut, Msg);

  if (CDC_Fill_Buffer(dataOut, length, &written) == USBD_OK)
  {
    return OK;
  }

  else
  {
    return UNKNOWN_ERROR;
  }
}
#endif

/**
  * @brief  Send a FFT data via VCOM
  * @param  data pointer to FFT data
  * @param  size of data (number of floats)
  * @retval None
  */
vcom_msg_status_t VCOM_send_FFT(float *data, uint32_t size, uint8_t config_index)
{
  uint16_t CountOut;
  uint8_t header[8];
  uint8_t CHK;
  uint8_t buffer[512];
  uint32_t copy_size;
  uint32_t index;
  uint32_t written;
  float *sf = (float*)(&header[4]);

  header[0] = 1; //DataStreamingDest;
  header[1] = 50; //DEV_ADDR;
  header[2] = 0x7d; //CMD_SF_DATA;
  header[3] = config_index;
  *sf = sensor_hub_data.meas_data_rate_Hz;
  CHK = CHK_Compute(header, 8, 0);
  CHK = CHK_Compute((uint8_t*)data, size * 4, CHK);
  if (CDC_Fill_Buffer(header, 8, &written) != USBD_OK)
  {
    return UNKNOWN_ERROR;
  }
  index = 0;
  while (size > 0)
  {
    copy_size = 64;
    if (copy_size > size) copy_size = size; //number of floats
    CountOut = ByteStuffCopyBuffer(buffer, (uint8_t*)(&data[index]), copy_size * 4);
    if (CDC_Fill_Buffer(buffer, CountOut, &written) != USBD_OK)
    {
      return UNKNOWN_ERROR;
    }
    index += copy_size;
    size -= copy_size;
    HAL_Delay(2);
  }
    
  CountOut = ByteStuffCopyBuffer(header, &CHK, 1);
  header[CountOut] = TMsg_EOF;
  CountOut++;
  if (CDC_Fill_Buffer(header, CountOut, &written) != USBD_OK)
  {
    return UNKNOWN_ERROR;
  }
  return OK;
}


/**
 * @brief  Read from VCOM
 * @param  Pointer to buffer.
 * @param  Data max. length.
 * @retval Number of really read data bytes.
 */
uint32_t VCOM_read(char *buffer, uint32_t len_max)
{
  /* VCOM data receive not completed or no VCOM data received at all. */
  if (VCOM_RxData == 0)
  {
    return 0;
  }

  /* ERROR: No VCOM data ready. */
  if (VCOM_RxLength == 0 || VCOM_RxBuffer == NULL)
  {
    Error_Handler();
  }

  /* Read all data */
  if (VCOM_RxLength <= len_max)
  {
    uint32_t len = VCOM_RxLength;
    memcpy((uint8_t*)buffer, (uint8_t*)VCOM_RxBuffer, len);

    VCOM_RxData   = 0;
    VCOM_RxBuffer = NULL;
    VCOM_RxLength = 0;

    CDC_Next_Packet_Rx();
    return len;
  }

  /* Read part of data that fits into buffer. */
  else
  {
    memcpy((uint8_t*)buffer, (uint8_t*)VCOM_RxBuffer, len_max);

    VCOM_RxBuffer += len_max;
    VCOM_RxLength -= len_max;

    return len_max;
  }
}

/**
 * @brief  Write to VCOM
 * @param  Pointer to buffer.
 * @param  Number of data bytes to write.
 * @retval Number of really written data bytes.
 */
uint32_t VCOM_write(char *buffer, uint32_t len)
{
  uint32_t written;
  CDC_Fill_Buffer((uint8_t *)buffer, len, &written);
  return written;
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
