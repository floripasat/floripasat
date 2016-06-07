/*
 * flash.h
 *
 *  Created on: 16 de mai de 2016
 *      Author: mfrata
 */

#include <msp430.h>
#include "debug.h"
#include "../hal/engmodel1.h"

#ifndef UTIL_FLASH_H_
#define UTIL_FLASH_H_

char *flash_ptr;                         	// Initialize Flash pointer
long *current_flash_ptr;					//place holder to save flash pointer to boot

void flash_write(char*, int);
void flash_setup(void);
void flash_erase(long);
void flash_write_single(char ,long *);
void flash_write_long(long* ,long *);
void flash_save_ptr(void);
void flash_reset_ptr(void);

void write2Flash(char*, int);


#endif /* UTIL_FLASH_H_ */
