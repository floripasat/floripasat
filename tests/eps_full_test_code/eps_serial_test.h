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

/********** DS2784 VARIABLES **********/

extern volatile int avc_msb;
extern volatile int avc_lsb;
extern volatile int vr_msb;
extern volatile int vr_lsb;
extern volatile int tr_msb;
extern volatile int tr_lsb;
extern volatile int cr_msb;
extern volatile int cr_lsb;
extern volatile int acr_msb;
extern volatile int acr_lsb;

volatile unsigned int RG_Protection;

/********** UART functions **********/

void uart_tx(char *tx_data);
void config_MSP430_UART(void);
void text(void);
void float_send(float c);

#endif /* EPS_SERIAL_TEST_H_ */
