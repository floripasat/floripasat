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

unsigned int cycle_counter = 0;
char EPS_data_buffer[EPS_DATA_LENGTH];
char MPU_data_buffer[MPU_DATA_LENGTH];
char BEACON_data_buffer[BEACON_DATA_LENGTH];
char FSAT_frame[FSAT_FRAME_LENGTH];

unsigned char String_FSAT_Frame[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
									 "0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//DEBUG
unsigned char String_EPS_Data[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//DEBUG
unsigned char String_MPU_Data[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//DEBUG
unsigned char String_BEACON_Data[] = {"0x00,0x00,0x00,0x00,0x00"};//DEBUG

void main_setup(void);
void concatenate_frame(void);

void main(void) {

	main_setup();

    while(1) {


    	cycle_counter++;
    	sysled_toggle();
    	uart_debug_tx("\n\r----------------------------------------------\n\r"); //DEBUG
    	uart_debug_tx("[FSAT] Cycle: ");
    	uart_debug_tx(aligned_right(int_to_char(cycle_counter)));
    	uart_debug_tx_newline(); //DEBUG


    	uart_debug_tx("[FSAT] Reading EPS...\n\r"); //DEBUG
    	i2c_read_epsFrame(EPS_data_buffer,EPS_DATA_LENGTH);
//    	__delay_cycles(1000000);
    	frame_to_string(EPS_data_buffer,String_EPS_Data, sizeof String_EPS_Data); //DEBUG
    	uart_debug_tx(String_EPS_Data); //DEBUG
    	uart_debug_tx_newline(); //DEBUG
    	uart_debug_tx("[FSAT] Reading EPS DONE.\n\r"); //DEBUG


    	uart_debug_tx("----------------------------------------------\n\r"); //DEBUG


    	uart_debug_tx("[FSAT] Reading MPU...\n\r"); //DEBUG

    	frame_to_string(MPU_data_buffer,String_MPU_Data, sizeof String_MPU_Data); //DEBUG
    	uart_debug_tx(String_MPU_Data); //DEBUG
    	uart_debug_tx_newline(); //DEBUG
    	uart_debug_tx("[FSAT] Reading MPU DONE.\n\r"); //DEBUG

    	uart_debug_tx("----------------------------------------------\n\r"); //DEBUG
/*
    	uart_debug_tx("[FSAT] Reading BEACON...\n\r"); //DEBUG

    	frame_to_string(BEACON_data_buffer,String_BEACON_Data, sizeof String_BEACON_Data); //DEBUG
    	uart_debug_tx(String_BEACON_Data); //DEBUG
    	uart_debug_tx_newline(); //DEBUG
    	uart_debug_tx("[FSAT] Reading BEACON DONE.\n\r"); //DEBUG

    	uart_debug_tx("[FSAT] CRC...\n\r"); //DEBUG
    	uart_debug_tx("[FSAT] CRC DONE.\n\r"); //DEBUG

    	uart_debug_tx("[FSAT] Writing TO FLASH...\n\r"); //DEBUG
    	uart_debug_tx("[FSAT] Writing DONE.\n\r"); //DEBUG
*/
    	uart_debug_tx("[FSAT] Sending FSAT FRAME TO uZED...\n\r"); //DEBUG
    	concatenate_frame();
//    	uart_tx(FSAT_frame);
    	frame_to_string(FSAT_frame,String_FSAT_Frame, sizeof String_FSAT_Frame); //DEBUG
    	uart_debug_tx(String_FSAT_Frame);
    	uart_debug_tx_newline(); //DEBUG
    	uart_debug_tx("[FSAT] SENT.\n\r"); //DEBUG



    	__delay_cycles(1000001);


    }
}



void main_setup(void){

	watchdog_setup();
//	setup_clocks();
	uart_setup(9600);
	uart_debug_tx("\n\n\r[FSAT] MAIN booting...\n\r"); //DEBUG
	sysled_enable();
	i2c_setup(EPS);
	i2c_setup(MPU);
	__enable_interrupt();
	uart_debug_tx("[FSAT] MAIN boot completed.\n\r"); //DEBUG
}

void concatenate_frame(void){
	unsigned int i,j = 1;
	FSAT_frame[0] = START_BYTE;
	FSAT_frame[FSAT_FRAME_LENGTH - 2] = CRC_BYTE;
	FSAT_frame[FSAT_FRAME_LENGTH - 1] = END_BYTE;
	for(i = 0;i < EPS_DATA_LENGTH;i++)
		FSAT_frame[j++] = EPS_data_buffer[i];
	for(i = 0;i < MPU_DATA_LENGTH;i++)
		FSAT_frame[j++] = MPU_data_buffer[i];
	for(i = 0;i < BEACON_DATA_LENGTH;i++)
		FSAT_frame[j++] = BEACON_data_buffer[i];

}
