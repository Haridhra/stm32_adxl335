/*
 * ADXL335.c
 *
 *  Created on: Jan 16, 2022
 *      Author: Harid
 */

#include <ADXL335.h>

enum mold_state mold = MoldClosed;
enum accel_dir prevAccDir = None;
enum accel_dir currAccDir = None;

uint16_t yRaw = 0;

uint16_t xRawMin = 390;
uint16_t xRawMax = 604;

//uint16_t yRawMin = 394;
//uint16_t yRawMax = 602;
uint16_t yRawMin = 400;
uint16_t yRawMax = 600;

uint16_t zRawMin = 406;
uint16_t zRawMax = 604;

uint32_t lastAccTime = 0;
uint16_t accInterval = 800;

int16_t fw_trig = 200;
int16_t bw_trig = -200;
uint8_t adc_trig_offset = 0;

MoldOpeningCb_t moldOpening_cb;
MoldClosedCb_t moldClosed_cb;

/**
 *	Map - mapValue, minInp, maxInp, minOut, maxOut
 */
static int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min,
		int32_t out_max) {
	return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

/**
 *	ADC Analog Watchdog Callback - Called when window condition is met
 */
void check_accel_dir(void) {
//#ifndef NDEBUG
	//debug_console_log("Acceleration Detected!\r\n");
//#endif
	if (millis() - lastAccTime >= accInterval) {
		yRaw = adc_get_result();
		int32_t yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);
		if (yScaled > fw_trig) {
//#ifndef NDEBUG
			sprintf((char*) debug_buf, "Forward acceleration! = %ld\r\n",
					yScaled);
			debug_console_log((char*) debug_buf);
//#endif
			currAccDir = Forward;
			lastAccTime = millis();
		} else if (yScaled < bw_trig) {
//#ifndef NDEBUG
			sprintf((char*) debug_buf, "Backward acceleration! = %ld\r\n",
					yScaled);
			debug_console_log((char*) debug_buf);
//#endif
			currAccDir = Backward;
			lastAccTime = millis();
		}

		if ((mold == MoldOpen) && (currAccDir == Forward)) {
//#ifndef NDEBUG
			debug_console_log("Mold Closing\r\n");
//#endif
			mold = MoldClosing;
			currAccDir = None;
		} else if ((mold == MoldClosing) && (currAccDir == Backward)) {
			mold = MoldClosed;
			currAccDir = None;
			debug_console_log("Mold Closed\r\n");
			//(*moldClosed_cb)();
		} else if ((mold == MoldClosed) && (currAccDir == Backward)) {
			mold = MoldOpening;
			currAccDir = None;
			//(*moldOpening_cb)();
			debug_console_log("Mold Opening\r\n");
		} else if ((mold == MoldOpening) && (currAccDir == Forward)) {
//#ifndef NDEBUG
			debug_console_log("Mold Open\r\n");
//#endif
			mold = MoldOpen;
			currAccDir = None;
		}
		prevAccDir = currAccDir;
	}
}

/**
 * @brief  ADC Conversion complete custom callback
 * @param  None.
 * @retval None
 */
void adc_conv_complete_custom_cb(void) {
//#ifndef NDEBUG
	//sprintf((char*) debug_buf, "adc val = %d\r\n", adc_get_result());
	//debug_console_log((char*) debug_buf);
//#endif
}

void adxl335_init(void) {
	uint16_t fw_trig_mapped = map(fw_trig, -1000, 1000, yRawMin, yRawMax)
			+ adc_trig_offset;
	uint16_t bw_trig_mapped = map(bw_trig, -1000, 1000, yRawMin, yRawMax)
			+ adc_trig_offset;
	MX_ADC_Init(bw_trig_mapped, fw_trig_mapped);
	adc_reg_awd_callback(check_accel_dir, adc_conv_complete_custom_cb);
//#ifndef NDEBUG
	MX_USART2_UART_Init();
	debug_console_log("ADC Init Complete\r\n");
//#endif
}

void adxl355_deinit(void) {
	ADC_DeInit();
}

void register_mold_state_cb(MoldOpeningCb_t open_cb, MoldClosedCb_t closed_cb) {
	moldOpening_cb = open_cb;
	moldClosed_cb = closed_cb;
}

enum mold_state get_mold_state(void) {
	return mold;
}

void set_fw_accel_trigger(int16_t newTrigger) {
	fw_trig = newTrigger;
	adxl355_deinit();
	adxl335_init();
}

void set_bw_accel_trigger(int16_t newTrigger) {
	bw_trig = newTrigger;
	adxl355_deinit();
	adxl335_init();
}

void set_accel_interval(uint16_t newInterval) {
	accInterval = newInterval;
}
