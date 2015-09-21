/*
 * EPS_protocol.h
 *
 *  Created on: 21/09/2015
 *      Author: Bruno Eiterer
 */



#ifndef EPS_PROTOCOL_H_
#define EPS_PROTOCOL_H_

//---- Variables of MSP430 internal ADC ----//

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


//---- Variables of DS2784 ----//

extern volatile int msp_ts_msb;
extern volatile int msp_ts_lsb;
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




void write_data_package(void);



#endif /* EPS_PROTOCOL_H_ */
