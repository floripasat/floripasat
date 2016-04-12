#include <eps_serial_test.h>
#include <msp430.h>
#include <stdio.h>
#include <intrinsics.h>



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

void text(void)
{
	volatile int a,b;
	volatile float c;

   //ADC4
   a=adc4_lsb;								// take adc1 LSB
   b=adc4_msb;								// take adc1 MSB
   b=b<<8;									// shift MSB 8 bits to the left
   a=a+b;									// add LSB and shifted MSB to have a full 16bit number
   c=a*0.00061035;    						// multiply by ADC resolution 2.5/(2^12)
// uart_tx(" ADC4= ");						// used for better visual purposes, not used in tests
   float_send(c);							// call function to send float value via UART
// uart_tx("V");							// used for better viasual purposes, not used in tests
   uart_tx("\r\n");

   //ADC5
   a=adc5_lsb;								// take adc1 LSB
   b=adc5_msb;								// take adc1 MSB
   b=b<<8;									// shift MSB 8 bits to the left
   a=a+b;									// add LSB and shifted MSB to have a full 16bit number
   c=a*0.00061035;    						// multiply by ADC resolution 2.5/(2^12)
// uart_tx(" ADC5= ");						// used for better visual purposes, not used in tests
   float_send(c);							// call function to send float value via UART
// uart_tx("V");							// used for better viasual purposes, not used in tests
   uart_tx("\r\n");


}


void float_send(float c)
{

    volatile long int d;
	volatile  unsigned int hundreds, tens, units, tenths, hundredths, thousandths, tenthousandths,thousandth, ten_thousandths;
	volatile long int remainder;
    char string[30];

    c *= 10000;
    d = (long int)c;
    tens = d/100000;
    remainder =d - tens*100000;
    units = remainder/10000;
    remainder = remainder - units*10000;
	tenths = remainder/1000;
    remainder = remainder - tenths*1000;
    hundredths = remainder/100;
    remainder = remainder - hundredths *100;
    thousandth = remainder/10;
	remainder = remainder -thousandth*10;
	ten_thousandths=remainder;
    sprintf(string, "%d%d.%d%d%d%d", tens, units, tenths, hundredths,thousandth,ten_thousandths);
	uart_tx(string);
}
