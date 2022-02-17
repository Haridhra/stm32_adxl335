/*
 * stm32l4_adc.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Harid
 */

#include <stm32l4_adc.h>

/* Private variables ---------------------------------------------------------*/

ADC_HandleTypeDef hadc;
HAL_StatusTypeDef ret;

adc_awd_callback_t adc_awd_cb;
adc_conv_complete_callback_t adc_conv_cb;

// TODO: Add error logs to error handler function
/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
static void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

/**
 * @brief ADC Initialization Function
 * @param None
 * @retval None
 */
void MX_ADC_Init(uint16_t low_thresh, uint16_t high_thresh) {

	/* USER CODE BEGIN ADC_Init 0 */

	/* USER CODE END ADC_Init 0 */

	ADC_AnalogWDGConfTypeDef AnalogWDGConfig = { 0 };
	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC_Init 1 */

	/* USER CODE END ADC_Init 1 */
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc.Instance = ADC;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_10B;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.LowPowerAutoPowerOff = DISABLE;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	hadc.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_160CYCLES_5;
	hadc.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_160CYCLES_5;
	hadc.Init.OversamplingMode = DISABLE;
	hadc.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_LOW;
	if (HAL_ADC_Init(&hadc) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Analog WatchDog 1
	 */
	AnalogWDGConfig.WatchdogNumber = ADC_ANALOGWATCHDOG_1;
	AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_SINGLE_REG;
	AnalogWDGConfig.Channel = ADC_CHANNEL_0;
	AnalogWDGConfig.ITMode = ENABLE;
	//TODO: Change hardcoded thresholds back to vars
	AnalogWDGConfig.HighThreshold = high_thresh;
	AnalogWDGConfig.LowThreshold = low_thresh;
	if (HAL_ADC_AnalogWDGConfig(&hadc, &AnalogWDGConfig) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC_Init 2 */
	if (HAL_ADC_Start_IT(&hadc) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE END ADC_Init 2 */

}

/**
 * @brief  Conversion complete callback in non blocking mode
 * @param  AdcHandle : ADC handle
 * @note   This example shows a simple way to report end of conversion
 *         and get conversion result. You can add your own implementation.
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	(*adc_conv_cb)();
}

/**
 * @brief  Analog watchdog callback in non blocking mode.
 * @param  hadc: ADC handle
 * @retval None
 */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc) {
	(*adc_awd_cb)();
}

/**
 * @brief  ADC error callback in non blocking mode
 *        (ADC conversion with interruption or transfer by DMA)
 * @param  hadc: ADC handle
 * @retval None
 */
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc) {
	/* In case of ADC error, call main error handler */
	Error_Handler();
}

/**
 *	Get ADC result - Start conversion, wait for completion and return result
 */
uint16_t adc_get_result(void) {
	uint16_t result = HAL_ADC_GetValue(&hadc);
	return result;
}

/**
 *	Register external adc watchdog callback
 */
void adc_reg_awd_callback(adc_awd_callback_t awd_cb, adc_conv_complete_callback_t conv_cb) {
	adc_awd_cb = awd_cb;
	adc_conv_cb = conv_cb;
}

/**
 *	ADC De-initialize
 */
// TODO: verify de-init procedure --> enable ADC clock?
void ADC_DeInit(void) {
	__HAL_RCC_ADC_CLK_DISABLE();
	HAL_ADC_DeInit(&hadc);
	__HAL_RCC_ADC_CLK_ENABLE();
}

