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
void prvEPSTask( void *pvParameters );
void prvIMUTask( void *pvParameters );
void prvTTCTask( void *pvParameters );
void prvSendUartTask( void *pvParameters );
void prvSetupUart( void );

#define EPS_DATA_LENGHT 16
#define IMU_DATA_LENGHT 10
#define TTC_DATA_LENGHT 30

#define UART_PACKAGE_LENGHT (EPS_DATA_LENGHT + IMU_DATA_LENGHT + TTC_DATA_LENGHT)

#define VERIFY_BEFORE_SEND 1 //verify if the data was changed since last sending

static char eps_data[EPS_DATA_LENGHT];
static char imu_data[IMU_DATA_LENGHT];
static char ttc_data[TTC_DATA_LENGHT];


#if VERIFY_BEFORE_SEND == 1
#define EPS_FLAG 1<<0
#define IMU_FLAG 1<<1
#define TTC_FLAG 1<<2

static unsigned char data_flags;
#endif

#endif /* FSAT_FSAT_TASKS_H_ */
