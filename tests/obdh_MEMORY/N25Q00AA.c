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
	_SS(LOW);													//start of the communication
	_SPI_TX(WriteEnable);
	_SS(HIGH);													//end of the communication
}

void _ReadId(unsigned char *Buffer, int bytes){
	unsigned int i;
	_SS(LOW);													//start of the communication
	_SPI_TX(ReadId);
	for(i = 0; i < bytes; i++)
		Buffer[i] = _SPI_RX();
	_SS(HIGH);
}

void _WriteDisable(void) {
	_SS(LOW);													//start of the communication
	_SPI_TX(WriteDisable);
	_SS(HIGH);													//end of the communication
}

void _PageProgram(unsigned long startAdress, unsigned char Data[], int bytes){
	_WriteEnable();
	unsigned int i;
	_SS(LOW);													//start of the communication
	_SPI_TX(PageProgram);										//sends first the comand
	_SPI_TX(0x00 | (startAdress) >> 16);						//then sends the MSB of the adress
	_SPI_TX(0x00 | (startAdress) >> 8);							//the middle byte of adress
	_SPI_TX(0x00 | startAdress);								//last the LSB of the adress
	for(i = 0; i < bytes; i++)									//sends the actual data
		_SPI_TX(Data[i]);
	_SS(HIGH);
	//while ((_ReadStatusRegister() & WriteinProgress) == true); //wait for the end of the operaration
}

void _Read(unsigned long startAdress, unsigned char Buffer[], int bytes){
	_WriteEnable();
	unsigned int i;
	_SS(LOW);													//start of the communication
	_SPI_TX(Read);												//sends first the comand
	_SPI_TX(0x00 | (startAdress) >> 16);						//then sends the MSB of the adress
	_SPI_TX(0x00 | (startAdress) >> 8);							//the middle byte of adress
	_SPI_TX(0x00 | startAdress);								//last the LSB of the adress
	for(i = 0; i < bytes; i++)									//sends the actual data
		Buffer[i] = _SPI_RX();
		__delay_cycles(10);										//delay to the operation completes
	_SS(HIGH);
}

unsigned char _ReadStatusRegister(void){
	unsigned char status;
	_SS(LOW);													//start of the communication
	_SPI_TX(ReadStatusRegister);								//sends first the comand
	status = _SPI_RX();
	_SS(HIGH);													//start of the communication
	return status;
}

void _SectorErase(unsigned long startAdress){
	_WriteEnable();
	_SS(LOW);
	_SPI_TX(SectorErase);										//sends first the comand
	_SPI_TX(0x00 | (startAdress) >> 16);						//then sends the MSB of the adress
	_SPI_TX(0x00 | (startAdress) >> 8);							//the middle byte of adress
	_SPI_TX(0x00 | startAdress);
	_SS(HIGH);
	__delay_cycles(10000);										//delay to the operation completes

}

void _WriteExtendedAddressRegister(unsigned char byte){
	_WriteEnable();
	_SS(LOW);
	_SPI_TX(WriteExtendedAddressRegister);
	_SPI_TX(byte);
	_SS(HIGH);
	__delay_cycles(100);										//delay to the operation completes

}



