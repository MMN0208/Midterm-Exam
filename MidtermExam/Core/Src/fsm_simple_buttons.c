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
		setTimer3(IDLE_TIME);

		resetBuffer();
		status = WAIT;
		break;

	case WAIT:
		display7SEG();

		if(is_button_pressed(RESET_BTN)) {
			status = RST;
		}

		if(is_button_pressed(INC_BTN)) {
			status = INC;
		}

		if(is_button_hold(INC_BTN)) {
			setTimer3(0);
			status = LONG_INC;
		}

		if(is_button_pressed(DEC_BTN)) {
			status = DEC;
		}

		if(is_button_hold(DEC_BTN)) {
			status = LONG_DEC;
		}

		if(timer3_flag == 1) {
			setTimer3(AUTO_CHANGE);
			status = AUTO;
			countdownBuffer();
			display7SEG();
		}
		break;

	case RST:
		setTimer3(IDLE_TIME);
		resetBuffer();
		status = WAIT;
		break;

	case INC:
		setTimer3(IDLE_TIME);
		increaseBuffer();
		status = WAIT;
		break;

	case DEC:
		setTimer3(IDLE_TIME);
		decreaseBuffer();
		status = WAIT;
		break;

	case LONG_INC:
		if(timer1_flag == 1 && is_button_hold(INC_BTN)) {
			setTimer1(AUTO_CHANGE);
			increaseBuffer();
			display7SEG();
		}

		if(!is_button_hold(INC_BTN)) {
			setTimer3(IDLE_TIME);
			status = WAIT;
		}
		break;

	case LONG_DEC:
		if(timer1_flag == 1 && is_button_hold(DEC_BTN)) {
			setTimer1(AUTO_CHANGE);
			decreaseBuffer();
			display7SEG();
		}

		if(!is_button_hold(DEC_BTN)) {
			setTimer3(IDLE_TIME);
			status = WAIT;
		}
		break;

	case AUTO:
		if(timer3_flag == 1) {
			setTimer3(AUTO_CHANGE);
			countdownBuffer();
			display7SEG();
		}

		if(is_button_pressed(RESET_BTN)) {
			status = RST;
		}

		if(is_button_pressed(INC_BTN)) {
			status = INC;
		}

		if(is_button_pressed(DEC_BTN)) {
			status = DEC;
		}
		break;

	default: break;
	}
}
