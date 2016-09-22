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


void prvSetupHardware( void );
void prvLedTask( void *pvParameters );
void prvUartTask( void *pvParameters );
void prvSetupUart( void );


#endif /* FSAT_FSAT_TASKS_H_ */
