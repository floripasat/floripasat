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

#define DEBUG_LOG_ENABLE 	1	//TODO: move debug enable flag to main.c, for beter UX/visibility

void debug        (char* msg);
void debug_inline (char* msg);
void debug_int    (char* msg,  int16_t value);
void debug_uint   (char* msg, uint16_t value);
void debug_float  (char* msg,    float value);


#endif /* UTIL_DEBUG_H_ */
