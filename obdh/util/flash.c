/*
 * flash.c
 *
 *  Created on: 16 de mai de 2016
 *      Author: mfrata
 */


#include "flash.h"

void write2Flash(char* data, int bytes){
	debug("Writing to flash init");
	if(flash_ptr >= LAST_WRITE_ADDR || flash_ptr == (OVERFLOW_FLAG_ADDR)){
		flash_ptr = OVERFLOW_FLAG_ADDR;
		flash_write("{FSAT:memory full}",18);
		flash_ptr = OVERFLOW_FLAG_ADDR;
	}else {
		flash_write(data,bytes);
		flash_save_ptr();
	}
	debug("Writing to flash done");
}


void flash_write(char* data, int bytes){
	  unsigned int i;
	//  __disable_interrupt();
	  FCTL3 = FWKEY;                            // Clear Lock bit
	  FCTL1 = FWKEY|WRT;                        // Set WRT bit for write operation
	  for (i = 0; i < bytes; i++){
		*flash_ptr++ = data[i];                	// Write value to flash
		while((FCTL3 & BUSY) == TRUE);             // Check if Flash being used
	  }
	  FCTL1 = FWKEY;                            // Clear WRT bit
	  FCTL3 = FWKEY|LOCK;                       // Set LOCK bit
	//  __enable_interrupt();
}

void flash_write_single(char data, long *addr){
//  __disable_interrupt();
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY|WRT;                        // Set WRT bit for write operation
  *addr = data;                				// Write value to flash
  while((FCTL3 & BUSY) == TRUE);            // Check if Flash being used
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY|LOCK;                       // Set LOCK bit
//  __enable_interrupt();
}

void flash_write_long(long* data, long *addr){
//  __disable_interrupt();
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY|BLKWRT;                     // Set WRT bit for write operation
  *addr = data;                				// Write value to flash
  while((FCTL3 & BUSY) == TRUE);            // Check if Flash being used
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY|LOCK;                       // Set LOCK bit
//  __enable_interrupt();
}


void flash_setup(void) {
	current_flash_ptr = FLASH_PTR_ADDR;
	flash_ptr = *current_flash_ptr;
}

void flash_erase(long region){
	long *erase_ptr = region;
//	__disable_interrupt();
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
	*erase_ptr = 0;
	while((FCTL3 & BUSY) == TRUE);
	FCTL1 = FWKEY;                            	// Clear WRT bit
	FCTL3 = FWKEY | LOCK;                       // Set LOCK bit
//	__enable_interrupt();
}


void flash_save_ptr(void){
	current_flash_ptr = FLASH_PTR_ADDR;
	flash_erase(FLASH_PTR_ADDR);
	flash_write_long(flash_ptr, current_flash_ptr);
}

void flash_reset_ptr(void){
	flash_erase(FLASH_PTR_ADDR);
	flash_write_long(BOOT_ADDR,FLASH_PTR_ADDR);
}
