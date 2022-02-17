/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <ADXL335.h>
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
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint64_t adc_conv_complete = RESET;

/* Variable to report ADC analog watchdog status:   */
/*   RESET <=> voltage into AWD window   */
/*   SET   <=> voltage out of AWD window */
uint8_t ubAnalogWatchdogStatus = RESET; /* Set into analog watchdog interrupt callback */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
//static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void adc_conv_complete_custom_cb(void);
void adc_awd_custom_cb(void);
void debug_console_log(char *debug_msg);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	//uint8_t debug_buf[100];
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
	adxl335_init();
	//MX_USART2_UART_Init();
//	MX_ADC_Init(1000, 3000);
//	/* USER CODE BEGIN 2 */
//	adc_reg_awd_callback(adc_awd_custom_cb, adc_conv_complete_custom_cb);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
//		if (adc_conv_complete == SET) {
//			sprintf((char*) debug_buf, "adc val = %ld\r\n",
//					HAL_ADC_GetValue(&hadc));
//			debug_console_log((char*) debug_buf);
//		} else {
//			//debug_console_log("ADC Conv not complete\r\n");
//		}
//
//		if (ubAnalogWatchdogStatus == RESET) {
//			HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
//		} else {
//			HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET);
//		}
//
//		adc_conv_complete = RESET;
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE
			| RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}



///**
// * @brief USART2 Initialization Function
// * @param None
// * @retval None
// */
//static void MX_USART2_UART_Init(void) {
//
//	/* USER CODE BEGIN USART2_Init 0 */
//
//	/* USER CODE END USART2_Init 0 */
//
//	/* USER CODE BEGIN USART2_Init 1 */
//
//	/* USER CODE END USART2_Init 1 */
//	huart2.Instance = USART2;
//	huart2.Init.BaudRate = 115200;
//	huart2.Init.WordLength = UART_WORDLENGTH_8B;
//	huart2.Init.StopBits = UART_STOPBITS_1;
//	huart2.Init.Parity = UART_PARITY_NONE;
//	huart2.Init.Mode = UART_MODE_TX_RX;
//	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
//	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
//	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//	if (HAL_UART_Init(&huart2) != HAL_OK) {
//		Error_Handler();
//	}
//	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8)
//			!= HAL_OK) {
//		Error_Handler();
//	}
//	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8)
//			!= HAL_OK) {
//		Error_Handler();
//	}
//	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK) {
//		Error_Handler();
//	}
//	/* USER CODE BEGIN USART2_Init 2 */
//
//	/* USER CODE END USART2_Init 2 */
//
//}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LED1_Pin | LED2_Pin | LED3_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, FE_CTRL3_Pin | FE_CTRL2_Pin | FE_CTRL1_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin */
	GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin | LED3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : FE_CTRL3_Pin FE_CTRL2_Pin FE_CTRL1_Pin */
	GPIO_InitStruct.Pin = FE_CTRL3_Pin | FE_CTRL2_Pin | FE_CTRL1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : B1_Pin B2_Pin */
	GPIO_InitStruct.Pin = B1_Pin | B2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : B3_Pin */
	GPIO_InitStruct.Pin = B3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(B3_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

///**
// * @brief  ADC Conversion complete custom callback
// * @param  None.
// * @retval None
// */
//void adc_conv_complete_custom_cb(void) {
//	adc_conv_complete = SET;
//	ubAnalogWatchdogStatus = RESET;
//}
//
///**
// * @brief  ADC watchdog custom callback
// * @param  None
// * @retval None
// */
//void adc_awd_custom_cb(void) {
//	/* Set variable to report analog watchdog out of window status to main      */
//	/* program.                                                                 */
//	ubAnalogWatchdogStatus = SET;
//}
//
//void debug_console_log(char *debug_msg) {
//	uint8_t debug_buf[100];
//	strcpy((char*) debug_buf, debug_msg);
//	HAL_UART_Transmit(&huart2, debug_buf, strlen((char*) debug_buf), 1000);
//}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

