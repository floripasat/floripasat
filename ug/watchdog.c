/*
 * watchdog.c
 *
 *  Created on: 11 de mai de 2016
 *      Author: mario
 */

#include "watchdog.h"

void watchdog_setup(char mode, char time2trigger) {
	WDTCTL = WDTPW + mode + time2trigger;
	if (mode == INTERVAL)
		 IE1 |= WDTIE;                             // Enable WDT interrupt
}

void wdt_reset_counter(void){
	WDTCTL = (WDTCTL & 0x00FF) + WDTPW + WDTCNTCL;
	WDTCTL = ((WDTCTL & 0x00FF) + WDTPW) & ~WDTCNTCL;

}

void wdt_hold_counter(void){
	WDTCTL = (WDTCTL & 0x00FF) + WDTPW + WDTHOLD;
}

void wdt_release_counter(void){
	WDTCTL = ((WDTCTL & 0x00FF) + WDTPW) & ~WDTHOLD;
}

void reboot(void){
	WDTCTL = 0x00;
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void){
	P1OUT ^= BIT6;

//	if(IFG1 & WDTIFG){
//	}else if(IFG1 & NMIIFG){
//
//	}
}
