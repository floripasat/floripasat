#include <msp430.h>
#include <stdbool.h>
#include "memory_SPI.h"
#include "N25Q00AA.h"


unsigned char FloripaSatTXFrame[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
//floripasat transmit frame

unsigned char testFrame[] = { 0x01, 0x02, 0x03 };


unsigned char RDFrame[30];    							//place holder to test the readed frame
unsigned char IdBuffer[3];
unsigned char status;


int main(void) {

	WDTCTL = WDTPW | WDTHOLD;                   		// Stop watchdog timer
	_setup_USCIA1_SPI();								// setup SPI
	memory_adress = 0x01111111;							// start adress
	__bis_SR_register(GIE);								// enable interruptions


	while (1)
	{
		do
			_ReadId(IdBuffer, sizeof IdBuffer);
		while(IdBuffer[0] != 0x20 && IdBuffer[1] != 0xBA && IdBuffer[2] != 0x21);
		_WriteExtendedAddressRegister(0x01);
		//_SectorErase(memory_adress);

		//_PageProgram(memory_adress, testFrame, sizeof testFrame);	//writing data
		//status = _ReadStatusRegister();
		//__delay_cycles(5000);
		//memory_adress += sizeof FloripaSatTXFrame;	  //updating adress
		//_Read(memory_adress, RDFrame, sizeof RDFrame);	//reading data
	}
}
