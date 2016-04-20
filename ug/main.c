#include <msp430.h> 
#include "eps_serial_test.h"
#include "eps_timer_test.h"
#include "eps_onewire_test.h"



void main(void) {
   WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
   P1DIR |= BIT4;
   P1OUT |= BIT4;
   BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
   DCOCTL = CALDCO_8MHZ;

   config_MSP430_UART();
   config_MSP430_ONE_WIRE();
   config_DS2784();

   while(1){
	   measurement_data_DS2784();
	   text();
   }


}
