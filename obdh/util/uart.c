
#include "uart.h"
#include "misc.h"


void uart_setup(unsigned long baud_rate){
	P9SEL |= BIT2 + BIT3;							//P9.2,3 = USCI_A2 TXD/RXD
	UCA2CTL1 |= UCSWRST;							//**Put state machine in reset**
	UCA2CTL1 |= UCSSEL_1;							//Use ACLK (Auxilliary Clock)
	set_baud_rate(baud_rate);
	UCA2MCTL = UCBRS_3 + UCBRF_0;					//Modulation UCBRSx = 3, UCBRF = 0
	//UCA2IE |= UCRXIE;								//enabling RX interruption
	UCA2CTL1 &= ~UCSWRST;							//**Initialize USCI state machine
}

void set_baud_rate(unsigned long baud_rate){
	switch(baud_rate){
	case 9600:
		UCA2BR0 |= 0x03;								//32kHz/9600 = 3.41 (see User's Guide)
		UCA2BR1 |= 0x00;
		break;
	case 4800:
		//TODO implementation
		break;
	default: //9600
		UCA2BR0 |= 0x03;								//32kHz/9600 = 3.41 (see User's Guide)
		UCA2BR1 |= 0x00;
		break;
	}
}

void uart_tx_hello(void){
	unsigned char hello_str[] = "Hello Floripasat!\r\n";
	uart_tx(hello_str);
}


void uart_tx(unsigned char *tx_data){			//Define a function that accepts a character pointer to an array
	while (*tx_data != 0) { 					// Increment through array, look for null pointer (0)  at end of string
		while ((UCA2STAT & UCBUSY) == TRUE);         // Wait if line TX/RX module is busy with data
		UCA2TXBUF = *tx_data; 					// Send out element i of tx_data array on UART bus
		tx_data++;
	}

}

unsigned char uart_rx(void){
	while ((UCA2STAT & UCBUSY) == TRUE);         	// Wait if line TX/RX module is busy with data
	return UCA2RXBUF;
}


/*
 * Interrupt Vector
 */
#pragma vector=USCI_A2_VECTOR
__interrupt void USCI_A2_ISR(void) {
  switch (__even_in_range(UCA2IV, 4)) {
  case 0:							// Vector 0 - no interrupt
      break;
  case 2:							// Vector 2 - RXIFG
      break;
  case 4:                           // Vector 4 - TXIFG
      break;
  default:
      break;
  }
}

