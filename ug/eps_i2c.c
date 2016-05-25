#include <msp430.h>
#include <eps_i2c.h>
#include <misc.h>


unsigned char *PTxData;                     // Pointer to TX data
unsigned int TXByteCtr;
unsigned char EPSData[18] = {0};

unsigned char FormatedEPSData[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};
unsigned char time_string[5];
unsigned int time=1;



//------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move data from MSP430 memory to the
// I2C master. PTxData points to the next byte to be transmitted, and TXByteCtr
// keeps track of the number of bytes transmitted.
//------------------------------------------------------------------------------

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void) {
	wdt_reset_counter();

	if (TXByteCtr == 0)
		PTxData = (unsigned char *) EPSData;      // Start of TX buffer


	if (TXByteCtr++ < 18) {
		UCB0TXBUF = *PTxData++;              // Transmit data at address PTxData
		__delay_cycles(10000);

	} else {
		TXByteCtr = 0;
//		int_to_char(time, time_string, sizeof time_string);
//		frame_to_string(EPSData, FormatedEPSData, sizeof FormatedEPSData);
//		uart_tx(time_string);
//		uart_tx(" , ");
//		uart_tx(FormatedEPSData);
//		uart_tx("\r\n");
		time++;

	}
}

/*
//------------------------------------------------------------------------------
// The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to do
// processing in the main program after data has been transmitted. LPM0 is
// only exit in case of a (re-)start or stop condition w hen actual data
// was transmitted.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
//  if (TXByteCtr)                            // Check TX byte counter
  //  __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0 if data was
}                                           // transmitted
*/
