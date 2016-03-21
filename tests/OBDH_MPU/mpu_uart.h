/*
 * mpu_uart.h
 *
 *  Created on: Mar 18, 2016
 *      Author: mfrata
 */

#ifndef __MPU_UART_H_
#define __MPU_UART_H_

#include <stdio.h>

volatile unsigned char *PTxUart;

void setup_uart(void) {
	P3SEL |= BIT3 + BIT4;                      // P3.3,4 = USCI_A0 TXD/RXD
	UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
	UCA0BR0 = 0x03;                        // 32kHz/9600=3.41 (see User's Guide)
	UCA0BR1 = 0x00;                           //
	UCA0MCTL = UCBRS_3 + UCBRF_0;             // Modulation UCBRSx=3, UCBRFx=0
	UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine
}

void uart_tx(char *tx_data) // Define a function which accepts a character pointer to an array
		{
	PTxUart = tx_data;
	UCA0IE |= UCTXIE;                         // Enable USCI_A0 TX interrupt
	__bis_SR_register(LPM0_bits);
}

void float_send(float c) {

	volatile long int d;
	volatile unsigned int hundreds, tens, units, tenths, hundredths,
			thousandths, tenthousandths, thousandth, ten_thousandths = 0;
	volatile long int remainder;
	unsigned char string[30];

	c *= 10000;
	d = (long int) c;
	tens = d / 100000;
	remainder = d - tens * 100000;
	units = remainder / 10000;
	remainder = remainder - units * 10000;
	tenths = remainder / 1000;
	remainder = remainder - tenths * 1000;
	hundredths = remainder / 100;
	remainder = remainder - hundredths * 100;
	thousandth = remainder / 10;
	remainder = remainder - thousandth * 10;
	ten_thousandths = remainder;
	sprintf(string, "%d%d.%d%d", tens, units, tenths, hundredths);
	uart_tx(string);
}

void int_send(int data){
	unsigned char string[30];
	sprintf(string, "%d", data);
	uart_tx(string);
}
#endif /* MPU_UART_H_ */
