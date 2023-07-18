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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nevronskaMreza_jakostGibanja.h"

#define BUFSIZE 256
char	SendBuffer[BUFSIZE];

int counterOfTestData = 0;

int numberOfDurations = 100;
uint32_t averageDurationValue = 0;
int countDurations = 0;

uint32_t timestamp;

const float inputList[] = {2.466293163028155e-07, 2.453839476057596e-07, 1.787794572383206e-07, 4.025996696022105e-07, 1.0707693554046216e-06,
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
		/* {-0.5740904574483623, -0.5740904606501107, -0.5740906318852026, -0.5740900564604163, -0.5740883386468434,
    -0.574090389675756, -0.5740907563615886, -0.5740905172174292, -0.5740907530400766, -0.574090474879219, -0.5740905430198953, -0.5740905722080379,
    -0.5740906340845007, -0.5740905970558476, -0.5740905156727824, -0.5740904564551741, -0.5740905359705041, -0.5740906293477518, -0.5740904482189905,
    -0.5740904576232971, -0.5740905123303723, -0.5740906325985548, -0.5740904825586944, -0.574090483374815, -0.5740904598382087, -0.5740904546193721,
    -0.5740904550326787, -0.5740904619694842, -0.574090458378136, -0.5740904408809406, -0.574090470162343, -0.5740905108192167, -0.5740904716665587,
    -0.5740904558481622, -0.5740904875948307, -0.5740904599033689, -0.5740904528357429, -0.5740905078992041, -0.574090461732248, -0.574090509249653,
    -0.5740904493480491, -0.5740905045697584, -0.5740904528357418, -0.5740904597254514, -0.5740904468061832, -0.5740905373574583, -0.5740904837213002,
    -0.5740904901313728, -0.5740904809130146, -0.5740906951703694, -0.5740904499800571, -0.5740904842494785, -0.5740904489064484, -0.5740904473813017,
    -0.5740904462292197, -0.5740904509915882, -0.574090581154483, -0.5740904509767019, -0.5740904466764553, -0.5740905179779201, 0.08522548533791707,
    2.490178730662951, 2.07216215002506, 0.8886664096464241, 0.6726757202331317, 1.584550393276248, 1.0201452981016919, 0.056228999044082455,
    -0.1786792597230069, 0.38808621596676324, 0.7583089130556834, 0.3207002396491483, 1.5122311308113299, 1.0816851559452978, -0.3056187881467284,
    -0.23203165905845957, 1.436317784464491, 1.3229427051484994, 0.6010025258907656, 0.23097297307792522, -0.06784533616938844, 1.549606051894303,
    1.2987117409527074, 0.03836300632571678, -0.21670946378121658, -0.3252608039781697, -0.43714301358266583, -0.41581933305276403, -0.40558827096449346,
    0.7576815204053328, 1.1645619316130649, 0.8567219991881373, 1.7645861350329979, 0.007938673685606622, -0.13725173672669716, -0.3838929376728968,
    -0.24096624278197118, -0.16406910824053847, -0.2857018768667053, -0.17511265032656853, -0.1499790766627377, -0.14672352387606974, -0.15255294289454102,
    -0.24347211646324657, 0.3320296654766363, 0.18330728646849537, 0.6493374609975638, 1.21837567441924, 0.1842182782318309, -0.42005925941285405,
    -0.40332710608992295, 1.034460905416852, 0.5420930411747646, -0.31245717851219623, 0.0018748548971931572, 0.1483746717200025, -0.44421938962508595,
    -0.2643951150417379, 0.042743022998055054, -0.12929745676446583, -0.33665426888865224, -0.3776570167879396, -0.3939669882459015, -0.21320298264173834,
    -0.2745651144213681, -0.518900484778015, -0.5471516602155396, -0.4423779372035856, -0.22810674606090495, -0.3342549720140231, -0.5410905664014172,
    -0.5694371498709956, -0.5672375854583545, -0.5627650102179304, -0.2153105770229587, -0.11973344284565499, -0.5006891581269763, -0.5504625258428515,
    -0.5661005935538914, -0.5631673961287892, -0.5699633443506442, -0.5679968002256757, -0.5508865872016985, -0.5628441163241702, -0.5595851044319549,
    -0.48981327421321447, -0.39063810920255937, -0.5341944869138014, -0.5373604557095845, -0.5300475871857316, -0.5698962774318795, -0.5685384240649802,
    -0.5639838987093317, -0.5367554915454533, -0.5358922722021361, -0.5448275845540286, -0.555950238620261, -0.5663360061603471, -0.2247485995793876,
    -0.36430437788183867, -0.18088812567861984, -0.15501783026103957, -0.5571992262420321, -0.5539682377334466, -0.556153905420149, -0.5665637142223063,
    -0.5701744751090553, -0.5708605009705402, -0.5648915148448509, -0.5478048813397287, -0.41377669624920654, -0.21373394904487739, -0.30270179495322014,
    -0.34005360358488146, -0.5020457561408982, -0.5245007507481545, -0.5196924982216186, -0.5222827537356519, -0.5216697080118965, -0.5212109086554176,
    -0.510929054482506, -0.5163529641391241, -0.5343973024459424, -0.556496323905755};
    */

int length = sizeof(inputList) / sizeof(inputList[0]);

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
ADC_HandleTypeDef hadc3;

QSPI_HandleTypeDef hqspi;

TIM_HandleTypeDef htim16;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC3_Init(void);
static void MX_TIM16_Init(void);
static void MX_QUADSPI_Init(void);
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
  MX_ADC3_Init();
  MX_TIM16_Init();
  MX_USB_DEVICE_Init();
  MX_QUADSPI_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_TIM_Base_Start(&htim16);

  while (1)
  {
	  if(counterOfTestData == 0) {
		  timestamp = htim16.Instance->CNT;
	  }

	  float input = (inputList[counterOfTestData] - 0.22330145150297734) * 2.5709241370783027;

	  const float features[] = { input };
	  int out = nevronskaMreza_jakostGibanja_predict(features, 1); // Alternative A: "inline"
	  if (out < 0) {
	      return out; // error
	  } else {
		  counterOfTestData++;
	  }

	  if(counterOfTestData == length) {
		  counterOfTestData=0;

		  countDurations++;

		  		uint32_t duration = htim16.Instance->CNT;

		  		if(duration >= timestamp)
		  			duration -= timestamp;
		  		else
		  			duration += (65535 - timestamp) + 1; //+1 because of counting from 0 onwards

		  		//snprintf(SendBuffer,BUFSIZE,"1 Trajanje izvajanja: %lu mikrosekund. \r\n", duration);
		  		//CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));
		  		averageDurationValue += duration;

		  		if(countDurations == numberOfDurations) {
		  			snprintf(SendBuffer,BUFSIZE,"Trajanje izvajanja: [%lu] %lu mikrosekund. \r\n", averageDurationValue, averageDurationValue / 100);
		  			CDC_Transmit_FS(SendBuffer,strlen(SendBuffer));

		  			countDurations = 0;
		  			averageDurationValue = 0;
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 22;
  RCC_OscInitStruct.PLL.PLLN = 169;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_0;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.Resolution = ADC_RESOLUTION_16B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc3.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc3.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_DIFFERENTIAL_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 255;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = 1;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 64 - 1;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 65535;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

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
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PI6 PI5 PI4 PI7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : FDCAN2_RX_Pin FDCAN2_TX_Pin */
  GPIO_InitStruct.Pin = FDCAN2_RX_Pin|FDCAN2_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PK5 PK4 PK6 PK3
                           PK7 PK2 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

  /*Configure GPIO pin : PG10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : SDIO1_D2_Pin SDIO1_D3_Pin SDIO1_CK_Pin SDIO1_D0_Pin
                           SDIO1_D1_Pin SDIO1_D7_Pin SDIO1_D6_Pin */
  GPIO_InitStruct.Pin = SDIO1_D2_Pin|SDIO1_D3_Pin|SDIO1_CK_Pin|SDIO1_D0_Pin
                          |SDIO1_D1_Pin|SDIO1_D7_Pin|SDIO1_D6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PI1 PI0 PI9 PI12
                           PI14 PI15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_9|GPIO_PIN_12
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : PE1 PE0 PE10 PE9
                           PE11 PE12 PE15 PE8
                           PE13 PE7 PE14 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_13|GPIO_PIN_7|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_SPI2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MII_TX_EN_Pin MII_TXD1_Pin MII_TXD0_Pin */
  GPIO_InitStruct.Pin = MII_TX_EN_Pin|MII_TXD1_Pin|MII_TXD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_DISP_Pin PJ14 PJ12 PJ13
                           PJ11 PJ10 PJ9 PJ0
                           PJ8 PJ7 PJ6 PJ1
                           PJ5 PJ3 PJ4 */
  GPIO_InitStruct.Pin = LCD_DISP_Pin|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_0
                          |GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1
                          |GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

  /*Configure GPIO pin : PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PI2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PH15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : FDCAN1_RX_Pin FDCAN1_TX_Pin */
  GPIO_InitStruct.Pin = FDCAN1_RX_Pin|FDCAN1_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : MII_TXD3_Pin */
  GPIO_InitStruct.Pin = MII_TXD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(MII_TXD3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_DISPD7_Pin */
  GPIO_InitStruct.Pin = LCD_DISPD7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_DISPD7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PE5 PE4 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI4;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : SDIO1_D5_Pin */
  GPIO_InitStruct.Pin = SDIO1_D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
  HAL_GPIO_Init(SDIO1_D5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PG15 PG8 PG5 PG4
                           PG0 PG1 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_5|GPIO_PIN_4
                          |GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : SDIO1_CMD_Pin */
  GPIO_InitStruct.Pin = SDIO1_CMD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
  HAL_GPIO_Init(SDIO1_CMD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD15 PD14
                           PD10 PD9 PD8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_14
                          |GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MII_RX_ER_Pin */
  GPIO_InitStruct.Pin = MII_RX_ER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(MII_RX_ER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PF2 PF1 PF0 PF3
                           PF5 PF4 PF13 PF14
                           PF12 PF15 PF11 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_3
                          |GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_INT_Pin */
  GPIO_InitStruct.Pin = LCD_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_BL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MII_MDC_Pin MII_TXD2_Pin MII_TX_CLK_Pin MII_RXD0_Pin
                           MII_RXD1_Pin */
  GPIO_InitStruct.Pin = MII_MDC_Pin|MII_TXD2_Pin|MII_TX_CLK_Pin|MII_RXD0_Pin
                          |MII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MII_CRS_Pin MII_COL_Pin */
  GPIO_InitStruct.Pin = MII_CRS_Pin|MII_COL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : MII_MDIO_Pin MII_RX_CLK_Pin MII_RX_DV_Pin */
  GPIO_InitStruct.Pin = MII_MDIO_Pin|MII_RX_CLK_Pin|MII_RX_DV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PH5 PH6 PH7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : VCP_TX_Pin VCP_RX_Pin */
  GPIO_InitStruct.Pin = VCP_TX_Pin|VCP_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS2_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS2_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS2_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_TIM13;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PH9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : MII_RX_D3_Pin MII_RX_D2_Pin */
  GPIO_InitStruct.Pin = MII_RX_D3_Pin|MII_RX_D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LD1_Pin */
  GPIO_InitStruct.Pin = LD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_OPEN);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA1, SYSCFG_SWITCH_PA1_OPEN);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
