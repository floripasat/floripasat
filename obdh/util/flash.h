/*
 * flash.h
 *
 *  Created on: 16 de mai de 2016
 *      Author: mfrata
 */

#include <msp430.h>
#include "debug.h"

#ifndef UTIL_FLASH_H_
#define UTIL_FLASH_H_

//128 KB banks
#define BANK0_ADDR		0x008000
#define BANK1_ADDR		0x028000
#define BANK2_ADDR		0x048000
#define BANK3_ADDR		0x068000
//128 B info segments
#define SEGA_ADDR		0x001800
#define SEGB_ADDR		0x001880
#define SEGC_ADDR		0x001900
#define SEGD_ADDR		0x001980
//512 B bootstrap segments
#define BSL0_ADDR		0x001600
#define BSL1_ADDR		0x001400
#define BSL2_ADDR		0x001200
#define BSL3_ADDR		0x001000
#define MASS_ERASE		0XFFFFFF
//
#define BOOT_ADDR		0x026000
#define FLASH_PTR_ADDR  BANK3_ADDR

char *flash_ptr;                         	// Initialize Flash pointer
long *current_flash_ptr;					//place holder to save flash pointer to boot

void flash_write(char*, int);
void flash_setup(long);
void flash_erase(long);
void flash_write_single(char ,long *);
void flash_write_long(long* ,long *);
void flash_save_ptr(void);

void write2Flash(char*, int);


#endif /* UTIL_FLASH_H_ */
