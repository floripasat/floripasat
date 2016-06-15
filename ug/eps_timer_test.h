/*
 * eps_timer_test.h
 *
 *  Created on: 11/04/2016
 *      Author: Bruno Eiterer
 *
 *      uses these guidines: http://umich.edu/~eecs381/handouts/CHeaderFileGuidelines.pdf
 */

#ifndef EPS_TIMER_TEST_H_
#define EPS_TIMER_TEST_H_


extern volatile int avc_msb;
extern volatile int avc_lsb;
extern volatile int vr_msb1;
extern volatile int vr_lsb1;
extern volatile int vr_msb2;
extern volatile int vr_lsb2;
extern volatile int tr_msb;
extern volatile int tr_lsb;
extern volatile int cr_msb;
extern volatile int cr_lsb;
extern volatile int acr_msb;
extern volatile int acr_lsb;
extern volatile unsigned int RG_Protection;
extern volatile unsigned char EPSData[18];
extern volatile int temp[2];


void make_frame(void);

#endif /* EPS_TIMER_TEST_H_ */
