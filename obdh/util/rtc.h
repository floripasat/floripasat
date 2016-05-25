/*
 * rtc_builtin.h
 *
 *  Created on: 23 de mai de 2016
 *      Author: mario
 */

#ifndef RTC_BUILTIN_H_
#define RTC_BUILTIN_H_

#include <msp430.h>

void RTCA_setup(void);
unsigned long RTCA_counter(void);

#endif /* RTC_BUILTIN_H_ */
