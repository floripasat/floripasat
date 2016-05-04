#include <msp430.h> 
#include "hal/obdh_engmodel1.h"
#include "util/uart.h"


void boot_setup(void);



int main(void) {

	boot_setup();
	

    for (;;) {

    	sysled_toggle();

//    	uart_tx_hello();
    	uart_tx("Dado 1, 2, 3.");

    	__delay_cycles(10 * 100001);
    }


    // should never reach this point
	return 0;
}





void boot_setup(void) {

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	sysled_enable();
	uart_setup();
}


