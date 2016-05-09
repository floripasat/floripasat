#include <msp430.h> 
#include "hal/obdh_engmodel1.h"
#include "util/uart.h"
#include "util/i2c.h"


void boot_setup(void);


unsigned char EPSData[18];         // Allocate 18 byte of RAM



void main(void) {


	boot_setup();

    while(1) {
    	sysled_toggle();
    	i2c_read_epsFrame(EPSData,sizeof EPSData);
    	sysled_toggle();

    	__delay_cycles(1000);

    }
}

void boot_setup(void){

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	sysled_enable();
	uart_setup(9600);
	i2c_setup(EPS);
	i2c_setup(MPU);
	__enable_interrupt();
}
