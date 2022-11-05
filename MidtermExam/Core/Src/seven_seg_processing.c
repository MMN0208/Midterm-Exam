/*
 * seven_seg_processing.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ADMIN
 */

#include "seven_seg_processing.h"

#define NO_OF_SEGMENTS	7
#define NO_OF_VALUES 	10
#define MAX_VALUE		10

#define SECOND 			1000 // 1s = 1000ms

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

//seven segment buffer
int seven_seg_buffer;

//seven segment functions
void driver7SEG(int num) {
	if(num < 0 || num > 9) return;
	for(int i = 0; i < NO_OF_SEGMENTS; i++) {
		HAL_GPIO_WritePin(sevenSegPort[i], sevenSegPin[i], (sevenSegValue[num] >> i) & 0x01);
	}
}

void resetBuffer(void) {
	seven_seg_buffer = 0;
}

void increaseBuffer(void) {
	seven_seg_buffer += 1;
	seven_seg_buffer %= MAX_VALUE;
}

void decreaseBuffer(void) {
	seven_seg_buffer -= 1;
	if(seven_seg_buffer < 0) {
		seven_seg_buffer = MAX_VALUE - 1;
	}
}

void countdownBuffer(void) {
	if(seven_seg_buffer > 0) {
		seven_seg_buffer -= 1;
	}
}

void display7SEG(void) {
	driver7SEG(seven_seg_buffer);
}
