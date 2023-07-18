
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "svm.h"
#include "svm_data.h"

/* USER CODE BEGIN includes */

#include "math.h"
#include "fatfs.h"
#include "ff.h"

#define BUFSIZE 256
char	SendBuffer[BUFSIZE];

uint8_t windowLength = 104;
uint8_t windowOverlap = 52;

float bufAccX[104];
float bufAccY[104];
float bufAccZ[104];
float bufAccMagnitude[104];

float accX_Mean;
float accX_STD;
float accX_MinMax;
float accX_RMS;
float accY_Mean;
float accY_STD;
float accY_MinMax;
float accY_RMS;
float accZ_Mean;
float accZ_STD;
float accZ_MinMax;
float accZ_RMS;
float accMagnitude_Mean;
float accMagnitude_STD;
float accMagnitude_MinMax;
float accMagnitude_RMS;

int buf_len = 0;

#define LSM6DSOX_ACC_SENSITIVITY_FS_4G   0.122f
//#define LSM6DSOX_ACC_SENSITIVITY_FS_2G   0.061f

	  uint8_t indata[2];
	  uint8_t outdata[2] = {0,0};
	  uint8_t lis_id;
	  uint8_t newValueAvailable = 0;

	  uint8_t AccelX1;
	  uint8_t AccelY1;
	  uint8_t AccelZ1;
	  uint8_t AccelX2;
	  uint8_t AccelY2;
	  uint8_t AccelZ2;

	  const char* classes[5] = {
	  			  "jaz", "mami", "mirovanje", "sestra", "vati"
	  	  };

	  FRESULT res; /* FatFs function common result code */
	  uint32_t byteswritten, bytesread; /* File write/read counts */
	  uint8_t wtext[BUFSIZE] = "Podatki: \r\n"; /* File write buffer */
	  uint8_t rtext[_MAX_SS];/* File read buffer */

	  char errorValue[20] = "Ni problema";
	  uint8_t countOutput = 0;

/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_SVM_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_SVM_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_SVM_IN_NUM] = {
data_in_1
};
#else
ai_i8* data_ins[AI_SVM_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_SVM_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_SVM_OUT_1_SIZE_BYTES];
AI_ALIGNED(4) ai_i8 data_out_2[AI_SVM_OUT_2_SIZE_BYTES];
ai_i8* data_outs[AI_SVM_OUT_NUM] = {
data_out_1,
data_out_2
};
#else
ai_i8* data_outs[AI_SVM_OUT_NUM] = {
NULL,
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_SVM_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle svm = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_svm_create_and_init(&svm, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_svm_create_and_init");
    return -1;
  }

  ai_input = ai_svm_inputs_get(svm, NULL);
  ai_output = ai_svm_outputs_get(svm, NULL);

#if defined(AI_SVM_INPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
   *  used from the activations buffer. This is not mandatory.
   */
  for (int idx=0; idx < AI_SVM_IN_NUM; idx++) {
	data_ins[idx] = ai_input[idx].data;
  }
#else
  for (int idx=0; idx < AI_SVM_IN_NUM; idx++) {
	  ai_input[idx].data = data_ins[idx];
  }
#endif

#if defined(AI_SVM_OUTPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
   *  used from the activations buffer. This is no mandatory.
   */
  for (int idx=0; idx < AI_SVM_OUT_NUM; idx++) {
	data_outs[idx] = ai_output[idx].data;
  }
#else
  for (int idx=0; idx < AI_SVM_OUT_NUM; idx++) {
	ai_output[idx].data = data_outs[idx];
  }
#endif

  return 0;
}

static int ai_run(void)
{
  ai_i32 batch;

  batch = ai_svm_run(svm, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_svm_get_error(svm),
        "ai_svm_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
float accMagnitude(float accX, float accY, float accZ) {
	float result = sqrt(accX * accX + accY * accY + accZ * accZ);
	return result;
}

int acquire_and_process_data(ai_float* data[])
{
	while(buf_len < windowLength) {
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
				outdata[0] = 0x1e | 0x80 ; // read status register if there is new accelerometer data
				HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
				newValueAvailable = indata[1] & 0b1; //only accelerometer state
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

				if(newValueAvailable == 1) {
					buf_len++;

					newValueAvailable = 0;

					//////////////////////////////////////////Read accelerometer measurements
					outdata[0] = 0x29 | 0x80 ; // read x, high
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelX1 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
					outdata[0] = 0x28 | 0x80 ; // read x, low
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelX2 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					outdata[0] = 0x2b | 0x80 ; // read y, 0x53
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelY1 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
					outdata[0] = 0x2a | 0x80 ; // read y, low
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelY2 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					outdata[0] = 0x2d | 0x80 ; // read z, 0x55
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelZ1 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
					outdata[0] = 0x2c | 0x80 ; // read z, low
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelZ2 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

					//Calculation to get measurements in the unit mG and with /1000 to G
					int16_t AccelX;
					int32_t AccelX_mg;
					int16_t AccelY;
					int32_t AccelY_mg;
					int16_t AccelZ;
					int32_t AccelZ_mg;

					AccelX= ((int16_t)AccelX1 <<8 ) | AccelX2;
					AccelX_mg= (int32_t)((float)AccelX * LSM6DSOX_ACC_SENSITIVITY_FS_4G);
					AccelY= ((int16_t)AccelY1 <<8 ) | AccelY2;
					AccelY_mg= (int32_t)((float)AccelY * LSM6DSOX_ACC_SENSITIVITY_FS_4G);
					AccelZ= ((int16_t)AccelZ1 <<8 ) | AccelZ2;
					AccelZ_mg= (int32_t)((float)AccelZ * LSM6DSOX_ACC_SENSITIVITY_FS_4G);

					float AccelX_inG = AccelX_mg * 0.001f;
					float AccelY_inG = AccelY_mg * 0.001f;
					float AccelZ_inG = AccelZ_mg * 0.001f;


					bufAccX[buf_len - 1] = AccelX_inG;
					bufAccY[buf_len - 1] = AccelY_inG;
					bufAccZ[buf_len - 1] = AccelZ_inG;

					bufAccMagnitude[buf_len - 1] = accMagnitude(AccelX_inG, AccelY_inG, AccelZ_inG);
				}
			}

			if(buf_len == windowLength) {
				buf_len = windowOverlap;

				accX_Mean = 0;
				accX_STD = 0;
				accX_MinMax = 0;
				accX_RMS = 0;

				accY_Mean = 0;
				accY_STD = 0;
				accY_MinMax = 0;
				accY_RMS = 0;

				accZ_Mean = 0;
				accZ_STD = 0;
				accZ_MinMax = 0;
				accZ_RMS = 0;

				accMagnitude_Mean = 0;
				accMagnitude_STD = 0;
				accMagnitude_MinMax = 0;
				accMagnitude_RMS = 0;


				float minX = bufAccX[0];
				float maxX = bufAccX[0];
				float minY = bufAccY[0];
				float maxY = bufAccY[0];
				float minZ = bufAccZ[0];
				float maxZ = bufAccZ[0];
				float minMagnitude = bufAccMagnitude[0];
				float maxMagnitude = bufAccMagnitude[0];


				for (int i = 0; i < windowLength; i++) {

					accX_Mean += bufAccX[i];
					if(minX > bufAccX[i])
						minX = bufAccX[i];
					if(maxX < bufAccX[i])
						maxX = bufAccX[i];
					accX_RMS += pow(bufAccX[i], 2);

					accY_Mean += bufAccY[i];
					if(minY > bufAccY[i])
						minY = bufAccY[i];
					if(maxY < bufAccY[i])
						maxY = bufAccY[i];
					accY_RMS += pow(bufAccY[i], 2);

					accZ_Mean += bufAccZ[i];
					if(minZ > bufAccZ[i])
						minZ = bufAccZ[i];
					if(maxZ < bufAccZ[i])
						maxZ = bufAccZ[i];
					accZ_RMS += pow(bufAccZ[i], 2);

					accMagnitude_Mean += bufAccMagnitude[i];
					if(minMagnitude > bufAccMagnitude[i])
						minMagnitude = bufAccMagnitude[i];
					if(maxMagnitude < bufAccMagnitude[i])
						maxMagnitude = bufAccMagnitude[i];
					accMagnitude_RMS += pow(bufAccMagnitude[i], 2);

				}

				accX_Mean /= windowLength;
				accX_MinMax = maxX - minX;
				accX_RMS = sqrt(accX_RMS/windowLength);

				accY_Mean /= windowLength;
				accY_MinMax = maxY - minY;
				accY_RMS = sqrt(accY_RMS/windowLength);

				accZ_Mean /= windowLength;
				accZ_MinMax = maxZ - minZ;
				accZ_RMS = sqrt(accZ_RMS/windowLength);

				accMagnitude_Mean /= windowLength;
				accMagnitude_MinMax = maxMagnitude - minMagnitude;
				accMagnitude_RMS = sqrt(accMagnitude_RMS/windowLength);

				for (int i = 0; i < windowLength; i++) {
					accX_STD += pow(bufAccX[i] - accX_Mean, 2);
					accY_STD += pow(bufAccY[i] - accY_Mean, 2);
					accZ_STD += pow(bufAccZ[i] - accZ_Mean, 2);
					accMagnitude_STD += pow(bufAccMagnitude[i] - accMagnitude_Mean, 2);
				}

				accX_STD = sqrt(accX_STD / windowLength);
				accY_STD = sqrt(accY_STD / windowLength);
				accZ_STD = sqrt(accZ_STD / windowLength);
				accMagnitude_STD = sqrt(accMagnitude_STD / windowLength);


				//Replace first half of buffers with their second half
				for (int i = 0; i < windowOverlap; i++) {
					bufAccX[i] = bufAccX[i + windowOverlap];
					bufAccY[i] = bufAccY[i + windowOverlap];
					bufAccZ[i] = bufAccZ[i + windowOverlap];
					bufAccMagnitude[i] = bufAccMagnitude[i + windowOverlap];
				}


				data[0][0] = (accX_Mean - (-0.7925340396583439)) * 2.0949933205020708;
				data[0][1] = (accX_STD - 0.25463438722461235) * 5.929210562633304;
				data[0][2] = (accX_MinMax - 1.2237432034064877) * 1.1805004714159546;
				data[0][3] = (accX_RMS - 0.9080303069938368) * 2.8316304285664726;

				data[0][4] = (accY_Mean - (-0.043692102975635576)) * 3.7465012332289103;
				data[0][5] = (accY_STD - 0.2380924561831248) * 6.581672613424032;
				data[0][6] = (accY_MinMax - 1.2170445463478536) * 1.2546657227425297;
				data[0][7] = (accY_RMS - 0.3188075751411812) * 4.415641148049384;

				data[0][8] = (accZ_Mean - 0.0036754295900627365) * 3.7391857781655413;
				data[0][9] = (accZ_STD - 0.23952607306415402) * 7.479754757980447;
				data[0][10] = (accZ_MinMax - 1.2980415984277747) * 1.313726772069218;
				data[0][11] = (accZ_RMS - 0.3156636494289826) * 4.60580702527008;

				data[0][12] = (accMagnitude_Mean - 1.0669456527929735) * 15.930676904057798;
				data[0][13] = (accMagnitude_STD - 0.2766352751305663) * 5.763399986208959;
				data[0][14] = (accMagnitude_MinMax - 1.3165988949163936) * 1.1621726084324315;
				data[0][15] = (accMagnitude_RMS - 1.1134635041015108) * 10.457188751844905;
			}
  return 0;
}

int post_process(ai_i8* data[])
{
	snprintf(SendBuffer,BUFSIZE,"Razred: %lu, %s \r\n", (int32_t) *data[0], classes[(int) ((int32_t) *data[0])]);
	CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));

	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	switch((int32_t) *data[0])
		    {
		        case 0:
		        	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);
		            break;
		        case 1:
		        	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET);
		        	break;
		        case 2:
		        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		        	break;
		        case 3:
		        	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);
		        	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET);
		        	break;
		        case 4:
		        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		        	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET);
		        	break;
		    }

	///////////////////////////////////////////////////////////////////SD card

	f_open(&SDFile, "Podatki.TXT", FA_OPEN_APPEND | FA_WRITE);
	f_lseek(&SDFile, f_size(&SDFile));

	strcpy(wtext, SendBuffer);

	res = f_write(&SDFile, wtext, strlen((char *)wtext), (void *)&byteswritten);

	f_close(&SDFile);

	///////////////////////////////////////////////////////////////////

  return 0;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	outdata[0] = 0x0f | 0x80 ; // read whoami
	HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
	lis_id = indata[1];
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

	snprintf(SendBuffer,BUFSIZE,"[ID:%02x] \r\n",lis_id);
	CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));


	// sensor setup (activation and setting frequency)
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);

	outdata[0] = 0x10 ; // register used for setting up the accelerometer
	outdata[1] = 0x48 ;//0x4a ;//0x40 ; // set frequency to 104Hz and FS to 4g
	HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);


	outdata[0] = 0x15 | 0x80 ; // read CTRL6_C
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
	uint8_t existingValue = indata[1];
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	outdata[0] = 0x15 ; // write to register CTRL6_C
	outdata[1] = existingValue | 0x10 ; //disable high performance
	HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);


	///////////////////////////////////////////////////////////////////SD card
	if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) != FR_OK)
	{
		//Error_Handler();
		snprintf(SendBuffer,BUFSIZE,"Error1 \r\n");
		CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));
		strcpy(errorValue, "Error1 \r\n");
	}
	else
	{
		if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, rtext, sizeof(rtext)) != FR_OK)
	    {
			//Error_Handler();
			snprintf(SendBuffer,BUFSIZE,"Error2 \r\n");
			CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));

			FRESULT errorState = f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, rtext, sizeof(rtext));

			snprintf(errorValue, 20, "Error2 [%d]\r\n", errorState);
	    }
		else
		{
			//Open file for writing (Create)
			if(f_open(&SDFile, "Podatki.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
			{
				//Error_Handler();
				snprintf(SendBuffer,BUFSIZE,"Error3 \r\n");
				CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));
				strcpy(errorValue, "Error3 \r\n");
			}
			else
			{

				//Write to the text file
				res = f_write(&SDFile, wtext, strlen((char *)wtext), (void *)&byteswritten);
				if((byteswritten == 0) || (res != FR_OK))
				{
					//Error_Handler();
					snprintf(SendBuffer,BUFSIZE,"Error4 \r\n");
					CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));
					strcpy(errorValue, "Error4 \r\n");
				}
				else
				{

					f_close(&SDFile);
				}
			}
		}
	}

	f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
	///////////////////////////////////////////////////////////////////



  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
  int res = -1;

  printf("TEMPLATE - run - main loop\r\n");

  if (svm) {

    do {
      /* 1 - acquire and pre-process input data */
      res = acquire_and_process_data(data_ins);
      /* 2 - process the data - call inference engine */
      if (res == 0)
        res = ai_run();
      /* 3- post-process the predictions */
      if (res == 0)
        res = post_process(data_outs);
    } while (res==0);
  }

  if (res) {
    ai_error err = {AI_ERROR_INVALID_STATE, AI_ERROR_CODE_NETWORK};
    ai_log_err(err, "Process has FAILED");
  }
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
