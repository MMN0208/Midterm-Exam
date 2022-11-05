/*
 * global.h
 *
 *  Created on: Oct 29, 2022
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "seven_seg_processing.h"

typedef enum  {
	INIT,
	WAIT,
	RST,
	INC,
	DEC,
	LONG_INC,
	LONG_DEC,
	AUTO,
} systemState;

extern systemState status;

#endif /* INC_GLOBAL_H_ */
