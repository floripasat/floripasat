/*
 * N25Q00AA.c
 *
 *  Created on: 22/04/2016
 *      Author: Frata
 */

#include <msp430.h>
#include "N25Q00AA.h"
#include "memory_SPI.h"


void _WriteEnable(void) {
	unsigned char TXData[] = { WriteEnable };
	_SPI_TX(TXData, sizeof TXData);
}

void _WriteDisable(void) {
	unsigned char TXData[] = { WriteDisable };
	_SPI_TX(TXData, sizeof TXData);
}

void _PageProgram(unsigned long startAdress, unsigned char *Data){
	int i;														//iteration variable
	unsigned char *fillerPtr = Data;							//poiter to fill up the Transmit data vector
	unsigned char TXData[4 + FloripaSatFrameSize];				//Creating Transmit data vector
	TXData[0] = PageProgram;									//sends first the comand
	TXData[1] = (0x00 | (startAdress) >> 16);					//then sends the MSB of the adress
	TXData[2] = (0x00 | (startAdress) >> 8);					//the middle byte of adress
	TXData[3] = (0x00 | startAdress);							//last the LSB of the adress
	for(i = 4; i < sizeof TXData; i++)							//filling up the Transmit data vector...
		TXData[i] = *fillerPtr++;								//...with the actual data
	_SPI_TX(TXData, sizeof TXData);								//deliver to transmit
	__delay_cycles(100);										//delay to the operation completes
}

void _Read(unsigned long startAdress, unsigned char Buffer[], int bytes){
	unsigned char TXData[] = { Read, (0x00 | (startAdress) >> 16), (0x00 | (startAdress) >> 8), (0x00 | startAdress) }; //creating Transmit data vector
	unsigned char *AuxPtr = Buffer;								//auxiliar pointer to buffer
	int bufferSize = bytes;										//auxiliar interger to bytes
	_SPI_RX(TXData, sizeof TXData, AuxPtr, bufferSize);			//deliver to transmit and then read
}
