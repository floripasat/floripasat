/*
FloripaSat I2C multi-mater

Author: Bruno Eiterer

Descripition: this code implements I2C multi-master protocol between a EPS Directly Coupled prototype board and a OBC prototype board. It checks if the bus is busy before
attempting to start an i2c communication, if the bus is busy it reconfigures the microcontroller as a slave receiver and waits for another master to initiate communication. If the
bus is not busy, it keeps sending start conditions and the slave andress until the slave send an ACK signal, this way it waits for a possible other master reconfiguring as a slave.

To do: validade arbitration procedure when two masters start communication at the same time (implemented in hardware)

*/

#include <msp430.h>

//------------- GLOBAL VARIABLES -------------//

unsigned char RXByteCtr;
volatile unsigned char RxBuffer[5];       	// Variable to save received data
volatile unsigned int i = 0;				// Counter to determine which RxBuffer position is to be used
unsigned char *PTxData;                     // Pointer to TX data
unsigned char TXByteCtr;					// Counter to determine which TxData position is to be sent
const unsigned char TxData[] =              // Table of data to transmit
{
		0x11,
		0x22,
		0x33,
		0x44,
		0x55
};

//------------- FUNCTION PROTOTYPES -------------//

void config_master_mode(void);
void config_slave_mode(void);

//------------- MAIN -------------//

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 			// Stop WDT
	config_master_mode();								// call function to configure I2C master moder

	while (1)
	{
		if(UCB0STAT & UCBBUSY)							// Checks if bus is busy
		{
			config_slave_mode();						// If bus is busy config as slave to receive data
		}
		else
		{
			while (UCB0CTL1 & UCTXSTP);             	// Ensure stop condition got sent
			UCB0CTL1 |= UCTXSTT;             			// send start condition
			__delay_cycles(150);						// ???waits for NACK flag to be set???
			while(UCB0STAT & UCNACKIFG){				// keep sending start condition and adress while NACK is received. This waits for another master possibly reconfiguring as slave
				UCB0CTL1 |= UCTXSTT;             		// send start condition
				__delay_cycles(150);					// ???waits for NACK flag to be set???
			}
		}
		__bis_SR_register(GIE);        					// enable interrupts
		while(1);										// traps CPU after communication is done
	}
}

//------------- INTERRUPTS -------------//

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)

{
	if(UCB0CTL1 & UCTR){							// check if interrupt source is Tx or Rx
		if (TXByteCtr)                            	// check TX byte counter
		{
			UCB0TXBUF = *PTxData++;                 // load TX buffer
			TXByteCtr--;                            // decrement TX byte counter
		}
		else
		{
			UCB0CTL1 |= UCTXSTP;                    // send I2C stop condition
			IFG2 &= ~UCB0TXIFG;                     // clear USCI_B0 TX int flag
		}
	}
	else
	{
		RxBuffer[i] = UCB0RXBUF;                   	// move RX data to RxBuffer[i]
		i++;										// incremets RxBuffer counter
	}
}

//------------- CONFIGURATION FUNCTIONS -------------//

void config_slave_mode(void)
{
	i = 0;											// reset RxBuffer counter
	P3SEL |= 0x06;                            		// assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      		// enable SW reset
	UCB0CTL1 &= ~UCTR;								// receiver mode
	UCB0CTL0 = UCMODE_3 + UCSYNC;             		// I2C Slave, synchronous mode
	UCB0I2COA = 0x50;								// own andress value (example 0x50h)
	UCB0CTL1 &= ~UCSWRST;                     		// clear SW reset, resume operation
	IE2 |= UCB0RXIE;                          		// enable RX interrupt
}

void config_master_mode(void)
{
	P3SEL |= 0x06;                            			// Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      			// Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC + UCMM;     	// I2C Master, synchronous mode, multi-master environment
	UCB0CTL1 = UCSSEL_2 + UCTR + UCSWRST;           	// Use SMCLK, keep SW reset, trasmitter mode
	UCB0BR0 = 12;                             			// fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;
	UCB0I2CSA = 0x50;                         			// Slave Address Register
	UCB0CTL1 &= ~UCSWRST;                     			// Clear SW reset, resume operation
	PTxData = (unsigned char *)TxData;      			// TX array start address
	TXByteCtr = sizeof TxData;              			// Load TX byte counter
	IE2 |= UCB0TXIE;                          			// Enable TX interrupt
}


