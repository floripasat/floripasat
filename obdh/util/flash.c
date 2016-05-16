/*
 * flash.c
 *
 *  Created on: 16 de mai de 2016
 *      Author: mfrata
 */

#include <msp430.h>
#include "flash.h"
#include "misc.h"


void write_flash(char* data, int bytes){
  unsigned int i;
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY|WRT;                        // Set WRT bit for write operation
  for (i = 0; i < bytes; i++){
    *flash_ptr++ = data[i];                	// Write value to flash
    while((FCTL3 & BUSY) == TRUE);             // Check if Flash being used
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY|LOCK;                       // Set LOCK bit
}

void setup_flash(long long str_addr){
	flash_ptr = str_addr;					//flash start address
}

void erase (long long region){
	flash_ptr = region;
	FCTL3 = FWKEY;                            // Clear Lock bit
	switch (region){
	case BANK0_ADDR: FCTL1 = FWKEY | MERAS; break;
	case BANK1_ADDR: FCTL1 = FWKEY | MERAS; break;
	case BANK2_ADDR: FCTL1 = FWKEY | MERAS; break;
	case BANK3_ADDR: FCTL1 = FWKEY | MERAS; break;
	case SEGA_ADDR:  FCTL1 = FWKEY | ERASE; break;
	case SEGB_ADDR:  FCTL1 = FWKEY | ERASE; break;
	case SEGC_ADDR:  FCTL1 = FWKEY | ERASE; break;
	case SEGD_ADDR:  FCTL1 = FWKEY | ERASE; break;
	case MASS_ERASE: FCTL1 = FWKEY | MERAS | ERASE; break;
	}
	*flash_ptr = 0;
	while((FCTL3 & BUSY) == TRUE);
	FCTL1 = FWKEY;                            	// Clear WRT bit
	FCTL3 = FWKEY | LOCK;                       // Set LOCK bit
}



