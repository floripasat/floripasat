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

char  obdhData[OBDH_DATA_LENGTH];
char   imuData[IMU_DATA_LENGTH];
char   epsData[EPS_DATA_LENGTH];
char radioData[RADIO_DATA_LENGTH];

char ugFrame[UG_FRAME_LENGTH];


void main_setup(void);
void sleep(void);



void main(void) {

//	Can't debug log the init because UART, Timers, etc are not yet setup
	main_setup();	//Task 1
//	flash_reset_ptr();
	debug("Main setup done \t\t\t\t\t(Task 1)");
//	All tasks beyond this point MUST keep track/control of the watchdog (ONLY in the high level main loop).


    while(1) {		//Task 2


    	payloadEnable_toggle();
    	cycleCounter++;
    	sysled_on();
    	debug("Main loop init \t\t\t\t\t(Task 2)");
    	debug_uint( "Main Loop Cycle:",  cycleCounter);



    	debug("  OBDH internal read init \t\t\t\t(Task 2.1)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	obdh_read(obdhData);
    	debug( obdh_data2string(tmpStr, obdhData) );
    	debug_array("    OBDH data:", obdhData, OBDH_DATA_LENGTH);
    	debug("  OBDH read done");
    	wdt_reset_counter();



    	debug("  EPS read init \t\t\t\t\t(Task 2.2)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	eps_read(epsData);
    	debug_array("    EPS data:", epsData, EPS_DATA_LENGTH);
    	debug( eps_data2string(tmpStr, epsData) );
    	debug("  EPS read done");
    	wdt_reset_counter();



    	debug("  IMU read init \t\t\t\t\t(Task 2.3)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	imu_read(imuData);
    	debug_array("    IMU data", imuData, sizeof(imuData) );
    	debug( imu_data2string(tmpStr, imuData, IMU_ACC_RANGE, IMU_GYR_RANGE) );
    	debug("  IMU read done");
    	wdt_reset_counter();



    	debug("  RADIO read init \t\t\t\t\t(Task 2.4)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	readTransceiver(radioData);
    	debug("  RADIO read done");
    	wdt_reset_counter();



    	debug("  Encode dataframe init \t\t\t\t(Task 2.5)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	uG_encode_dataframe( ugFrame, obdhData, radioData, epsData, imuData );
    	uG_encode_crc(ugFrame);
    	debug("  Encode dataframe done");
    	wdt_reset_counter();



    	debug("  uG communication: sending data to host \t\t(Task 2.6)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	debug_array("    uG Frame:", ugFrame, UG_FRAME_LENGTH);
    	uG_send(ugFrame, UG_FRAME_LENGTH);
    	debug("  uG communication done");
    	wdt_reset_counter();



    	debug("  Flash write init \t\t\t\t\t(Task 2.7)");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	write2Flash(ugFrame,UG_FRAME_LENGTH);
    	debug("  Flash write done");
    	wdt_reset_counter();



    	debug("Main loop done");
    	sysled_off();
//    	Main loop active time: ~ 180 ms
    	payloadEnable_toggle();



//    	Main cycle total time must be 500ms (2Hz send rate to uG Host board)
//    	Therefore the board should sleep for (500 - main_active_time) ms
    	debug("Sleeping...");
    	watchdog_setup(WATCHDOG,WD_8_4_SEC);
    	sleep();
    	wdt_reset_counter();

    }
}


void sleep(void){
    __delay_cycles(DELAY_100_MS_IN_CYCLES);
    __delay_cycles(DELAY_100_MS_IN_CYCLES);
    __delay_cycles(DELAY_100_MS_IN_CYCLES);
    __delay_cycles(DELAY_10_MS_IN_CYCLES);
    __delay_cycles(DELAY_10_MS_IN_CYCLES);
}



void main_setup(void){

	if (DEBUG_LOG_ENABLE){
		watchdog_setup(WATCHDOG,WD_18_H_12_MIN_16_SEC); // 'ignore' watchog in Debug mode because uart_print extra delay disturbs time slots
	} else {
		watchdog_setup(WATCHDOG,WD_4_MIN_16_SEC);
	}

	sysclock_setup();
	uart_setup(9600);
	debug("  UART setup done");
	sysled_setup();
	payloadEnable_setup();
	debug("  Sysled setup done");
	flash_setup();
	debug("  Flash setup done");
	i2c_setup(EPS);
	debug("  EPS setup done");
	i2c_setup(MPU);
	debug("  OBDH temp setup done");
	obdh_setup();
	__enable_interrupt();
	imu_config();
    debug("  IMU setup done");
	SPI_Setup();
    debug("  SPI setup done");
	radio_Setup();
	debug("  radio setup done");
}



