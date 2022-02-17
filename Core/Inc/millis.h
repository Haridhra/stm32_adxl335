/*
 * millis.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Harid
 */

#ifndef INC_MILLIS_H_
#define INC_MILLIS_H_

#include <stm32wlxx_hal.h>

uint32_t millis (void);
void delay_ms (uint32_t delay);

#endif /* INC_MILLIS_H_ */
