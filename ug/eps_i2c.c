#include <msp430.h>
#include <eps_i2c.h>


unsigned char *PTxData;                     // Pointer to TX data
unsigned int TXByteCtr;
volatile unsigned char EPSData[18] = {0};





//------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move data from MSP430 memory to the
// I2C master. PTxData points to the next byte to be transmitted, and TXByteCtr
// keeps track of the number of bytes transmitted.
//------------------------------------------------------------------------------

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{

     if (TXByteCtr == 0)
         PTxData = (unsigned char *)EPSData;      // Start of TX buffer
     if(TXByteCtr++ < 18){
         UCB0TXBUF = *PTxData++;                     // Transmit data at address PTxData
     	 __delay_cycles(10000);}
     else
         TXByteCtr = 0;
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
