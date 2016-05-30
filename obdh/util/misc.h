/*
 * misc.h
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#ifndef MISC_H_
#define MISC_H_

#include <stdio.h>
#include "../hal/engmodel1.h"
#include "sysclock.h"
#include "uart.h"

#define TRUE  1
#define FALSE 0

#define intStringSize 10

void sysled_setup(void);
void sysled_toggle(void);
void sysled_on(void);
void sysled_off(void);

void payloadEnable_setup(void);
void payloadEnable_on(void);
void payloadEnable_off(void);
void payloadEnable_toggle(void);

char*   int2str(char* strbuff,  int16_t value);
char*  uint2str(char* strbuff, uint16_t value);
char* float2str(char* strbuff,    float value);

unsigned char hex2char(unsigned char);
void frame2string(unsigned char*, unsigned char*, int);
unsigned char* aligned_right(unsigned char*);




#endif /* MISC_H_ */
