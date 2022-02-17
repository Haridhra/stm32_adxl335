/*
 * stm32_uart_console.h
 *
 *  Created on: Feb 7, 2022
 *      Author: Harid
 */

#ifndef INC_STM32_UART_CONSOLE_H_
#define INC_STM32_UART_CONSOLE_H_

#include <stm32wlxx_hal.h>
#include <stdio.h>
#include <string.h>

void MX_USART2_UART_Init(void);
void debug_console_log(char * debug_msg);
void debug_test(char * msg);

#endif /* INC_STM32_UART_CONSOLE_H_ */
