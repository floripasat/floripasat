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

#define UART_DEBUG_RX		1
#define UART_DEBUG_TX		0

#define SECOND_IN_CYCLES	    400
#define MILISECOND_IN_CYCLES	400

#define  EPS_DATA_LENGTH 	18
#define  MPU_DATA_LENGTH 	14
#define  BEACON_DATA_LENGTH 3
#define  FSAT_FRAME_LENGTH	38
#define  MISC_INFO_LENGHT 	4

#define  STT_BYTE 		0xAC
#define  END_BYTE		0xFF

#define INFO_STT_BYTE  	0x55
#define INFO_END_BYTE	0xFF

#define IMU_ACC_RANGE	2.0
#define IMU_GYR_RANGE	2.0


#endif /* HAL_OBDH_H_ */
