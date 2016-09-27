#include <eps_serial.h>
#include <msp430.h>
#include <stdio.h>
#include <intrinsics.h>



void config_MSP430_UART(void)
{
//	  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
	//  DCOCTL = CALDCO_8MHZ;
	  P3SEL |= 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
	  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCA0BR0 = 65;                            // 1MHz 9600; (104)decimal = 0x068h
	  UCA0BR1 = 3;                              // 1MHz   9600
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

void float_send(float c)
{

    volatile long int d;
	volatile long int hundreds, tens, units, tenths, hundredths, thousandths, tenthousandths,thousandth, ten_thousandths;
	volatile long int remainder;
    char string[30];

    c *= 10000;																						// multiply value by 10000
    d = (long int)c;																				// convert value to long int (truncation)
    tens = d/100000;																				// take tens part of number
    remainder =d - tens*100000;																		// take remainder
    units = remainder/10000;																		// take units part of number
    remainder = remainder - units*10000;															// take remainder
	tenths = remainder/1000;																		// take tenths part of number
    remainder = remainder - tenths*1000;															// take remainder
    hundredths = remainder/100;																		// take hundredths part of number
    remainder = remainder - hundredths *100;														// take remainder
    thousandth = remainder/10;																		// take thousandths part of number
	remainder = remainder -thousandth*10;															// take remainder
	ten_thousandths=remainder;																		// take ten thousandths part of number with truncation of remainder
    sprintf(string, "%ld%ld.%ld%ld%ld%ld", tens, units, tenths, hundredths,thousandth,ten_thousandths);	// converT all parts of number to single string
	uart_tx(string);																				// send string via uart
}
