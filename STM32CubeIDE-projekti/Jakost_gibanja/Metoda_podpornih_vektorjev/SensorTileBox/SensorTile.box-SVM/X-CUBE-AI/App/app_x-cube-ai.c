
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

#define BUFSIZE 256
char	SendBuffer[BUFSIZE];

float bufVar[26];
int bufVar_len = 0;

#define LSM6DSOX_ACC_SENSITIVITY_FS_4G   0.122f

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

	  const char* classes[3] = {"mirovanje", "srednja jakost", "velika jakost"};

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
int acquire_and_process_data(ai_float* data[])
{
	while(bufVar_len < 26) {
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
				outdata[0] = 0x1e | 0x80 ; // read status register if there is new accelerometer data
				HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
				newValueAvailable = indata[1] & 0b1; //only accelerometer state
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

				if(newValueAvailable == 1) {
					bufVar_len++;

					newValueAvailable = 0;

					//Read accelerometer measurements
					outdata[0] = 0x29 | 0x80 ; // read x, 0x51
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelX1 = indata[1];
					outdata[0] = 0x28 | 0x80 ; // read x, low
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelX2 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					outdata[0] = 0x2b | 0x80 ; // read y, 0x53
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelY1 = indata[1];
					outdata[0] = 0x2a | 0x80 ; // read y, low
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelY2 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					outdata[0] = 0x2d | 0x80 ; // read z, 0x55
					HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);
					AccelZ1 = indata[1];
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
					outdata[0] = 0x2c | 0x80 ; // read z, low
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

					float AccelX_inG = AccelX_mg * 0.001f; //Calculation to get measurements in the unit mG and with /1000 to G
					float AccelY_inG = AccelY_mg * 0.001f;
					float AccelZ_inG = AccelZ_mg * 0.001f;


					bufVar[bufVar_len - 1] = sqrt(AccelX_inG * AccelX_inG + AccelY_inG * AccelY_inG + AccelZ_inG * AccelZ_inG);
				}
			}

			if(bufVar_len == 26) {
				bufVar_len = 0;
				float summ = 0;
				float sumOfSquares = 0;
				for(int i = 0; i < 26; i++) {
					summ += bufVar[i];
					sumOfSquares += bufVar[i] * bufVar[i];
				}
				float mean = summ / 26;
				float meanSquared = mean * mean;

				float svmInputValue = (sumOfSquares / 26) - meanSquared;

				for (int idx=0; idx < AI_SVM_IN_NUM; idx++ )
				  {
				      data[idx][0] = (svmInputValue - 0.22330145150297734) * 2.5709241370783027; //using offset and factor from Orange data preprocessing
				  }
			}
  return 0;
}

int post_process(ai_i8* data[])
{
	snprintf(SendBuffer,BUFSIZE,"Razred: %lu, %s \r\n", (int32_t) *data[0], classes[(int) ((int32_t) *data[0])]);///////snprintf(SendBuffer,BUFSIZE,"Razred: %lu, %d, %d, %d, %d \r\n", (int32_t) *data[0], data[0][0], data[0][1], data[0][2], data[0][3]);
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
		    }
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
		outdata[1] = 0x28 ; // set frequency to 26Hz and FS to 4g
		HAL_SPI_TransmitReceive(&hspi1, &outdata, &indata, 2, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);


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
