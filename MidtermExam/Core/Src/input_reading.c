/*
 * input_reading.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ADMIN
 */
#include "input_reading.h"
//we aim to work with more than one buttons
#define NO_OF_BUTTONS 				       3
//time to register hold
#define DURATION_FOR_BUTTON_HOLD		   3000
//time interval inbetween each press to detect double press
#define DURATION_FOR_DOUBLE_PRESS		   200
#define BUTTON_IS_PRESSED                  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED                 GPIO_PIN_SET
//the buffer that the final result is stored after

//button ports and pins array
GPIO_TypeDef * buttonPort[NO_OF_BUTTONS] = {
	RESET_GPIO_Port,
	INC_GPIO_Port,
	DEC_GPIO_Port
};

uint16_t buttonPin[NO_OF_BUTTONS] = {
	RESET_Pin,
	INC_Pin,
	DEC_Pin
};

//debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
//we define three buffers for debouncing
static GPIO_PinState debounceButtonBuffer0[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
//we define a flag for a button pressed more than 1 second.
static uint8_t flagForButtonPressed[NO_OF_BUTTONS];
static uint8_t flagForButtonDoublePressed[NO_OF_BUTTONS];
static uint8_t flagForButtonHold[NO_OF_BUTTONS];
//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
static uint16_t counterForButtonHold[NO_OF_BUTTONS] = {0, 0, 0};
static uint16_t waitForSecondPress[NO_OF_BUTTONS] = {0, 0, 0};

void button_reading(void){
	for(int i = 0; i < NO_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = debounceButtonBuffer0[i];
		debounceButtonBuffer0[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
		if((debounceButtonBuffer2[i] == debounceButtonBuffer1[i]) || (debounceButtonBuffer1[i] == debounceButtonBuffer0[i])) {
			if(buttonBuffer[i] != debounceButtonBuffer0[i]) {
				buttonBuffer[i] = debounceButtonBuffer0[i];
				if(buttonBuffer[i] == BUTTON_IS_PRESSED) {
					counterForButtonHold[i] = DURATION_FOR_BUTTON_HOLD;
					if(SYSTEM_DELAY > 0) counterForButtonHold[i] /= SYSTEM_DELAY;

					flagForButtonPressed[i] = 1;
				}
				else {
					flagForButtonHold[i] = 0;
				}
			}
			else {
				if(buttonBuffer[i] == BUTTON_IS_PRESSED) {
					counterForButtonHold[i]--;
					if(counterForButtonHold[i] == 0) {
						flagForButtonHold[i] = 1;
					}
				}
			}
		}
	}
}

int is_button_pressed(int index) {
	if(index < 0 || index > NO_OF_BUTTONS) return 0;
	if(flagForButtonPressed[index] == 1) {
		flagForButtonPressed[index] = 0;
		return 1;
	}
	return 0;
}

int is_button_hold(int index) {
	if(index < 0 || index > NO_OF_BUTTONS) return 0;
	if(flagForButtonHold[index] == 1) {
		return 1;
	}
	return 0;
}
