#include <msp430.h> 
#include <eps_serial_test.h>
#include <eps_timer_test.h>
#include <eps_ADC_test.h>
#include <eps_onewire_test.h>



void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    config_MSP430_ADC();
    config_MSP430_UART();
    config_MSP430_timer();
    config_MSP430_ONE_WIRE();
    config_DS2784();
	while(1);

}
