/*
 * obdh.c
 *
 *  Created on: 30 de mai de 2016
 *      Author: mario
 */

// Interface with internal components of the OBDH SoC

#include "obdh.h"
#include "../hal/engmodel1.h"

void obdh_read(char* obdhData){

	obdhData[0] = 0;		//sysclock  S high
	obdhData[1] = 1;		//sysclock  S low
	obdhData[2] = 2;		//sysclock MS high
	obdhData[3] = 3;		//sysclock MS low
	obdhData[4] = 4;		//temperature high
	obdhData[5] = 5;		//temperature low
	obdhData[6] = 5;		//system status code

	__delay_cycles(DELAY_100_MS_IN_CYCLES);

}
