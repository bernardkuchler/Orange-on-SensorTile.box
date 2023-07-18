
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

int counterOfTestData = 0;

int numberOfDurations = 100;
uint32_t averageDurationValue = 0;
int countDurations = 0;


float testData[] = {2.466293163028155e-07, 2.453839476057596e-07, 1.787794572383206e-07, 4.025996696022105e-07, 1.0707693554046216e-06,
		2.729905010934175e-07, 1.3036247592523864e-07, 2.2338122973586397e-07, 1.3165442847018485e-07, 2.3984931973863866e-07, 2.1334496858038682e-07,
		2.0199179706636985e-07, 1.7792400686111878e-07, 1.9232686399028864e-07, 2.239820435789852e-07, 2.470156319489547e-07, 2.1608693634433962e-07,
		1.7976643729156194e-07, 2.502192206765841e-07, 2.4656127273203765e-07, 2.252821247328285e-07, 1.785019880795602e-07, 2.3686227113017821e-07,
		2.3654482861346082e-07, 2.4569974921284654e-07, 2.477296949798813e-07, 2.4756893313160333e-07, 2.448707572266784e-07, 2.4626766670365896e-07,
		2.530734666272849e-07, 2.416840203522952e-07, 2.2586991166306802e-07, 2.4109893281831773e-07, 2.4725173841666503e-07, 2.349033894066821e-07,
		2.45674404153462e-07, 2.4842346468823e-07, 2.2700569490829994e-07, 2.449630338574593e-07, 2.2648041730910506e-07, 2.4978005619402666e-07,
		2.2830073342916535e-07, 2.484234651323192e-07, 2.4574360790730054e-07, 2.5076875354024253e-07, 2.1554745943674905e-07, 2.3641005797436779e-07,
		2.3391676284845173e-07, 2.375023833156576e-07, 1.5416373022603125e-07, 2.495342270592005e-07, 2.362046149784192e-07, 2.499518234611031e-07,
		2.505450524825648e-07, 2.509931722460834e-07, 2.491407766758158e-07, 1.9851194132947117e-07, 2.491465669329785e-07, 2.5081921317671174e-07,
		2.230854252438519e-07, 0.256451198750973, 1.1918942990122336, 1.0293003995621546, 0.5689617519490024, 0.4849488920212286, 0.8396363990899536,
		0.6201024630104675, 0.2451725748990894, 0.1538014389798288, 0.3742534809190609, 0.5182572232891705, 0.3480426817181965, 0.8115067232967563,
		0.6440393256179897, 0.1044263809635388, 0.1330492127410241, 0.781979073977197, 0.7378801145093243, 0.4570705142392151, 0.3131418982694898,
		0.1969119773092773, 0.826044266643114, 0.7284551128741812, 0.2382233256152621, 0.1390090133653458, 0.0967863205089494, 0.0532680353946934,
		0.0615622048812092, 0.0655417319083651, 0.5180131893866129, 0.6762755065587278, 0.5565364882091748, 0.909664035907487, 0.226389319235484,
		0.1699153034065674, 0.0739804613826047, 0.1295739706696399, 0.1594842793529687, 0.112173366179002, 0.1551887258876765, 0.1649648111876471,
		0.1662311079016247, 0.1639636668152082, 0.1285992730326559, 0.3524494340078083, 0.2946016053366929, 0.4758711215421314, 0.697207179349093,
		0.2949559494226179, 0.059913021111474, 0.0664212463374218, 0.6256707359550862, 0.4341567752196935, 0.1017664851436492, 0.2240307047976015,
		0.2810140341420828, 0.05051557143033, 0.1204609548782085, 0.2399269996401658, 0.1730092414374542, 0.09235465924514, 0.076406017545473,
		0.070062006369594, 0.1403729124741943, 0.1165051791192288, 0.0214672249327163, 0.0104785010609842, 0.0512318323245908, 0.1345758672777912,
		0.0932879022140888, 0.012836055578719, 0.0018102213035029, 0.0026657752970722, 0.0044054513831612, 0.1395531316215335, 0.1767293099454576,
		0.0285507970958898, 0.0091906895773383, 0.0031080255712305, 0.0042489372701792, 0.001605549966819, 0.0023704671795079, 0.0090257444695729,
		0.0043746818613776, 0.0056423240470078, 0.0327811373680542, 0.0713568244450605, 0.0155183904590678, 0.0142869387992841, 0.0171313901070397,
		0.0016316366637376, 0.0021597943589866, 0.0039313461873593, 0.0145222488013982, 0.0148580110788096, 0.0113824855963475, 0.0070561603245047,
		0.0030164582616158, 0.1358820693679601, 0.0815997292981953, 0.1529422670098137, 0.1630049114280112, 0.0065703476146865, 0.0078270896795291,
		0.0069769410286295, 0.0029278877516287, 0.0015234274508855, 0.0012565872701151, 0.0035783151031552, 0.010224420781147, 0.0623567194972176,
		0.1401663850253749, 0.1055609897804381, 0.0910324363731371, 0.0280231276892524, 0.0192889164056884, 0.0211591592717421, 0.0201516400389976,
		0.0203900934865008, 0.0205685504661767, 0.0245678338462753, 0.0224581217865558, 0.015439502276715, 0.0068437521567108};

int size = sizeof(testData) / sizeof(testData[0]);

uint32_t timestamp;

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
	if(counterOfTestData == 0) {
		timestamp = htim16.Instance->CNT;
	}

	for (int idx=0; idx < AI_SVM_IN_NUM; idx++ ) //SVM jakost
	{
	    data[idx][0] = (testData[counterOfTestData] - 0.22330145150297734) * 2.5709241370783027; //Orange predprocesiranje podatkov (offset in factor)
	}

	counterOfTestData++;
  return 0;
}

int post_process(ai_i8* data[])
{
	if(counterOfTestData == size) {

		counterOfTestData = 0;

		countDurations++;

		uint32_t duration = htim16.Instance->CNT;

		if(duration >= timestamp)
			duration -= timestamp;
		else
			duration += (65535 - timestamp) + 1; //+1 because of counting from 0 onwards

		//snprintf(SendBuffer,BUFSIZE,"1 Trajanje izvajanja: %lu milisekund. \r\n", duration);
		//CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));
		averageDurationValue += duration;

		if(countDurations == numberOfDurations) {
			snprintf(SendBuffer,BUFSIZE,"Trajanje izvajanja: [%lu] %lu milisekund. \r\n", averageDurationValue, averageDurationValue / 100);
			CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));

			countDurations = 0;
			averageDurationValue = 0;
		}
	}

  return 0;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    BSP_QSPI_Init_t qspiInit;
    qspiInit.InterfaceMode=MT25TL01G_QPI_MODE;
    qspiInit.TransferRate= MT25TL01G_DTR_TRANSFER ;
    qspiInit.DualFlashMode= MT25TL01G_DUALFLASH_ENABLE;
    BSP_QSPI_Init(0,&qspiInit);
    BSP_QSPI_EnableMemoryMappedMode(0);
    /* USER CODE BEGIN 5 */

    HAL_TIM_Base_Start(&htim16);

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
