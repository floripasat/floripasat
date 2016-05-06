#include <msp430.h> 
#include "hal/obdh_engmodel1.h"
#include "util/uart.h"
#include "util/i2c.h"


void boot_setup(void);

volatile unsigned char EPS0[18];         // Allocate 18 byte of RAM
volatile unsigned char EPS1[18];         // Allocate 18 byte of RAM
volatile unsigned char EPS2[18];         // Allocate 18 byte of RAM
volatile unsigned char EPS3[18];         // Allocate 18 byte of RAM
volatile unsigned char EPS4[18];         // Allocate 18 byte of RAM
volatile unsigned char EPS5[18];         // Allocate 18 byte of RAM



void main(void) {

	boot_setup();
	
	sysled_toggle();
	i2c_read_epsFrame(EPS0,sizeof EPS0);
	sysled_toggle();

	__delay_cycles(10 * 1001);

	sysled_toggle();
	i2c_read_epsFrame(EPS1,sizeof EPS1);
	sysled_toggle();

	__delay_cycles(10 * 1001);

    for (;;) {

    	sysled_toggle();
    	i2c_read_epsFrame(EPS2,sizeof EPS2);
    	sysled_toggle();

    	__delay_cycles(10 * 1001);


    	sysled_toggle();
    	i2c_read_epsFrame(EPS3,sizeof EPS3);
    	sysled_toggle();

    	__delay_cycles(10 * 1001);


    	sysled_toggle();
    	i2c_read_epsFrame(EPS4,sizeof EPS4);
    	sysled_toggle();

    	__delay_cycles(10 * 1001);

    	sysled_toggle();
    	i2c_read_epsFrame(EPS5,sizeof EPS5);
    	sysled_toggle();

    	__delay_cycles(10 * 1001);










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


