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
#define _64_uSEC			0x07
#define _512_uSEC			0x06
#define _2_mSEC				0x27
#define _8_2_mSEC			0x05
#define _15_6_mSEC			0x26
#define _32_8_mSEC			0x04
#define _250_mSEC			0x25
#define _524_3_mSEC			0x03
#define _1_SEC				0x24
#define _8_4_SEC			0x02
#define _16_SEC				0x23
#define _134_SEC			0x01
#define _4_MIN_16_SEC		0x22
#define _8_MIN_16_SEC		0x21
#define _30_MIN_47_5_SEC	0x00
#define _18_H_12_MIN_16_SEC	0x20


#include <msp430.h>

void watchdog_setup(char, char);
void wdt_reset_counter(void);
void wdt_hold_counter(void);
void wdt_release_counter(void);
void system_reboot(void);


#endif /* UTIL_WATCHDOG_H_ */
