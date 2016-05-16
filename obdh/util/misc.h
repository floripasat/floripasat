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
unsigned char CRC8(unsigned char *Data, unsigned int n);

#define DEBUG_MODE 		1
void debug(char* strbuffer);
void debug_inline(char* strbuffer);

void frame_to_string(unsigned char frame[], unsigned char string[], int size);
unsigned char* aligned_right(unsigned char* data);
char* int2char(char* strbuff, int value);
unsigned char hex2char(unsigned char byte);


#endif /* MISC_H_ */
