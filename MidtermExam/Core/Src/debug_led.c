/*
 * debug_led.c
 *
 *  Created on: Nov 5, 2022
 *      Author: nhatmai
 */

#include "debug_led.h"

#define BLINK_PERIOD	1000 // 1s

void led_blinky(void) {
	if(timer2_flag == 1) {
		setTimer2(BLINK_PERIOD);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}
}
