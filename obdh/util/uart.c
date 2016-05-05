
#include "uart.h"


void uart_setup(void){
	P9SEL |= BIT2 + BIT3;							//P9.2,3 = USCI_A2 TXD/RXD
	UCA2CTL1 |= UCSWRST;							//**Put state machine in reset**
	UCA2CTL1 |= UCSSEL_1;							//Use ACLK (Auxilliary Clock)
	UCA2BR0 |= 0x03;								//32kHz/9600 = 3.41 (see User's Guide)
	UCA2BR1 |= 0x00;
	UCA2MCTL = UCBRS_3 + UCBRF_0;					//Modulation UCBRSx = 3, UCBRF = 0
	UCA2CTL1 &= ~UCSWRST;							//**Initialize USCI state machine
}


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



void uart_tx_hello(void){

	unsigned char hello_str[] = "Hello Floripasat!\r\n";
	uart_tx(hello_str);
}


void uart_tx(unsigned char *tx_data)			//Define a function that accepts a character pointer to an array
{
	unsigned char *PTxUart = tx_data;
	while (*PTxUart != 0) { 					// Increment through array, look for null pointer (0)  at end of string
		while ((UCA2STAT & UCBUSY));         	// Wait if line TX/RX module is busy with data
		UCA2TXBUF = *PTxUart; 					// Send out element i of tx_data array on UART bus
		PTxUart++;
	}

}


