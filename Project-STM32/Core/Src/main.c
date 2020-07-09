/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BMP280/bmp280.h"
#include "Led.h"
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
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

BMP280_HandleTypedef bmp280;

float pressure, temperature, humidity;

uint16_t size;
uint8_t Data[512] = {0};
uint16_t size_r = 1;
uint8_t Data_r[512] = {0};
uint16_t i = 0;
char Data_rx[1] = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*huart){
	if(huart->Instance == USART2){
		Data_r[i] = Data_rx[0];
		i++;
		HAL_UART_Receive_IT(&huart2, Data_rx, size_r);
	}
}

void ESP_Init(){

	size = sprintf(Data, "AT\r\n");
		HAL_UART_Transmit_IT(&huart2, Data, size);
		HAL_Delay(500);
		size = sprintf(Data, Data_r);
		HAL_UART_Transmit_IT(&huart3, Data, size);
		i = 0;
		for(int k = 0; k < 256; k++) Data_r[k] = 0;
		HAL_Delay(500);

		size = sprintf(Data, "AT+CWMODE?\r\n");
		HAL_UART_Transmit_IT(&huart2, Data, size);
		HAL_Delay(500);
		size = sprintf(Data, Data_r);
		HAL_UART_Transmit_IT(&huart3, Data, size);
		i = 0;
		for(int k = 0; k < 256; k++) Data_r[k] = 0;
		HAL_Delay(500);

		size = sprintf(Data, "AT+CWJAP?\r\n");
		HAL_UART_Transmit_IT(&huart2, Data, size);
		HAL_Delay(500);
		size = sprintf(Data, Data_r);
		HAL_UART_Transmit_IT(&huart3, Data, size);
		i = 0;
		for(int k = 0; k < 256; k++) Data_r[k] = 0;
		HAL_Delay(500);

		size = sprintf(Data, "AT+CWSAP_CUR=\"STM\",\"testtymczasowy\",1,4\r\n");
			HAL_UART_Transmit_IT(&huart2, Data, size);
			HAL_Delay(500);
			size = sprintf(Data, Data_r);
			HAL_UART_Transmit_IT(&huart3, Data, size);
			i = 0;
			for(int k = 0; k < 256; k++) Data_r[k] = 0;
			HAL_Delay(500);

		size = sprintf(Data, "AT+CIPMODE=0\r\n");
			HAL_UART_Transmit_IT(&huart2, Data, size);
			HAL_Delay(500);
			size = sprintf(Data, Data_r);
			HAL_UART_Transmit_IT(&huart3, Data, size);
			i = 0;
			for(int k = 0; k < 256; k++) Data_r[k] = 0;
			HAL_Delay(500);

			size = sprintf(Data, "AT+CIPMUX=1\r\n");
				HAL_UART_Transmit_IT(&huart2, Data, size);
				HAL_Delay(500);
				size = sprintf(Data, Data_r);
				HAL_UART_Transmit_IT(&huart3, Data, size);
				i = 0;
				for(int k = 0; k < 256; k++) Data_r[k] = 0;
				HAL_Delay(500);

			size = sprintf(Data, "AT+CIPSERVER=1,8080\r\n");
				HAL_UART_Transmit_IT(&huart2, Data, size);
				HAL_Delay(500);
				size = sprintf(Data, Data_r);
				HAL_UART_Transmit_IT(&huart3, Data, size);
				i = 0;
				for(int k = 0; k < 256; k++) Data_r[k] = 0;
				HAL_Delay(500);
}

void ESP_SendData()
{
	bmp280_read_float(&bmp280, &temperature, &pressure, &humidity);

			size = sprintf((char *)Data,"Temperature: %.2f C \n\r",temperature);
						HAL_UART_Transmit_IT(&huart3, Data, size);
						HAL_Delay(10);
			size = sprintf((char *)Data,"Pressure: %.2f Pa \n\r",pressure);
						HAL_UART_Transmit_IT(&huart3, Data, size);
						HAL_Delay(10);
			size = sprintf((char *)Data,"Humidity: %.2f\n\r\n\r", humidity);
						HAL_UART_Transmit_IT(&huart3, Data, size);
						HAL_Delay(10);

	size = sprintf(Data, "AT+CIPSTART=0,\"TCP\",\"164.132.104.58\",8080\r\n");
				HAL_UART_Transmit_IT(&huart2, Data, size);
				HAL_Delay(200);
				size = sprintf(Data, Data_r);
				HAL_UART_Transmit_IT(&huart3, Data, size);
				i = 0;
				for(int k = 0; k < 256; k++) Data_r[k] = 0;
				HAL_Delay(200);

				char aszJsonData[150] = {0};
				sprintf(aszJsonData,"{\"temperature\":\"%.2f\",\"pressure\":\"%.2f\",\"humidity\":\"%.2f\"}",temperature,pressure,humidity);
				char aszJsonRequest[250] = { 0 };
				char aszServiceMethod[] = "/STM/putStmData";
				char aszRequest[150] = { 0 };
				char aszHostIp[30] = "164.132.104.58";
				char aszPort[] = "8080";
				uint16_t size_temp = 0;
				sprintf(aszRequest,"http://%s:%s%s HTTP/1.1",aszHostIp,aszPort,aszServiceMethod);
				strcat(aszHostIp, ":");
				strcat(aszHostIp, aszPort);
				size_temp = sprintf(aszJsonRequest, "PUT %s\r\nHost: %s\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s\r\n",
						aszRequest, aszHostIp, strlen(aszJsonData), aszJsonData);

	size = sprintf(Data, "AT+CIPSEND=0,%d\r\n",size_temp);
				HAL_UART_Transmit_IT(&huart2, Data, size);
				HAL_Delay(200);

				HAL_UART_Transmit_IT(&huart2, aszJsonRequest, size_temp);
				HAL_Delay(200);

				size = sprintf(Data, Data_r);
				HAL_UART_Transmit_IT(&huart3, Data, size);
				i = 0;
				for(int k = 0; k < 256; k++) Data_r[k] = 0;
				HAL_Delay(200);

	size = sprintf(Data, "AT+CIPCLOSE=0\r\n");
				HAL_UART_Transmit_IT(&huart2, Data, size);
				HAL_Delay(200);
				size = sprintf(Data, Data_r);
				HAL_UART_Transmit_IT(&huart3, Data, size);
				i = 0;
				for(int k = 0; k < 256; k++) Data_r[k] = 0;
				HAL_Delay(200);

					open();

					size = sprintf(Data,"%.2f 'C %.1f hPa %.2f %%",temperature,pressure,humidity);
					showMessage(Data,size);
					HAL_Delay(30*(size+1));
					close();
}
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
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = &hi2c1;

	while (!bmp280_init(&bmp280, &bmp280.params)) {
		size = sprintf((char *)Data, "BMP280 initialization failed\n\r");
		HAL_UART_Transmit_IT(&huart3, Data, size);
		HAL_Delay(2000);
	}
	bool bme280p = bmp280.id == BME280_CHIP_ID;
	size = sprintf((char *)Data, "BMP280: found %s\n\r", bme280p ? "BME280" : "BMP280");
	HAL_UART_Receive_IT(&huart2, Data_rx, size_r);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	ESP_Init();
	max_init(&hspi1);
	open();
	orientate(90,0);
	close();

	while (1) {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		/*HAL_Delay(100);
		while (!bmp280_read_float(&bmp280, &temperature, &pressure, &humidity)) {
			size = sprintf((char *)Data,
					"Temperature/pressure reading failed\n\r");
			HAL_UART_Transmit_IT(&huart3, Data, size);
			HAL_Delay(2000);
		}
		size = sprintf((char *)Data,"Temperature: %.2f C \n\r",temperature);
		HAL_UART_Transmit_IT(&huart3, Data, size);
		HAL_Delay(1000);
		size = sprintf((char *)Data,"Pressure: %.2f Pa \n\r",pressure);
				HAL_UART_Transmit_IT(&huart3, Data, size);
		HAL_Delay(1000);
		if (bme280p) {
			size = sprintf((char *)Data,"Humidity: %.2f\n\r\n\r", humidity);
			HAL_UART_Transmit_IT(&huart3, Data, size);
		}
		else {
			size = sprintf((char *)Data, "\n\r");
			HAL_UART_Transmit_IT(&huart3, Data, size);
		}*/
		ESP_SendData();
		HAL_Delay(2000);


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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 41999;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 2199;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD3_Pin */
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

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
	while (1) {
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
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
