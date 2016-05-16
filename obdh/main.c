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

/////////////frame to save into flash///////////////

[RTC_TIME][EPS DATA][BEACON DATA][IMU DATA]


*************************************************************************************/
#include <msp430.h> 
#include "hal/obdh_engmodel1.h"
#include "util/uart.h"
#include "util/misc.h"
#include "util/i2c.h"
#include "util/watchdog.h"
#include "util/flash.h"




unsigned int cycle_counter = 0;
char strbuff[100];
char EPS_data_buffer[EPS_DATA_LENGTH];
char MPU_data_buffer[MPU_DATA_LENGTH];
char BEACON_data_buffer[BEACON_DATA_LENGTH];
char FSAT_frame[FSAT_FRAME_LENGTH];

unsigned char String_FSAT_Frame[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
									 "0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//TODO rm
unsigned char String_EPS_Data[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//TODO rm
unsigned char String_MPU_Data[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//TODO rm
unsigned char String_BEACON_Data[] = {"0x00,0x00,0x00,0x00,0x00"};//TODO rm

void main_setup(void);
void concatenate_frame(void);

void main(void) {

	main_setup();

    while(1) {


    	cycle_counter++;
    	sysled_toggle();
    	debug("Main cycle init");
    	debug("Cycle: "); debug_inline( int2char(strbuff, cycle_counter) );



    	debug("Reading EPS init");
    	i2c_read_epsFrame(EPS_data_buffer,EPS_DATA_LENGTH);
//    	__delay_cycles(1000000);
    	frame2string(EPS_data_buffer,String_EPS_Data, sizeof String_EPS_Data); //TODO rm
    	debug(String_EPS_Data);
    	debug("Reading EPS done");



    	debug("Reading MPU init");
    	frame2string(MPU_data_buffer,String_MPU_Data, sizeof String_MPU_Data); //TODO rm
    	debug(String_MPU_Data);
    	debug("Reading MPU done");



    	debug("Reading Beacon init");
//    	frame2string(BEACON_data_buffer,String_BEACON_Data, sizeof String_BEACON_Data); //TODO rm
//    	debug(String_BEACON_Data); //TODO rm
//    	uart_tx_newline(); //TODO rm
    	debug("Reading Beacon done");


    	debug("Writing to flash init");
    	concatenate_frame();
    	flash_write(FSAT_frame,FSAT_FRAME_LENGTH);
    	debug("Writing to flash done");



    	debug("Sending to uZED/uG init");
    	debug("[FSAT] Sending FSAT FRAME TO uZED...\n\r"); //TODO rm
//    	uart_tx(FSAT_frame);
    	frame2string(FSAT_frame,String_FSAT_Frame, sizeof String_FSAT_Frame); //TODO rm
    	debug(String_FSAT_Frame);
    	debug("Sending to uZED/uG done");



    	__delay_cycles(1000001);

    	debug("Main cycle done.");

    }
}



void main_setup(void){

	watchdog_setup();
//	setup_clocks();
	uart_setup(9600);
	debug("\n\n\r[FSAT] MAIN booting...\n\r"); //TODO rm
	sysled_enable();
	flash_setup(BANK1_ADDR);
	i2c_setup(EPS);
	i2c_setup(MPU);
	__enable_interrupt();
	debug("[FSAT] MAIN boot completed.\n\r"); //TODO rm
}

void concatenate_frame(void){
	unsigned int i,j = 1;
	FSAT_frame[0] = START_BYTE;
	FSAT_frame[FSAT_FRAME_LENGTH - 1] = END_BYTE;
	for(i = 0;i < EPS_DATA_LENGTH;i++)
		FSAT_frame[j++] = EPS_data_buffer[i];
	for(i = 0;i < MPU_DATA_LENGTH;i++)
		FSAT_frame[j++] = MPU_data_buffer[i];
	for(i = 0;i < BEACON_DATA_LENGTH;i++)
		FSAT_frame[j++] = BEACON_data_buffer[i];
	debug("[FSAT] CRC...\n\r"); //TODO rm
	FSAT_frame[FSAT_FRAME_LENGTH - 2] = CRC8(FSAT_frame, sizeof FSAT_frame);
	debug("[FSAT] CRC DONE.\n\r"); //TODO rm
}


