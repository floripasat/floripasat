/*
 * fast_tasks.h
 *
 *  Created on: 8 de set de 2016
 *      Author: Fsat
 */

#ifndef FSAT_FSAT_TASKS_H_
#define FSAT_FSAT_TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "msp430.h"

#define LED_PORT_DIR      P5DIR
#define LED_PORT_OUT      P5OUT
#define LED_1             BIT4
#define LED_2             BIT4

#define BAUD_RATE                               9600


 void prvSetupHardware( void );
 void prvLed1Task( void *pvParameters );
 void prvLed2Task( void *pvParameters );



#endif /* FSAT_FSAT_TASKS_H_ */
