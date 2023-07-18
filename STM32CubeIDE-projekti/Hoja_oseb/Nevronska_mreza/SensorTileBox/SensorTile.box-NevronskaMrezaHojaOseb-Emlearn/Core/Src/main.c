/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nevronskaMreza_HojaOseb.h"

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

float accMagnitude(float accX, float accY, float accZ);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel0;
DMA_HandleTypeDef hdma_dfsdm1_flt0;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

RTC_HandleTypeDef hrtc;

SD_HandleTypeDef hsd1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_DFSDM1_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C3_Init(void);
static void MX_RTC_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_DFSDM1_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_RTC_Init();
  MX_SDMMC1_SD_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

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

  		    		//strcpy(errorValue, "Error2 \r\n");
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
  		    //f_mount(&SDFatFS, (TCHAR const*)NULL, 0);

  		    f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
  		    //f_open(&SDFile, "Podatki.TXT", FA_OPEN_APPEND | FA_WRITE);
  		    ///////////////////////////////////////////////////////////////////


  while (1)
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


	  		accX_Mean = (accX_Mean - (-0.7925340396583439)) * 2.0949933205020708;
	  		accX_STD = (accX_STD - 0.25463438722461235) * 5.929210562633304;
	  		accX_MinMax = (accX_MinMax - 1.2237432034064877) * 1.1805004714159546;
	  		accX_RMS = (accX_RMS - 0.9080303069938368) * 2.8316304285664726;

	  		accY_Mean = (accY_Mean - (-0.043692102975635576)) * 3.7465012332289103;
	  		accY_STD = (accY_STD - 0.2380924561831248) * 6.581672613424032;
	  		accY_MinMax = (accY_MinMax - 1.2170445463478536) * 1.2546657227425297;
	  		accY_RMS = (accY_RMS - 0.3188075751411812) * 4.415641148049384;

	  		accZ_Mean = (accZ_Mean - 0.0036754295900627365) * 3.7391857781655413;
	  		accZ_STD = (accZ_STD - 0.23952607306415402) * 7.479754757980447;
	  		accZ_MinMax = (accZ_MinMax - 1.2980415984277747) * 1.313726772069218;
	  		accZ_RMS = (accZ_RMS - 0.3156636494289826) * 4.60580702527008;

	  		accMagnitude_Mean = (accMagnitude_Mean - 1.0669456527929735) * 15.930676904057798;
	  		accMagnitude_STD = (accMagnitude_STD - 0.2766352751305663) * 5.763399986208959;
	  		accMagnitude_MinMax = (accMagnitude_MinMax - 1.3165988949163936) * 1.1621726084324315;
	  		accMagnitude_RMS = (accMagnitude_RMS - 1.1134635041015108) * 10.457188751844905;

	  		/////////////////////////////////////Result

	  		const float features[] = { accX_Mean, accX_STD, accX_MinMax, accX_RMS, accY_Mean, accY_STD, accY_MinMax, accY_RMS,
	  								 accZ_Mean, accZ_STD, accZ_MinMax, accZ_RMS, accMagnitude_Mean, accMagnitude_STD, accMagnitude_MinMax, accMagnitude_RMS };
	  		int out = nevronskaMreza_HojaOseb_predict(features, 16); // Alternative A: "inline"
	  		if (out < 0) {
	  		    return out; // error
	  		} else {
	  			snprintf(SendBuffer,BUFSIZE,"Razred: %lu, %s \r\n", out, classes[out]);
	  			CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));

	  			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET);
	  			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET);
	  			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	  			switch(out)
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
	  		}
	  	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.DFSDMConfig = ADC_DFSDM_MODE_ENABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief DFSDM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DFSDM1_Init(void)
{

  /* USER CODE BEGIN DFSDM1_Init 0 */

  /* USER CODE END DFSDM1_Init 0 */

  /* USER CODE BEGIN DFSDM1_Init 1 */

  /* USER CODE END DFSDM1_Init 1 */
  hdfsdm1_filter0.Instance = DFSDM1_Filter0;
  hdfsdm1_filter0.Init.RegularParam.Trigger = DFSDM_FILTER_SW_TRIGGER;
  hdfsdm1_filter0.Init.RegularParam.FastMode = ENABLE;
  hdfsdm1_filter0.Init.RegularParam.DmaMode = ENABLE;
  hdfsdm1_filter0.Init.FilterParam.SincOrder = DFSDM_FILTER_SINC2_ORDER;
  hdfsdm1_filter0.Init.FilterParam.Oversampling = 192;
  hdfsdm1_filter0.Init.FilterParam.IntOversampling = 1;
  if (HAL_DFSDM_FilterInit(&hdfsdm1_filter0) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel0.Instance = DFSDM1_Channel0;
  hdfsdm1_channel0.Init.OutputClock.Activation = DISABLE;
  hdfsdm1_channel0.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM;
  hdfsdm1_channel0.Init.OutputClock.Divider = 2;
  hdfsdm1_channel0.Init.Input.Multiplexer = DFSDM_CHANNEL_ADC_OUTPUT;
  hdfsdm1_channel0.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel0.Init.Input.Pins = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  hdfsdm1_channel0.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
  hdfsdm1_channel0.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL;
  hdfsdm1_channel0.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel0.Init.Awd.Oversampling = 1;
  hdfsdm1_channel0.Init.Offset = 0x00;
  hdfsdm1_channel0.Init.RightBitShift = 7;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel0) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_0, DFSDM_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DFSDM1_Init 2 */

  /* USER CODE END DFSDM1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00B03FDB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00B03FDB;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_TUESDAY;
  sDate.Month = RTC_MONTH_APRIL;
  sDate.Date = 3;
  sDate.Year = 20;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  hsd1.Init.Transceiver = SDMMC_TRANSCEIVER_ENABLE;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 119;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFFFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 119;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 119;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 0xFFFF;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_LIS2MDL_GPIO_Port, CS_LIS2MDL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SD_SEL_Pin|SD_EN_Pin|CS_LIS2DW12_Pin|CS_IIS3DHHC_Pin
                          |CS_LSM6DSOX_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, USER_LED_Pin|BB_MODE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CHG_LED2_GPIO_Port, CHG_LED2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LDO_2V7_EN_GPIO_Port, LDO_2V7_EN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SW_SEL_GPIO_Port, SW_SEL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CPU_LED_GPIO_Port, CPU_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : INT2_LSM6DSOX_Pin INT2_IIS3DHHC_Pin */
  GPIO_InitStruct.Pin = INT2_LSM6DSOX_Pin|INT2_IIS3DHHC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : USART2_RX_Pin USART2_TX_Pin */
  GPIO_InitStruct.Pin = USART2_RX_Pin|USART2_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : CS_LIS2MDL_Pin */
  GPIO_InitStruct.Pin = CS_LIS2MDL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(CS_LIS2MDL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SD_SEL_Pin SD_EN_Pin */
  GPIO_InitStruct.Pin = SD_SEL_Pin|SD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : USER_LED_Pin BB_MODE_Pin LDO_2V7_EN_Pin */
  GPIO_InitStruct.Pin = USER_LED_Pin|BB_MODE_Pin|LDO_2V7_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : CHG_LED2_Pin SW_SEL_Pin */
  GPIO_InitStruct.Pin = CHG_LED2_Pin|SW_SEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : CHG_LED_Pin */
  GPIO_InitStruct.Pin = CHG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CHG_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : INT_LPS22HH_Pin INT2_LIS2DW12_Pin INT_HTS221_Pin */
  GPIO_InitStruct.Pin = INT_LPS22HH_Pin|INT2_LIS2DW12_Pin|INT_HTS221_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_LIS2DW12_Pin CS_IIS3DHHC_Pin CS_LSM6DSOX_Pin */
  GPIO_InitStruct.Pin = CS_LIS2DW12_Pin|CS_IIS3DHHC_Pin|CS_LSM6DSOX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : CPU_LED_Pin */
  GPIO_InitStruct.Pin = CPU_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CPU_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : INT1_LIS2DW12_Pin */
  GPIO_InitStruct.Pin = INT1_LIS2DW12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INT1_LIS2DW12_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : INT1_LSM6DSOX_Pin */
  GPIO_InitStruct.Pin = INT1_LSM6DSOX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INT1_LSM6DSOX_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_DETECT_Pin */
  GPIO_InitStruct.Pin = SD_DETECT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SD_DETECT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_PB1_Pin */
  GPIO_InitStruct.Pin = USER_PB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_PB1_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

float accMagnitude(float accX, float accY, float accZ) {
    //return sqrt(pow(accX, 2) + pow(accY, 2) + pow(accZ, 2));
	float result = sqrt(accX * accX + accY * accY + accZ * accZ);
	return result;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
