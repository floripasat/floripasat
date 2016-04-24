#include <msp430.h>
#include <stdbool.h>
#include "memory_SPI.h"
#include "N25Q00AA.h"


unsigned char FloripaSatTXFrame[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xFF };
//floripasat transmit frame

unsigned char RDFrame[FloripaSatFrameSize];    			//place holder to test the readed frame

int main(void) {

	WDTCTL = WDTPW | WDTHOLD;                   		// Stop watchdog timer
	_setup_USCIA1_SPI();								// setup SPI
	memory_adress = 0x00000000;							// start adress
	__bis_SR_register(GIE);								// enable interruptions

	while (1)
	{
		_WriteEnable();									//enable write (set write latch)
		_PageProgram(memory_adress, FloripaSatTXFrame);	//writing data
		//memory_adress += sizeof FloripaSatTXFrame;	  //updating adress
		__delay_cycles(500);
		_Read(memory_adress, RDFrame, sizeof RDFrame);	//reading data
	}
}
