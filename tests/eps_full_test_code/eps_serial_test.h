/*
 * eps_serial_test.h
 *
 *  Created on: 11/04/2016
 *      Author: Bruno Eiterer
 */

#ifndef EPS_SERIAL_TEST_H_
#define EPS_SERIAL_TEST_H_


/********** ADC VARIABLES **********/

extern volatile int adc0_msb;
extern volatile int adc0_lsb;
extern volatile int adc1_msb;
extern volatile int adc1_lsb;
extern volatile int adc2_msb;
extern volatile int adc2_lsb;
extern volatile int adc3_msb;
extern volatile int adc3_lsb;
extern volatile int adc4_msb;
extern volatile int adc4_lsb;
extern volatile int adc5_msb;
extern volatile int adc5_lsb;
extern volatile int adc6_msb;
extern volatile int adc6_lsb;
extern volatile int adc7_msb;
extern volatile int adc7_lsb;
extern volatile int msp_ts_msb;
extern volatile int msp_ts_lsb;


/********** UART functions **********/

void uart_tx(char *tx_data);
void config_MSP430_UART(void);
void text(void);
void float_send(float c);

#endif /* EPS_SERIAL_TEST_H_ */
