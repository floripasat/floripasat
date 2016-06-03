/*
 * watchdog.h
 *
 *  Created on: 11 de mai de 2016
 *      Author: mario
 */

#ifndef UTIL_WATCHDOG_H_
#define UTIL_WATCHDOG_H_

#include <msp430.h>

//mode
#define INTERVAL			0x10
#define WATCHDOG			0x00

//time to trigger
#define _1_2_SEC			0x04
#define _188_mSEC			0x05
#define _11_8_mSEC			0x06
#define _4_1_mSEC			0x00
#define _1_5_mSEC			0x07
#define _1_mSEC				0x01
#define _64_uSEC			0x02
#define _8_uSEC				0x03

#include <msp430.h>

void watchdog_setup(char mode, char time2trigger);
void wdt_reset_counter(void);
void wdt_hold_counter(void);
void reboot(void);



#endif /* UTIL_WATCHDOG_H_ */
