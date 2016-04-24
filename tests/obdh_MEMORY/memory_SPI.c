/*
 * memory_SPI.c
 *
 *  Created on: 22/04/2016
 *      Author: Frata
 */

#include <msp430.h>
#include <stdbool.h>
#include "memory_SPI.h"
#include "N25Q00AA.h"


void _setup_USCIA1_SPI(void) {
	P8SEL |= BIT1 + BIT2 + BIT3 + BIT4;            				// clk,mosi,miso
	P8DIR |= BIT4;												// ss
	P8OUT |= BIT4;												// ss activate in low

	UCA1CTL1 |= UCSWRST;                      					// **Put state machine in reset**
	UCA1CTL0 |= UCMST | UCSYNC | UCCKPL | UCCKPH | UCMSB; 		// 3pin, 8-bit SPI master, Clock polarity high, clock phase, MSB

	UCA1CTL1 |= UCSSEL_2;                     					// SMCLK
	UCA1BR0 = 0x02;                           					// /2
	UCA1BR1 = 0;                              					//
	UCA1MCTL = 0;                             					// No modulation
	UCA1CTL1 &= ~UCSWRST;                   					// **Initialize USCI state machine**
}

void _SS(bool state) {											// setting and clearing SS pin
	switch (state) {
	case LOW:
		P8OUT &= ~BIT4;
		break;
	case HIGH:
		P8OUT |= BIT4;
		break;
	}
}

void _SPI_TX(unsigned char TXframe[], int sizeTX) {
	num_bytes = sizeTX;											//assigning TXsize
	DPTR = TXframe;												//assigning TXframe to data pointer
	_SS(LOW);													//start of the communication
	UCA1IFG |= UCTXIFG;											//setting TX flag
	UCA1IE |= UCTXIE;											//enabling TX interrupt
	__bis_SR_register(LPM0_bits);								//enter LPM
																/** goes to interruptvector**/
	_SS(HIGH);													//end of the communication
}

void _SPI_RX(unsigned char TXframe[], int sizeTX,  unsigned char RXBuffer[], int bytesToRead) {
	num_bytes = sizeTX;											//assigning TXsize
	DPTR = TXframe;												//assigning TXframe to data pointer
	_SS(LOW);													//start of the communication
	UCA1IFG |= UCTXIFG;											//enabling TX flag
	UCA1IE |= UCTXIE;											//enabling TX interrupt
	__bis_SR_register(LPM0_bits);								//enter LPM
																/** goes to interruptvector**/
	DPTR = RXBuffer;											//assigning RXBuffer to data pointer
	num_bytes = bytesToRead;									//assigning bytesToread
	UCA1IFG |= UCRXIFG;											//enabling RX flag
	UCA1IE |= UCRXIE;											//enabling RX interrupt
	__bis_SR_register(LPM0_bits);								//enter LPM
																/** goes to interruptvector**/
	_SS(HIGH);													//end of the communication
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)

{
	switch (__even_in_range(UCA1IV, 4)) {
	case 0:														// Vector 0 - no interrupt
		break;
	case 2:														// Vector 2 - RXIFG
		do {
			num_bytes--;
			*DPTR++ = UCA1RXBUF;
		} while (num_bytes > 0);
		UCA1IE &= ~UCRXIE;
		UCA1IFG &= ~UCRXIFG;
		__bic_SR_register_on_exit(LPM0_bits); 					// Exit LPM0
		break;
	case 4:														// Vector 4 - TXIFG
		do {
			num_bytes--;
			UCA1TXBUF = *DPTR++;
		} while (num_bytes > 0);
		UCA1IE &= ~UCTXIE;
		UCA1IFG &= ~UCTXIFG;
		__bic_SR_register_on_exit(LPM0_bits); 					// Exit LPM0
		break;
	default:
		break;
	}
}
