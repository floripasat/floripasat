#include <msp430.h> 
#include "HAL_obdh.h"


void boot_setup(void);



/*
 * main.c
 */
int main(void) {

	boot_setup();
	

    for (;;) {

    	sysled_toggle();
    	__delay_cycles(100001);
    }


    // should never reach this point
	return 0;
}





void boot_setup(void) {

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	sysled_enable();

}


