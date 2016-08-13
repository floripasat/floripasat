
//******************************************************************************
//   MSP430F6659 Demo - eUSCI_A1, 9600 UART, SMCLK, LPM0, Echo with over-sampling
//
//   Description: transmits to UART_A1 text: radio_Test
//   Baud rate divider with UCBRx = 1MHz/(16*9600) = ~6.8
//   ACLK = REFO = ~32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   See User Guide for baud rate divider table

//
//               MSP430F6659
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |     P8.2/UCA1TXD|------------>
//            |                 | 9600 - 8N1
//            |                 |
//
//  Sara
// OBDH Test
// 18/03/2016
//******************************************************************************
#include <msp430.h>

//serial functions
void UART_TX(char * tx_data);
void Radio_TX(void);


int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    P8SEL |= 0x04;                            // Assign P8.2 to UCA1TXD
    P8DIR |= 0x04;                            // P8.2 to output

  UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA1CTL1 |= UCSSEL_2;                     // SMCLK
  UCA1BR0 = 6;                              // 1MHz 9600 (see User's Guide)
  UCA1BR1 = 0;                              // 1MHz 9600
  UCA1MCTL = UCBRS_0 | UCBRF_13 | UCOS16;   // Modln UCBRSx=0, UCBRFx=0,
                                            // over sampling
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**


  while(1) {
	  while (!(UCA1IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
	     Radio_TX();                          // Radio trasmitter
	      __delay_cycles(10000);
  }

}

/************************************************************************/
/*  - name: UART_TX
 *  - Description:  transmits to UART_A1  char vector
 *  - input data:   char * tx_data
 *  - output data:  --
 ***********************************************************************/

void UART_TX(char * tx_data)              // Define a function which accepts a character pointer to an array
{
	unsigned int i=0;
	while(tx_data[i])                     // Increment through array, look for null pointer (0) at end of string
	  {
	     while ((UCA1STAT & UCBUSY));     // Wait if line TX/RX module is busy with data
	     UCA1TXBUF = tx_data[i];          // Send out element i of tx_data array on UART bus
	     i++;                             // Increment variable for array address
	  }
}

/************************************************************************/
/*  - name: Radio_TX
 *  - Description:  Text Test
 *  - input data:  --
 *  - output data: --
 ***********************************************************************/


void Radio_TX(void){


 UART_TX("***********************\r\n");
 UART_TX("*  Radio Transmitter  *\r\n");
 UART_TX("***********************\r\n");
 UART_TX(" ~~ CC1125 ~~\r\n");

	}

