/*
 * sysclock.c
 *
 *  Created on: 25 de mai de 2016
 *      Author: mario
 */

#include "sysclock.h"
#include "misc.h"

#define SYSCLOCK_INCREMENT 970   // 1ms, since Timer clk source is internal 1Mhz

uint16_t sysclock_s  = 0;
uint16_t sysclock_ms = 0;
uint16_t tic_s  = 0;
uint16_t tic_ms = 0;

void sysclock_setup(void){
	  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
	  TBCCR0 = SYSCLOCK_INCREMENT;
	  TBCTL = TBSSEL_2 | MC_1 | TBCLR;          // SMCLK, upmode, clear TBR
}


float sysclock_read(void){
	float sysclockNow = 0;
	sysclockNow = sysclock_s + (1.0/sysclock_ms);
	return sysclockNow;
}

uint16_t sysclock_read_s(void){
	return sysclock_s;
}

uint16_t sysclock_read_ms(void){
	return sysclock_ms;
}

void sysclock_tic(void){
	tic_s  = sysclock_s;
	tic_ms = sysclock_ms;
}

float sysclock_toc(void){
	float diff;
	diff = (sysclock_s-tic_s) + 1.0/(sysclock_ms-tic_ms);
	return diff;
}





//******************************************************************************
//
//This is the TIMER1_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERB0_VECTOR))) TIMERB0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	sysclock_ms++;

	if (sysclock_ms == 1000){
		sysclock_s++;
		sysclock_ms = 0;
	}

}
