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
//#define DELAY_1_MS_IN_CYCLES	    1049	// @ 1Mhz Internal clock	~1.040 ms
#define DELAY_1_MS_IN_CYCLES	    1010	// @ 1Mhz Internal clock	~1.001 ms

#define DELAY_9_MS_IN_CYCLES	   9210	    // @ 1Mhz Internal clock	~10 ms

#define DELAY_10_MS_IN_CYCLES	   10220	// @ 1Mhz Internal clock	~10 ms
//#define DELAY_10_MS_IN_CYCLES	   10486	// @ 1Mhz Internal clock	~10.27 ms

#define DELAY_99_MS_IN_CYCLES	  101390	// @ 1Mhz Internal clock	~100 ms

#define DELAY_50_MS_IN_CYCLES	  51200	    // @ 1Mhz Internal clock	~100 ms

#define DELAY_100_MS_IN_CYCLES	  102400	// @ 1Mhz Internal clock	~100 ms
//#define DELAY_100_MS_IN_CYCLES	  104858	// @ 1Mhz Internal clock	~102.5 ms


#define DELAY_1_S_IN_CYCLES		 1317472	// @ 1Mhz Internal clock	~1.026  s
//#define DELAY_1_S_IN_CYCLES	 1048576	// @ 1Mhz Internal clock	~1.026  s

//#define DELAY_5_S_IN_CYCLES	5242880		// @ 1Mhz Internal clock
#define DELAY_5_S_IN_CYCLES		5130019	    // @ 1Mhz Internal clock	~5.00X s

#define DELAY_10_S_IN_CYCLES	10000000	// @ 1Mhz Internal clock	~10.25  s
#define DELAY_60_S_IN_CYCLES	62914560	// @ 1Mhz Internal clock	~61.52	s


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
