#include "eps_serial_test.h"
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
	volatile int signal = 0;

/*
	switch(LCA){
		case 0: uart_tx("Decrease");
		break;

		case 1: uart_tx("Increase");
		break;

		case 2: uart_tx("-Eclipse");
		break;

		case 3: uart_tx("-TurnOff");
		break;

		default: uart_tx("NULLNULL");
	}

	     uart_tx(",");
*/

	//ADC4
	// uart_tx(" ADC4= ");					// used for better visual purposes, not used in tests
	float_send(mean_voltage);				// call function to send float value via UART
	// uart_tx("V");						// used for better viasual purposes, not used in tests
	uart_tx(",");							// send comma via UART (easer data separation in tests)

	//ADC5
	// uart_tx(" ADC5= ");					// used for better visual purposes, not used in tests
	float_send(mean_current);				// call function to send float value via UART
	// uart_tx("A");						// used for better viasual purposes, not used in tests
	uart_tx(",");							// send comma via UART (easer data separation in tests)

	//Average Current
	signal= cr_msb & 0x80;					// take msb, bitwise and with 0x80, this yelds the most signficant bit of the number which represents the signal in 2-complement
	if (signal == 0x00){					// test if number is positive
		a=  avc_lsb;						// take average current LSB
		b=  avc_msb;						// take average current MSB
	}
	else{
		if (signal == 0x80){				// test if number is negative
			b = ~avc_msb ;					// complement MSB
			a= ~avc_lsb+1;					// complement LSB anb add 1
			a &= 255;						// take only LSB part of number
			uart_tx("-");					// send minus signal via uart
		}
	}

	b=b<<8;									// shift MSB 8 bits to the left
	a=a+b;									// add LSB and shifted MSB to have a full 16bit number
	c=a*0.0000015625/0.050;    				// multiply by average current register resolution 0.0000015625/rsense
	// UART_TX(" Average Current= ");		// used for better visual purposes, not used in tests
	float_send(c);							// call function to send float value via UART
	uart_tx(",");							// send comma via UART (easer data separation in tests)


	//Temperature
	a=  tr_lsb;								// take temperature LSB
	b=  tr_msb;								// take temperature MSB
	b=b<<8;									// shift MSB 8 bits to the left
	a=a+b;									// add LSB and shifted MSB to have a full 16bit number
	c=a*0.125;    							// multiply by temperature register resolution 0.125
	//  UART_TX(" Temperature= ");			// used for better visual purposes, not used in tests
	float_send(c);							// call function to send float value via UART
	uart_tx(",");							// send comma via UART (easer data separation in tests)


	//Voltage
	a=  vr_lsb;								// take battery voltage LSB
	b=  vr_msb;								// take battery voltage MSB
	b=b<<8;									// shift MSB 8 bits to the left
	a=a+b;									// add LSB and shifted MSB to have a full 16bit number
	c=a*0.004886;    						// multiply by voltage register resolution 4.886mV
	//    UART_TX(" Voltage= ");			// used for better visual purposes, not used in tests
	float_send(c);							// call function to send float value via UART
	uart_tx(",");							// send comma via UART (easer data separation in tests)


	//Current
	signal=0;								// clear signal value
	signal= cr_msb & 0x80;					// take msb, bitwise and with 0x80, this yelds the most signficant bit of the number which represents the signal in 2-complement
	if (signal == 0x00){					// test if number is positive
		b= cr_msb;							// take current MSB
		a= cr_lsb;							// take current LSB
	}
	if (signal == 0x80){					// test if number is negative
		b= ~cr_msb;							// complement MSB
		a= ~cr_lsb+1;						// complement LSB and add 1
		a &= 255;							// take only LSB part of number
		uart_tx("-");						// send minus signal via uart
	}
	b=b<<8;									// shift MSB 8 bits to the left
	a=a+b;									// add LSB and shifted MSB to have a full 16bit number
	c=a*0.0000015625/0.050;    				// multiply by current resolution 0.0000015625/rsense
	// uart_Tx("current=");					// used for better visual purposes, not used in tests
	float_send(c);							// call function to send float value via UART
	uart_tx(",");							// send comma via UART (easer data separation in tests)


	//Accumulated Current
	a=  acr_lsb;							// take accumulated current LSB
	b=  acr_msb;							// take accumulated current MSB
	b=b<<8;									// shift MSB 8 bits to the left
	a=a+b;									// add LSB and shifted MSB to have a full 16bit number
	c=a*0.00000625/0.015;    				// multiply by accumulated current register resolution 0.00000625/rsense
	//  UART_TX("Accumulated Current= ");	// used for better visual purposes, not used in tests
	float_send(c);							// call function to send float value via UART
	uart_tx(",");							// send comma via UART (easer data separation in tests)


	//Protection Register
	char protection_register[10];			// allocate memory for protection register pointer
	a = RG_Protection;						// take protection register value
	sprintf(protection_register, "%d", a);  // convert protection register value from int to char*
//	uart_tx("Protection Register=")			// used for better visual purposes, not used in tests
	uart_tx(protection_register);			// send protection register value via uart
	uart_tx("\r\n");						// terminal new line and carriage return

}


void float_send(float c)
{

    volatile long int d;
	volatile  unsigned int hundreds, tens, units, tenths, hundredths, thousandths, tenthousandths,thousandth, ten_thousandths;
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
    sprintf(string, "%d%d.%d%d%d%d", tens, units, tenths, hundredths,thousandth,ten_thousandths);	// converT all parts of number to single string
	uart_tx(string);																				// send string via uart
}
