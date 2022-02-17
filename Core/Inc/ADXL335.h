/*
 * ADXL335.h
 *
 *  Created on: Jan 16, 2022
 *      Author: Harid
 */

#ifndef INC_ADXL335_H_
#define INC_ADXL335_H_

#include <stm32l4_adc.h>
#include <millis.h>
//#ifndef NDEBUG
#include <stm32_uart_console.h>
uint8_t debug_buf[30];
//#endif

#define ACCELEROMETER_XAXIS ADC_CHANNEL_1
#define ACCELEROMETER_YAXIS ADC_CHANNEL_0
#define ACCELEROMETER_ZAXIS ADC_CHANNEL_2

enum mold_state {
	MoldOpening, MoldOpen, MoldClosed, MoldClosing
};

enum accel_dir {
	Forward, Backward, None
};

/* Function Pointer to Mold Open callback */
typedef void (*MoldOpeningCb_t)(void);
/* Function Pointer to Mold Open callback */
typedef void (*MoldClosedCb_t)(void);

void adxl335_init(void);
void adxl355_deinit(void);
void check_accel_dir(void);
void register_mold_state_cb(MoldOpeningCb_t open_cb,MoldClosedCb_t closed_cb);
void adc_conv_complete_custom_cb(void);
enum mold_state get_mold_state(void);
void set_fw_accel_trigger(int16_t);
void set_bw_accel_trigger(int16_t);
void set_accel_interval(uint16_t);

#endif /* INC_ADXL335_H_ */
