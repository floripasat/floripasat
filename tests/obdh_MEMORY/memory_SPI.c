/*
 * memory_SPI.c
 *
 *  Created on: 22/04/2016
 *      Author: Frata
 */

#include <msp430.h>
#include <stdbool.h>
#include "memory_SPI.h"


void _setup_USCIA1_SPI(void) {
	P8SEL |= BIT1 + BIT2 + BIT3;            						// clk,mosi,miso
	P8DIR |= BIT4;													// ss
	P8OUT |= BIT4;													// ss activate in low

	UCA1CTL1 |= UCSWRST;                      						// **Put state machine in reset**
	UCA1CTL0 |= UCMODE_0 | UCMST | UCSYNC | UCMSB | UCCKPH;// 4pin, 8-bit SPI master, Clock polarity high, clock phase, MSB
	UCA1CTL1 |= UCSSEL_2;                     						// SMCLK
	UCA1BR0 = 0x02;                           						// /2
	UCA1BR1 = 0;                              						//
	UCA1MCTL = 0;                             						// No modulation
	UCA1IE |= UCRXIE | UCTXIE;
	UCA1CTL1 &= ~UCSWRST;                   						// **Initialize USCI state machine**
}

void _SS(bool state) {												// setting and clearing SS pin
	switch (state) {
	case LOW:
		P8OUT &= ~BIT4;
		break;
	case HIGH:
		P8OUT |= BIT4;
		break;
	}
}

void _SPI_TX(unsigned char byte) {
	UCA1TXBUF = byte;
	__delay_cycles(100);
}

unsigned char _SPI_RX() {
	_SPI_TX(DummyByte);
	return UCA1RXBUF;
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)

{
	switch (__even_in_range(UCA1IV, 4)) {
	case 0:														// Vector 0 - no interrupt
		break;
	case 2:														// Vector 2 - RXIFG
		while((UCA1STAT & UCBUSY) == 1);
		UCA1IFG &= ~UCRXIFG;
		break;
	case 4:														// Vector 4 - TXIFG
		while((UCA1STAT & UCBUSY) == 1);
		UCA1IFG &= ~UCTXIFG;
		break;
	default:
		break;
	}
}
