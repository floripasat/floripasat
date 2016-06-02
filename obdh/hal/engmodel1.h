/*
 * HAL_obdh.h
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#ifndef HAL_OBDH_H_
#define HAL_OBDH_H_

#include <msp430.h>

#define LED_ON				1
#define LED_OFF				0

#define SYSLED_PIN          BIT4		// LED connected to P5.4 (p 32) - OBDH SYSTEM LED
#define SYSLED_PORT_DIR 	P5DIR
#define SYSLED_PORT_OUT    	P5OUT

#define PAYLOAD_ENABLE_PIN          BIT7		// Payload Enable Pin: P1.7 (p 41)
#define PAYLOAD_ENABLE_PORT_DIR		P1DIR
#define PAYLOAD_ENABLE_PORT_OUT		P1OUT

#define UART_DEBUG_RX		1
#define UART_DEBUG_TX		0


// TI Compiler pre-processor is overflowing in the multiplication of long delay times.
// eg. __delay_cycles(60 * DELAY_1_S_IN_CYCLES) is generating different results than __delay_cycles(DELAY_60_S_IN_CYCLES)
//
// Default Internal Clock: MCLK and SMCLK to 1.048576 MHz
// (Time elaps) = (# of cycles) / (frequency)
// 1 Cycle = 1.0 / 1.048576*10^6 seconds  @~1Mhz default clock


// @ 1Mhz internal ref, 1 cycle ~= 1 uS
// Delays below adjusted empiricaly based on tests/mesurements (to fix internal clock drift)
#define DELAY_1_MS_IN_CYCLES	     1010
#define DELAY_5_MS_IN_CYCLES	     5050
#define DELAY_10_MS_IN_CYCLES	    10220
#define DELAY_50_MS_IN_CYCLES	    51200
#define DELAY_100_MS_IN_CYCLES	   102400
#define DELAY_150_MS_IN_CYCLES	   153600
#define DELAY_1_S_IN_CYCLES	      1025538
#define DELAY_5_S_IN_CYCLES	      5130019
#define DELAY_60_S_IN_CYCLES     62914560
#define DELAY_120_S_IN_CYCLES   125829120


//TODO: watchdog max times are hardcoded in the main loop
//	  use global defines below, in the hal file.
//	  must reference the WD definitions, because WD delay
//	  have its own special unit and are not in cycles
//#define TIMESLOT_OBDH_MAX			WD_250_mSEC
//#define TIMESLOT_EPS_MAX			WD_250_mSEC
//#define TIMESLOT_IMU_MAX			WD_250_mSEC
//#define TIMESLOT_RADIO_MAX			WD_250_mSEC
//#define TIMESLOT_ENCODEFRAME_MAX	WD_250_mSEC
//#define TIMESLOT_UGHOST_MAX			WD_250_mSEC
//#define TIMESLOT_FLASH_MAX			WD_250_mSEC
//#define TIMESLOT_SLEEP_MAX			WD_250_mSEC


#define OBDH_DATA_LENGTH	 7	//  7 B of payload
#define EPS_DATA_LENGTH 	23	// 17 B of payload + 2 * 3 Bytes of SOF and EOF
#define IMU_DATA_LENGTH 	14	// 6 B to Acc + 6 B to Gyr
#define RADIO_DATA_LENGTH 	 4	// 2 B to counter + 2 B fo signal dB
#define UG_FRAME_LENGTH		41	// SOF(3) + Payload(35) + EOF(3)


//TODO: deprecated
#define BEACON_DATA_LENGTH   3
#define FSAT_FRAME_LENGTH	38
#define MISC_INFO_LENGHT 	 4

#define  STT_BYTE 		0xAC
#define  END_BYTE		0xFF

#define INFO_STT_BYTE  	0x55
#define INFO_END_BYTE	0xFF

#define IMU_ACC_RANGE	16.0
#define IMU_GYR_RANGE	2.0


#endif /* HAL_OBDH_H_ */
