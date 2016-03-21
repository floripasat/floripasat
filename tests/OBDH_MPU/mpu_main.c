//Code by : Matheus Frata
/*Mpu comunication with i2c without uart.
 * Adpatation from arduino to msp430 - http://playground.arduino.cc/Main/MPU-9150
 */
#include <msp430.h>
#include "mpu_i2c.h"
#include "mpu_9150.h"
#include "mpu_uart.h"

#define x  0
#define y  1
#define z  2

int mag[3];
int acc[3];
int gyr[3];
float temp;

void main(void) {

	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	__bis_SR_register(GIE);
	setup_i2c(0x68);
	setup_uart();
	write_i2c(MPU9150_PWR_MGMT_1, 0x00);
	MPU9150_setupCompass();
	while (1) {
		temp = (float) MPU9150_readSensor(MPU9150_TEMP_OUT_H,
		MPU9150_TEMP_OUT_L) / 340 + 35;

		acc[x] = MPU9150_readSensor(MPU9150_ACCEL_XOUT_H, MPU9150_ACCEL_XOUT_L);
		acc[y] = MPU9150_readSensor(MPU9150_ACCEL_YOUT_H, MPU9150_ACCEL_YOUT_L);
		acc[z] = MPU9150_readSensor(MPU9150_ACCEL_ZOUT_H, MPU9150_ACCEL_ZOUT_L);

		gyr[x] = MPU9150_readSensor(MPU9150_GYRO_XOUT_H, MPU9150_GYRO_XOUT_L);
		gyr[y] = MPU9150_readSensor(MPU9150_GYRO_YOUT_H, MPU9150_GYRO_YOUT_L);
		gyr[z] = MPU9150_readSensor(MPU9150_GYRO_ZOUT_H, MPU9150_GYRO_ZOUT_L);

		mag[x] = MPU9150_readSensor(MPU9150_CMPS_XOUT_H, MPU9150_CMPS_XOUT_L);
		mag[y] = MPU9150_readSensor(MPU9150_CMPS_YOUT_H, MPU9150_CMPS_YOUT_L);
		mag[z] = MPU9150_readSensor(MPU9150_CMPS_ZOUT_H, MPU9150_CMPS_ZOUT_L);

		uart_tx("temp: ");
		float_send(temp);
		uart_tx("  ");;
		uart_tx("  ");
		uart_tx("acc: ");
		int_send(acc[x]);
		uart_tx(" ");
		int_send(acc[y]);
		uart_tx(" ");
		int_send(acc[z]);
		uart_tx("  ");
		uart_tx("  ");
		uart_tx("gyr: ");
		int_send(gyr[x]);
		uart_tx(" ");
		int_send(gyr[y]);
		uart_tx(" ");
		int_send(gyr[z]);
		uart_tx("  ");
		uart_tx("  ");
		uart_tx("mag: ");
		int_send(mag[x]);
		uart_tx(" ");
		int_send(mag[y]);
		uart_tx(" ");
		int_send(mag[z]);
		uart_tx("  ");
		uart_tx("\r\n");

		__delay_cycles(500000);

	}
}

#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void) {
	switch (__even_in_range(UCB0IV, 12)) {
	case 0:
		break;                           // Vector  0: No interrupts
	case 2:
		break;                           // Vector  2: ALIFG
	case 4:
		break;                           // Vector  4: NACKIFG
	case 6:
		break;                           // Vector  6: STTIFG
	case 8:
		break;                           // Vector  8: STPIFG
	case 10:                            		// Vector 10: RXIFG
		if (RXByteCtr)                          // Check TX byte counter
		{
			RXBuffer = UCB0RXBUF;
			PRxData = &RXBuffer;             	    // Load TX buffer
			RXByteCtr--;                          // Decrement TX byte counter
		} else {
			UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
			UCB0IFG &= ~UCRXIFG;                  // Clear USCI_B0 TX int flag
			UCB0IE &= ~UCRXIE;
			__bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
		}
		break;
	case 12:                                  // Vector 12: TXIFG
		if (TXByteCtr)                          // Check TX byte counter
		{
			UCB0TXBUF = *PTxData++;               // Load TX buffer
			TXByteCtr--;                          // Decrement TX byte counter
		} else {
			UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
			UCB0IFG &= ~UCTXIFG;                  // Clear USCI_B0 TX int flag
			UCB0IE &= ~UCTXIE;
			__bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
		}
		break;
	default:
		break;
	}
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {
	switch (__even_in_range(UCA0IV, 4)) {
	case 0:
		break;                             // Vector 0 - no interrupt
	case 2:
		break;                             // Vector 2 - RXIFG
	case 4:								   // Vector 4 - TXIFG
		while (*PTxUart) // Increment through array, look for null pointer (0) at end of string
		{
			while ((UCA0STAT & UCBUSY));     // Wait if line TX/RX module is busy with data
			UCA0TXBUF = *PTxUart++; // Send out element i of tx_data array on UART bus
		}
		UCA0IFG &= ~UCTXIFG;
		UCA0IE &= ~UCTXIE;
		__bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
		break;
	default:
		break;
	}
}
