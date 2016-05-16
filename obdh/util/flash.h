/*
 * flash.h
 *
 *  Created on: 16 de mai de 2016
 *      Author: mfrata
 */

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

char *flash_ptr;                         // Initialize Flash pointer

void write_flash(char* data, int bytes);
void setup_flash(long long str_addr);
void erase(long long region);


#endif /* UTIL_FLASH_H_ */
