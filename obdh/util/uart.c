
#include "uart.h"
#include "misc.h"


void uart_debug_setup(unsigned long baudrate){
	P9SEL |= BIT2 + BIT3;							//P9.2,3 = USCI_A2 TXD/RXD
	UCA2CTL1 |= UCSWRST;							//**Put state machine in reset**
	UCA2CTL1 |= UCSSEL_1;							//Use ACLK (Auxilliary Clock)
	uart_set_baudrate(baudrate);
	UCA2MCTL = UCBRS_3 + UCBRF_0;					//Modulation UCBRSx = 3, UCBRF = 0
	//UCA2IE |= UCRXIE;								//enabling RX interruption
	UCA2CTL1 &= ~UCSWRST;							//**Initialize USCI state machine
}

void uart_set_baudrate(unsigned long baudrate){
	switch(baudrate){
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



// Can be used directly for debug messages:
// uart_tx("hello");
void uart_debug_tx(char *tx_data){			//Define a function that accepts a character pointer to an array
	while (*tx_data != 0) { 					// Increment through array, look for null pointer (0)  at end of string
		while ((UCA2STAT & UCBUSY) == TRUE);         // Wait if line TX/RX module is busy with data
		UCA2TXBUF = *tx_data; 					// Send out element i of tx_data array on UART bus
		tx_data++;
	}

}

void uart_debug_tx_newline(void){
	uart_debug_tx("\n\r");
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

