/*
 * seven_seg_processing.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ADMIN
 */

#include "seven_seg_processing.h"

#define NO_OF_SEGMENTS	7
#define NO_OF_VALUES 	10

#define SECOND 			1000 // 1s = 1000ms

#define FIRST_ELEM		0
#define SECOND_ELEM		1
#define	THIRD_ELEM		2
#define FOURTH_ELEM		3

//seven segment ports and pins
GPIO_TypeDef * sevenSegPort[NO_OF_SEGMENTS] = {
	SEG0_GPIO_Port,
	SEG1_GPIO_Port,
	SEG2_GPIO_Port,
	SEG3_GPIO_Port,
	SEG4_GPIO_Port,
	SEG5_GPIO_Port,
	SEG6_GPIO_Port
};

uint16_t sevenSegPin[NO_OF_SEGMENTS] = {
	SEG0_Pin,
	SEG1_Pin,
	SEG2_Pin,
	SEG3_Pin,
	SEG4_Pin,
	SEG5_Pin,
	SEG6_Pin
};

//enable ports and pins
GPIO_TypeDef * enablePort[MAX_7SEG_LEDS] = {
	EN0_GPIO_Port,
	EN1_GPIO_Port,
	EN2_GPIO_Port,
	EN3_GPIO_Port
};

uint16_t enablePin[MAX_7SEG_LEDS] = {
	EN0_Pin,
	EN1_Pin,
	EN2_Pin,
	EN3_Pin
};

//seven segment display
const uint8_t sevenSegValue[NO_OF_VALUES] = {
	0x40, // 0
	0x79, // 1
	0x24, // 2
	0x30, // 3
	0x19, // 4
	0x12, // 5
	0x02, // 6
	0x78, // 7
	0x00, // 8
	0x10, // 9
};

//seven segment enable
const uint8_t sevenSegEnable[MAX_7SEG_LEDS] = {
	0x0e, // EN0
	0x0d, // EN1
	0x0b, // EN2
	0x07  // EN3
};

//seven segment buffer
int seven_seg_buffer[MAX_7SEG_LEDS];
int seven_seg_index = 0;

//seven segment functions
void driver7SEG(int num) {
	if(num < 0 || num > 9) return;
	for(int i = 0; i < NO_OF_SEGMENTS; i++) {
		HAL_GPIO_WritePin(sevenSegPort[i], sevenSegPin[i], (sevenSegValue[num] >> i) & 0x01);
	}
}

void enable7SEG(int index) {
	if(index < 0 || index >= MAX_7SEG_LEDS) return;
	for(int i = 0; i < MAX_7SEG_LEDS; i++) {
		HAL_GPIO_WritePin(enablePort[i], enablePin[i], (sevenSegEnable[index] >> i) & 0x01);
	}
}

void updateCountdownBuffer(void) {
	seven_seg_buffer[FIRST_ELEM] = getCountdown(SOUTH_NORTH) / 10;
	seven_seg_buffer[SECOND_ELEM] = getCountdown(SOUTH_NORTH) % 10;
	seven_seg_buffer[THIRD_ELEM] = getCountdown(EAST_WEST) / 10;
	seven_seg_buffer[FOURTH_ELEM] = getCountdown(EAST_WEST) % 10;
}

void updateTimeBuffer(int time) {
	seven_seg_buffer[FIRST_ELEM] = time / 10;
	seven_seg_buffer[SECOND_ELEM] = time % 10;
}

void updateModeBuffer(int mode) {
	seven_seg_buffer[THIRD_ELEM] = mode / 10;
	seven_seg_buffer[FOURTH_ELEM] = mode % 10;
}

void display7SEG(int index) {
	if(index < 0 || index >= MAX_7SEG_LEDS) return;
	enable7SEG(index);
	driver7SEG(seven_seg_buffer[index]);
}

void scan7SEG(void) {
	if(timer1_flag == 1) {
		setTimer1(LED_SCAN_PERIOD);
		display7SEG(seven_seg_index++);
		seven_seg_index %= MAX_7SEG_LEDS;
	}
}

void reset7SEGIndex(void){
	seven_seg_index = 0;
}
