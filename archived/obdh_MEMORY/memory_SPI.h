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
#define DummyByte		0x00


void _setup_USCIA1_SPI(void);
void _SS(bool state);
void _SPI_TX(unsigned char byte);
unsigned char _SPI_RX();

#endif /* _MEMORY_SPI_H_ */
