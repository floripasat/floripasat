/*
 * HAL_obdh.h
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#ifndef HAL_OBDH_H_
#define HAL_OBDH_H_

#include <msp430.h>


#define SYSLED_PIN          BIT4		// LED connected to P5.4 (p 32) - OBDH SYSTEM LED
#define SYSLED_PORT_DIR 	P5DIR
#define SYSLED_PORT_OUT    	P5OUT


#define LED_ON				1
#define LED_OFF				0




#endif /* HAL_OBDH_H_ */
