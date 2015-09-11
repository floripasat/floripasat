/* Floripa-Sat EPS I2C code


*/


#include <msp430.h>
#include "EPS_definitions.h"

#define NUM_BYTES  1                        // How many bytes?
//**** Please note this value needs to be the same as NUM_BYTES_RX in the
//     associated master code. This definition lets the slave know when to
//     switch from RX interrupt sources to TX interrupt sources. This is
//     important since the interrupt vectors are shared by TX and RX flags.

volatile unsigned char TXByteCtr, RXByteCtr, RX = 0;
unsigned char *PTxData;                     // Pointer to TX data
unsigned char *PRxData;                     // Pointer to RX data
volatile unsigned char RxBuffer[8];       // Allocate 10 byte of RAM
int SLV_Data[47] =

	{
		start_byte,							// '#' character

		//----- ADC DATA -----//

		header_start_byte,					// '%' character
		0x41,								// 'A' character
		0x44,								// 'D' character
		0x43,								// 'C' character

		adc0_msb,							// ADC channel 0 data
		adc0_lsb,

		adc1_msb,							// ADC channel 1 data
		adc1_lsb,

		adc2_msb,							// ADC channel 2 data
		adc2_lsb,

		adc3_msb,							// ADC channel 3 data
		adc3_lsb,

		adc4_msb,							// ADC channel 4 data
		adc4_lsb,

		adc5_msb,							// ADC channel 5 data
		adc5_lsb,

		adc6_msb,							// ADC channel 6 data
		adc6_lsb,

		adc7_msb,							// ADC channel 7 data
		adc7_lsb,

		//----- MSP TEMPERATURE SENSOR DATA -----//

		msp_ts_msb,							// MSP internal temperature sensor data
		msp_ts_lsb,

		//----- BATTERY MONITOR DATA -----//

		header_start_byte,					// '#' character
		0x42,								// 'B' character
		0x41,								// 'A' character
		0x54,								// 'T' character

		avc_msb, 							// average current data
		avc_lsb,

		tr_msb,								// temperature register data
		tr_lsb,

		vr_msb,								// voltage register data
		vr_lsb,

		cr_msb,								// current register data
		cr_lsb,

		acr_msb,							// accumulated current register data
		acr_lsb,

		//----- STATUS AMD CRC DATA ----//

		fault,								// battery charger fault byte

		mppt_st,							// mppt status byte

		0,								// voltage regulators status byte

		crc,								// cyclic redundancy check byte

		end_byte							// '!' byte

		};





void USCI_SLAVE_SETUP(void);
void Setup_RX(void);
void Receive(void);

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4DIR = 0Xff;

  while(1){
  USCI_SLAVE_SETUP();
  P4OUT = RxBuffer[6];
  }
}

//------------------------------------------------------------------------------
// The USCI_B0 data ISR is used to move data from MSP430 memory to the
// I2C master. PTxData points to the next byte to be transmitted, and TXByteCtr
// keeps track of the number of bytes transmitted.
//------------------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCIAB0TX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  if(RX == 0){ UCB0TXBUF = SLV_Data[TXByteCtr];      // Transmit data at address PTxData
  TXByteCtr++;                              // Increment TX byte counter
  }
  if(RX == 1){*PRxData++ = UCB0RXBUF;       // Move RX data to address PRxData
  RXByteCtr++;                              // Increment RX byte count
  if(RXByteCtr >= NUM_BYTES){               // Received enough bytes to switch
  RX = 0;                                   // to TX?
  IE2 &= ~UCB0RXIE;
  IE2 |= UCB0TXIE;
  RXByteCtr = 0;
  }
  }
}

//------------------------------------------------------------------------------
// The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to do
// processing in the main program after data has been transmitted. LPM0 is
// only exit in case of a (re-)start or stop condition when actual data
// was transmitted.
//------------------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCIAB0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  if(RX == 0){ UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
  if (TXByteCtr)                            // Check TX byte counter
   __bic_SR_register_on_exit(CPUOFF);       // Exit LPM0 if data was
}                                           // transmitted
  if(RX == 1){UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear interrupt flags
}
}
void Setup_RX(void){
  __disable_interrupt();
  RX = 1;
  IE2 &= ~UCB0TXIE;                         // Disable TX interrupt
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable STT and STP interrupt
  IE2 |= UCB0RXIE;                          // Enable RX interrupt

}

void Receive(void){
    PRxData = (unsigned char *)RxBuffer;    // Start of RX buffer
    RXByteCtr = 0;                          // Clear RX byte count
    TXByteCtr = 0;
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until master
                                            // finishes TX
}
void USCI_SLAVE_SETUP(void){
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  Setup_RX();
  Receive();
}



