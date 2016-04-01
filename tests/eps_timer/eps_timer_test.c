/*
 EPS test code revised
 tested with oscilloscope
 output period : 50.07ms

 */

#include <EPS_MSP.h>


/********** MAIN **********/

void main(void)
{
	config_MSP430();
	
	__bis_SR_register(GIE);					// enables interrupts

	while(1);

}

/********** INTERRUPTS **********/

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
 if(cont==3){								// period = CCR0 * 2 * cont / clock => 50m = 50000*2*cont/(8*10^6) => cont = 3 (starts at 0)
	 P2OUT ^= 0x01;							// toggle P2.0 to determine frequency of timer output
	 cont = 0;								// reset cont
  }else{
	    cont ++;

  }


}

void config_MSP430(void){

	WDTCTL = WDTPW | WDTHOLD;				  // Stop watchdog timer
	P2DIR |= 0x01;							  // used to debug timer
	P5DIR |= BIT5;							  // used to debug clock, sets P5.5 as output
	P5SEL |= BIT5;							  // used to debug clock, sets P5.5 as SMCLK

    BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
    DCOCTL = CALDCO_8MHZ;

    P3SEL = 0x30;

	//timer
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 =50000;
	TACTL = TASSEL_2 + MC_3;                  // SMCLK, contmode

}
