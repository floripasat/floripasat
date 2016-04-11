#include <msp430.h> 
#include <eps_serial_test.h>
#include <eps_timer_test.h>



void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    config_MSP430_UART();
    config_MSP430_timer();
	while(1);

}
