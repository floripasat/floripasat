/*************************************************************************************
****************************OBDH main for the uG mission******************************
**************************************************************************************
		Taks:

/////////////////////SETUP/////////////////////

				***waiting for hw/sw boot***----->TBD
				*watchdog
				*clock setup
					-master clock
					-submaster clock
				*Timers setup-------------------->TBD
				*serial communication setup
					-uart Zboard
					-i2c eps
					-i2c mpu
					-spi beacon
					-spi memory
				*enable interrupts

/////////////////////MAIN LOOP////////////////////

				*Read 18 bytes from EPS
				*Read 5 bytes from beacon
				*Read 12 bytes from IMU
				*CRC
				*Concatenate the frame
				*Write the frame on memory
				*Send the frame to uZed via uart

////////////////////frame///////////////////////////

[START BYTE][EPS DATA][BEACON DATA][IMU DATA][CRC][END BYTE]



*************************************************************************************/
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
