/*
 * millis.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Harid
 */

#include <millis.h>

uint32_t millis(void) {
	return HAL_GetTick();
}

void delay_ms(uint32_t delay) {
	return HAL_Delay(delay);
}

