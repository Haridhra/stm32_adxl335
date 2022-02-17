/*
 * stm32l4_adc.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Harid
 */

#ifndef INC_STM32L4_ADC_H_
#define INC_STM32L4_ADC_H_

#include <stm32wlxx_hal.h>

/* Function Pointer to Mold Open callback */
typedef void (*adc_awd_callback_t)(void);
typedef void (*adc_conv_complete_callback_t)(void);

void MX_ADC_Init(uint16_t low_thresh, uint16_t high_thresh);
void ADC_DeInit(void);
void adc_reg_awd_callback(adc_awd_callback_t adc_awd_cb, adc_conv_complete_callback_t adc_conv_cb);
uint16_t adc_get_result(void);

/* ADC Interrupt callbacks */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

#endif /* INC_STM32L4_ADC_H_ */
