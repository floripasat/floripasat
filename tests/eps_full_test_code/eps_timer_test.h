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

extern volatile int adc4_msb;
extern volatile int adc4_lsb;
extern volatile int adc5_msb;
extern volatile int adc5_lsb;

void config_MSP430_timer(void);

void mean_calculation(void);


#endif /* EPS_TIMER_TEST_H_ */
