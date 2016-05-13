/*
 * misc.h
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#ifndef MISC_H_
#define MISC_H_

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define intStringSize 10

void sysled_enable(void);
void sysled_toggle(void);
void frame_to_string(unsigned char frame[], unsigned char string[], int size);
unsigned char* aligned_right(unsigned char* data);
unsigned char* int_to_char(int value);
unsigned char hex_to_char(unsigned char byte);


#endif /* MISC_H_ */
