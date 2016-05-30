/*************************************************************************************

	OBDH main for the uG mission

	Please consult README.txt for detailed information.
	http://www.floripasat.ufsc.br/
	VERSION: 0.7 - 2016-05-26

*************************************************************************************/



#include <msp430.h>
#include "driverlib.h"

#include "hal/engmodel1.h"

#include "util/codecs.h"
#include "util/crc.h"
#include "util/debug.h"
#include "util/flash.h"
#include "util/i2c.h"
#include "util/misc.h"
#include "util/sysclock.h"
#include "util/uart.h"
#include "util/watchdog.h"

#include "interfaces/obdh.h"
#include "interfaces/eps.h"
#include "interfaces/imu.h"
#include "interfaces/radio.h"
#include "interfaces/uG.h"


uint16_t cycleCounter = 0;
char tmpStr[200];

char obdhData[OBDH_DATA_LENGTH];
char  imuData[IMU_DATA_LENGTH];
char  epsData[EPS_DATA_LENGTH];

char ugFrame[UG_FRAME_LENGTH];

char radioData[];





//main tasks
void main_setup(void);

//TODO: move to appropriate file
void write2Flash(void);

//frames manipulation
void concatenate_frame(void);
void concatenate_info_frame(void);




void main(void) {

//	Can't debug log the init because UART, Timers, etc are not yet setup
	main_setup();	//Task 1
	debug("Main setup done \t\t\t\t(Task 1)");
//	All tasks beyond this point MUST keep track/control of the watchdog (ONLY in the high level main loop).


    while(1) {		//Task 2

    	debug("Main loop init \t\t\t\t(Task 2)");
    	cycleCounter++;
    	sysled_on();
    	debug_uint( "Main Loop Cycle:",  cycleCounter);


    	debug("  OBDH internal read init \t\t\t\t(Task 2.1)");
    	//wdt init for obdh internal
    	obdh_read(obdhData);
    	debug_array("    OBDH data:", obdhData, OBDH_DATA_LENGTH);
    	debug("  OBDH read done");
    	wdt_reset_counter();



    	debug("  EPS read init \t\t\t\t(Task 2.2)");
    	//wdt init for eps
    	eps_read(epsData);
    	debug_array("    EPS data:", epsData, EPS_DATA_LENGTH);
    	debug("  EPS read done");
    	wdt_reset_counter(); // TODO: wdt tem que ser reinicializado e redefinido para o tempo
//    								  necessario até a proxima atividade "rastreada" por ele,
//									  não apenas reiniciado. Se não irá



    	debug("  IMU read init \t\t\t\t(Task 2.3)");
    	//wdt init for imu
    	imu_read(imuData);
    	debug_array("    IMU data", imuData, sizeof(imuData) );
    	debug( imu_data2string(tmpStr, imuData, IMU_ACC_RANGE, IMU_GYR_RANGE) );
    	debug("  IMU read done");
    	wdt_reset_counter();


//    	debug("-----------------------------------------------");
//    	debug("  RADIO read init \t\t\t\t(Task 2.4)");
//    	//wdt init for radio
//    	readTransceiver();
//    	debug("  RADIO read done");
//    	debug("-----------------------------------------------");
//    	wdt_reset_counter();


//    	write2Flash();


    	//    	send2uZed();
    	debug("  Sending data to uG/Host \t\t\t(Task 2.7)");
    	//wdt init for uG tx
//    	debug_array("    IMU decoding data", imuData, sizeof(imuData) );
//    	uG_send(frame_uG, sizeof(frame_uG));
//    	uart_tx("{{{aabbcc}\n\r");

    	uint8_t frameCRC8 = 6;
    	uG_encode_dataframe ( ugFrame, obdhData, radioData, epsData, imuData, frameCRC8 );
    	debug_array("    uG Frame:", ugFrame, UG_FRAME_LENGTH);
    	uG_send(ugFrame, UG_FRAME_LENGTH);

//    	uart_tx("{{{");
//    	int i;
//    	for (i=0; i<sizeof(frame_uG); i++){
//    		uart_tx_char( frame_uG[i] );
//    	}
//    	uart_tx("}\n\r");

    	debug("  uG communication done");
    	wdt_reset_counter();



    	debug("Main loop done");

    	debug("Sleeping...");
    	sysled_off();
//    	__delay_cycles(DELAY_1_S_IN_CYCLES);
    	__delay_cycles(DELAY_5_S_IN_CYCLES);
    }
}



void main_setup(void){
	watchdog_setup(WATCHDOG,_18_H_12_MIN_16_SEC);
	sysclock_setup();
	uart_setup(9600);
	debug("  UART setup done");
	sysled_setup();
	payloadEnable_setup();
	debug("  Sysled setup done");
	flash_setup(BANK1_ADDR);
	debug("  Flash setup done");
	i2c_setup(EPS);
	debug("  EPS setup done");
	i2c_setup(MPU);
//	SPI_Setup();
	__enable_interrupt();
	imu_config();
//	radio_Setup();
	debug("  IMU setup done");
}






// TODO: move to appropriate file module
//void write2Flash(void){
//	debug("Writing to flash init");
//	concatenate_frame();
//	flash_write(FSAT_frame,FSAT_FRAME_LENGTH);
//	flash_save_ptr();
//	concatenate_info_frame();
//	flash_write(misc_info_frame,MISC_INFO_LENGHT);
//	flash_save_ptr();
//	debug("Writing to flash done");
//	wdt_reset_counter();
//}


//// TODO: move to appropriate file module
//void concatenate_frame(void){
//	unsigned int i,j = 1;
//	FSAT_frame[0] = STT_BYTE;
//	for(i = 0;i < EPS_DATA_LENGTH;i++)
//		FSAT_frame[j++] = EPS_data_buffer[i];
//	for(i = 0;i < IMU_DATA_LENGTH;i++)
//		FSAT_frame[j++] = imuData[i];
//	for(i = 0;i < BEACON_DATA_LENGTH;i++)
//		FSAT_frame[j++] = BEACON_data_buffer[i];
//	debug("CRC...\n\r"); //TODO rm
//	FSAT_frame[FSAT_FRAME_LENGTH - 2] = CRC8(FSAT_frame, sizeof FSAT_frame);
//	debug("CRC DONE.\n\r"); //TODO rm
//	FSAT_frame[FSAT_FRAME_LENGTH - 1] = END_BYTE;
//}


//// TODO: move to appropriate file module
//void concatenate_info_frame(void){
//	misc_info_frame[0] = INFO_STT_BYTE;
//	misc_info_frame[1] = (char)(cycleCounter >> 8);
//	misc_info_frame[2] = (char)(cycleCounter);
//	misc_info_frame[MISC_INFO_LENGHT - 1] = INFO_END_BYTE;
//}


