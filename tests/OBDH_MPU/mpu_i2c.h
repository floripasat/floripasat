/*
 * mpu_i2c.h
 *
 *  Created on: Mar 18, 2016
 *      Author: mfrata
 */

#ifndef __MPU_I2C_H_
#define __MPU_I2C_H_


volatile unsigned char *PTxData;                     // Pointer to TX data
volatile unsigned char *PRxData;                     // Pointer to RX data
unsigned char RXBuffer;
char TXByteCtr;
char RXByteCtr;

void write_i2c(volatile unsigned char reg_adrr, volatile unsigned char data) {
	volatile unsigned char TxData[] = { reg_adrr, data };
	PTxData = (volatile unsigned char *) TxData;
	TXByteCtr = sizeof TxData;
	UCB0CTL1 |= UCTR + UCTXSTT;
	UCB0IE |= UCTXIE;
	__bis_SR_register(LPM0_bits);
	while (UCB0CTL1 & UCTXSTP);
}
void setup_i2c(volatile unsigned char dev_adrr) {
	P3SEL |= BIT0 + BIT1;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;
	UCB0I2CSA = dev_adrr;                         // Slave Address is 048h
	UCB0CTL1 &= ~UCSWRST;                    // Clear SW reset, resume operation

}
char read_i2c(volatile unsigned char reg_adrr) {
	char Data;
	PTxData = &reg_adrr;
	TXByteCtr = 1;
	UCB0CTL1 |= UCTR + UCTXSTT;
	UCB0IE |= UCTXIE;
	__bis_SR_register(LPM0_bits);
	while (UCB0CTL1 & UCTXSTP);
	RXByteCtr = 1;
	UCB0CTL1 &= ~UCTR;
	UCB0CTL1 |= UCTXSTT;
	UCB0IE |= UCRXIE;
	__bis_SR_register(LPM0_bits);
	Data = *PRxData;
	return Data;
}

void clear(void) {
	PTxData = 0;
	PRxData = 0;
	RXBuffer = 0;
	TXByteCtr = 0;
	RXByteCtr = 0;
	UCB0TXBUF = 0;
}

#endif /* MPU_I2C_H_ */
