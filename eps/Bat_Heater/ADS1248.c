#include <msp430.h>
#include "ADS1248.h"

volatile unsigned int w=0;
volatile long temp[]= {0,0,0};
volatile unsigned int i=0;


void config_ADS1248(int channel)
{
	int data[] = {SDATAC_command,WREG_command,0x03,(channel << 3 | 0x01),0x00,0x20,0x33,0x4A,0x01,0x02,0x60,0x20,0x03,NOP_command,NOP_command,NOP_command,NOP_command,0x2A,0x01,NOP_command,NOP_command};
	for (i = 50; i > 0; i--);                	 			// Wait for slave to initialize
	UCB1TXBUF = RESET_command;                     		// Send reset command to ensure device is properly powered on
	__delay_cycles(4800);									// delay after reset of 0.6ms

	for(w=0;w < 21;w++)
	{

		 UCB1TXBUF = data[w];
		for (i = 500; i; i--);                     // Add time between transmissions to
												   // make sure slave can keep up
	}
	if(w == 21)
	{
		P3OUT |= BIT6;
}
}
void read_ADS1248(int channel)
{

	P5OUT &= ~BIT4;
	UCB1TXBUF = SDATAC_command;
	for (i = 500; i; i--);
	UCB1TXBUF = WREG_command;
	for (i = 500; i; i--);
	UCB1TXBUF = 0x00;
	for (i = 500; i; i--);
	UCB1TXBUF = (channel << 3) | 0x01;
	for (i = 500; i; i--);

	/*
	UCB1TXBUF = 0x4B;
	for (i = 500; i; i--);
	UCB1TXBUF = 0x00;
	for (i = 500; i; i--);
	UCB1TXBUF = 0xC0 | channel;
	for (i = 500; i; i--);

*/

	UCB1TXBUF = SYNC_command;
	__delay_cycles(7);						// delay of 7 tclk
	P5OUT |= BIT4;

	__delay_cycles(250000);
				P3OUT &= ~BIT6;
				P5OUT &= ~BIT4;
				__delay_cycles(7);
				UCB1TXBUF = 0x12;
				for (i = 500; i; i--);                     // Add time between transmissions to
														   // make sure slave can keep up
				UCB1TXBUF = NOP_command;
				for (i = 500; i; i--);                     // Add time between transmissions to
														   // make sure slave can keep up
				temp[0] = UCB1RXBUF;
				UCB1TXBUF = NOP_command;
				for (i = 500; i; i--);                     // Add time between transmissions to
														   // make sure slave can keep up

				temp[1] = UCB1RXBUF;
				UCB1TXBUF = NOP_command;
				for (i = 500; i; i--);                     // Add time between transmissions to
														   // make sure slave can keep up
				temp[2] = UCB1RXBUF;
				__delay_cycles(7);
				P5OUT |= BIT4;


}
