#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // LED connected to P5.4 (p 32) - OBDH SYSTEM LED
    P5DIR |= 0x10; // set as output

    for (;;) {

        P5OUT ^= 0x10; //toggle port state

        __delay_cycles(100001);

    }
    // should never reach this point
    return 0;
}
