/*
 EPS test code revised
 tested with oscilloscope
 output period : 50.07ms

 */
#include <eps_timer_test.h>
#include <eps_serial_test.h>
#include <msp430.h>


unsigned int cont = 0;


/********** INTERRUPTS **********/

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
 if(cont==3){								// period = CCR0 * 2 * cont / clock => 50m = 50000*2*cont/(8*10^6) => cont = 3 (starts at 0)
//	 P2OUT ^= 0x01;							// toggle P2.0 to determine frequency of timer output
	 uart_tx("test");						// sends string "test" via UART
	 cont = 0;								// reset cont
  }else{
	    cont ++;							// increments cont to achieve desired output period

  }


}

void config_MSP430_timer(void){

	WDTCTL = WDTPW | WDTHOLD;				  // Stop watchdog timer
//	P2DIR |= 0x01;							  // used to debug timer
//	P5DIR |= BIT5;							  // used to debug clock, sets P5.5 as output
//	P5SEL |= BIT5;							  // used to debug clock, sets P5.5 as SMCLK
    BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
    DCOCTL = CALDCO_8MHZ;					  // Set DCO
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 =50000;							  // timer A capture and compare register
	TACTL = TASSEL_2 + MC_3;                  // SMCLK, contmode
	__bis_SR_register(GIE);					  // enables interrupts

}
