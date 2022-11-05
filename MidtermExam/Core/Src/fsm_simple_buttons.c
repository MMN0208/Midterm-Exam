/*
 * fsm_simple_buttons.c
 *
 *  Created on: Nov 5, 2022
 *      Author: nhatmai
 */

#include "fsm_simple_buttons.h"

#define RESET_BTN		0
#define INC_BTN			1
#define DEC_BTN			2

#define IDLE_TIME		10000 // 10s idle time
#define AUTO_CHANGE		1000  // inc/dec counter every 1s when button is hold for >= 3s

void fsm_simple_buttons_run(void) {
	switch(status) {
	case INIT:
		// Initialize all software timers
		setTimer1(SYSTEM_DELAY);
		setTimer2(SYSTEM_DELAY + 1);

		resetBuffer();
		display7SEG();

		if(is_button_pressed(RESET_BTN)) {
			resetBuffer();
			display7SEG();
		}

		if(is_button_pressed(INC_BTN)) {
			setTimer3(IDLE_TIME);
			status = INC;
			increaseBuffer();
			display7SEG();
		}

		if(is_button_pressed(DEC_BTN)) {
			setTimer3(IDLE_TIME);
			status = DEC;
			decreaseBuffer();
			display7SEG();
		}
		break;

	case INC:
		if(is_button_pressed(INC_BTN)) {
			setTimer3(IDLE_TIME);
			increaseBuffer();
			display7SEG();
		}

		if(timer1_flag == 1 && is_button_hold(INC_BTN)) {
			setTimer1(AUTO_CHANGE);
			increaseBuffer();
			display7SEG();
		}

		if(timer1_flag == 1 &&  !is_button_hold(INC_BTN)) {
			setTimer3(IDLE_TIME);
		}

		if(is_button_pressed(RESET_BTN)) {
			resetBuffer();
			display7SEG();
		}

		if(is_button_pressed(DEC_BTN)) {
			setTimer3(IDLE_TIME);
			status = DEC;
			decreaseBuffer();
			display7SEG();
		}

		if(timer3_flag == 1) {
			setTimer3(AUTO_CHANGE);
			status = AUTO;
			countdownBuffer();
			display7SEG();
		}
		break;

	case DEC:
		if(is_button_pressed(DEC_BTN)) {
			setTimer3(IDLE_TIME);
			decreaseBuffer();
			display7SEG();
		}

		if(timer1_flag == 1 && is_button_hold(DEC_BTN)) {
			setTimer1(AUTO_CHANGE);
			decreaseBuffer();
			display7SEG();
		}

		if(timer1_flag == 1 && is_button_hold(DEC_BTN)) {
			setTimer1(AUTO_CHANGE);
			decreaseBuffer();
			display7SEG();
		}

		if(timer1_flag == 1 &&  !is_button_hold(DEC_BTN)) {
			setTimer3(IDLE_TIME);
		}

		if(is_button_pressed(RESET_BTN)) {
			resetBuffer();
			display7SEG();
		}

		if(is_button_pressed(INC_BTN)) {
			setTimer3(IDLE_TIME);
			status = INC;
			increaseBuffer();
			display7SEG();
		}

		if(timer3_flag == 1) {
			setTimer3(AUTO_CHANGE);
			status = AUTO;
			countdownBuffer();
			display7SEG();
		}
		break;

	case AUTO:
		if(timer3_flag == 1) {
			setTimer3(AUTO_CHANGE);
			countdownBuffer();
			display7SEG();
		}

		if(is_button_pressed(RESET_BTN)) {
			resetBuffer();
			display7SEG();
		}

		if(is_button_pressed(INC_BTN)) {
			setTimer3(IDLE_TIME);
			status = INC;
			increaseBuffer();
			display7SEG();
		}

		if(is_button_pressed(DEC_BTN)) {
			setTimer3(IDLE_TIME);
			status = DEC;
			decreaseBuffer();
			display7SEG();
		}
		break;

	default: break;
	}
}
