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
#include <limits.h>
#include "hal/obdh_engmodel1.h"
#include "util/uart.h"
#include "util/i2c.h"
#include "util/watchdog.h"






unsigned char EPSData[18];         // Allocate 18 byte of RAM
unsigned char FormatedEPSData[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};
unsigned char time_string[4];
unsigned int  time;
unsigned int  cycle_counter = 0;
char * strbuffer[100];

char EPS_data_buffer[EPS_DATA_LENGTH];


void main_setup(void);

void main(void) {

	main_setup();
	time = 1;

    while(1) {


    	cycle_counter++;
    	sysled_toggle();
    	uart_debug_tx("\n\r----------------------------------------------\n\r");
    	uart_debug_tx("[FSAT] Cycle: "); uart_debug_tx( int2char(cycle_counter) ); uart_debug_tx_newline();


    	uart_debug_tx("[FSAT] Reading EPS...\n\r");
    	i2c_read_epsFrame(EPSData,sizeof EPSData);
    	__delay_cycles(10 * 2001);
    	int_to_char(time,time_string,sizeof time_string);
    	frame_to_string(EPSData,FormatedEPSData, sizeof FormatedEPSData);
    	uart_debug_tx(time_string);
    	uart_debug_tx(" , ");
    	uart_debug_tx(FormatedEPSData);
    	uart_debug_tx("\r\n");
    	uart_debug_tx("[FSAT] Reading EPS DONE.\n\r");


    }
}



void main_setup(void){

	watchdog_setup();
	uart_debug_setup(9600);
	uart_debug_tx("\n\n\r[FSAT] MAIN booting...\n\r");
	sysled_enable();
	i2c_setup(EPS);
	i2c_setup(MPU);
	__enable_interrupt();
	uart_debug_tx("[FSAT] MAIN boot completed.\n\r");
}

