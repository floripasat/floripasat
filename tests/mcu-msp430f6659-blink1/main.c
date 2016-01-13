#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    // LED connected to P1.1 (pin 35)
    P1DIR |= 0x02; // set as output

    for (;;) {

    	P1OUT ^= 0x02; //toggle port state

    	int i = 0;
    	for(i=0; i< 40000; i++); //delay

    }
    // should never reach this point
	return 0;
}

