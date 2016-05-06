/*
 * misc.c
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#include "misc.h"
#include "../hal/obdh_engmodel1.h"


void sysled_enable(void){
	SYSLED_PORT_DIR |= SYSLED_PIN; // set as output
	SYSLED_PORT_OUT &= ~SYSLED_PIN;
}


void sysled_toggle(void){
	SYSLED_PORT_OUT ^= SYSLED_PIN; //toggle port state
}
