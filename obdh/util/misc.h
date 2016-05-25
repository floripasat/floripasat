/*
 * misc.h
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#ifndef MISC_H_
#define MISC_H_

#include <stdio.h>

#define TRUE  1
#define FALSE 0

#define intStringSize 10

void sysled_enable(void);
void sysled_toggle(void);
unsigned char CRC8(unsigned char *, unsigned int);

#define DEBUG_MODE 		1
void debug(char*);
void debug_inline(char*);

void frame2string(unsigned char*, unsigned char*, int);
unsigned char* aligned_right(unsigned char*);

char*   int2str(char* strbuff,          int value);
char*  uint2str(char* strbuff, unsigned int value);
char* float2str(char* strbuff,        float value);

unsigned char hex2char(unsigned char);



#endif /* MISC_H_ */
