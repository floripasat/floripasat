/*
 * debug.h
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#ifndef UTIL_DEBUG_H_
#define UTIL_DEBUG_H_

#include "sysclock.h"
#include "uart.h"

#define DEBUG_LOG_ENABLE 		1

char tmpStr[16];

void debug        (char* msg);
void debug_int    (char* msg,  int16_t value);
void debug_uint   (char* msg, uint16_t value);
void debug_print  (char* msg);




#endif /* UTIL_DEBUG_H_ */
