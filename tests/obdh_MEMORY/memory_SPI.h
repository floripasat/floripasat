/*
 * memory_SPI.h
 *
 *  Created on: 22/04/2016
 *      Author: Frata
 */

#ifndef _MEMORY_SPI_H_
#define _MEMORY_SPI_H_

#include <stdbool.h>			//include for the SS function

#define HIGH	true			//state high for slave select
#define LOW		false			//state low for slave select

unsigned char *DPTR;       		//data pointer
unsigned int num_bytes;			//number of bytes

void _setup_USCIA1_SPI(void);
void _SS(bool state);
void _SPI_TX(unsigned char TXframe[], int sizeTX);
void _SPI_RX(unsigned char TXframe[], int sizeTX, unsigned char RXBuffer[], int bytesToRead);

#endif /* _MEMORY_SPI_H_ */
