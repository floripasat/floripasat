#include <msp430.h>

void uart_tx(char *tx_data);
void config_MSP430_UART(void);

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  config_MSP430_UART();
  if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
  {
    while(1);                               // do not load, trap CPU!!
  }

  while(1){
  uart_tx("testABC");
  }
}

void config_MSP430_UART(void)
{
	  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
	  DCOCTL = CALDCO_8MHZ;
	  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
	  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCA0BR0 = 65;                            // 1MHz 9600; (104)decimal = 0x068h
	  UCA0BR1 = 3;                              // 1MHz 9600
	  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}


void uart_tx(char *tx_data)               // Define a function which accepts a character pointer to an array
{
	unsigned int i = 0;				  	  // used to determine when array is finished
	while(tx_data[i])                     // Increment through array, look for null pointer (0) at end of string
	{
		while ((UCA0STAT & UCBUSY));      // Wait if line TX/RX module is busy with data
		UCA0TXBUF = tx_data[i];           // Send out element i of tx_data array on UART bus
		i++;                              // Increment variable for array address
	}
}


