/*
 * sysclock.c
 *
 *  Created on: 25 de mai de 2016
 *      Author: mario
 */

#include "sysclock.h"
#include "misc.h"

#define SYSCLOCK_INCREMENT 1000   // 1ms, since Timer clk source is internal 1Mhz

uint16_t sysclock_s  = 0;
uint16_t sysclock_ms = 0;


void sysclock_setup(void){

	//Start timer in continuous mode sourced by SMCLK
	Timer_A_initContinuousModeParam initContParam = {0};
	initContParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
	initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
	initContParam.timerClear = TIMER_A_DO_CLEAR;
	initContParam.startTimer = false;
	Timer_A_initContinuousMode(TIMER_A1_BASE, &initContParam);

	//Initiaze compare mode
	Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
										 TIMER_A_CAPTURECOMPARE_REGISTER_0
										 );

	Timer_A_initCompareModeParam initCompParam = {0};
	initCompParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
	initCompParam.compareInterruptEnable =
		TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
	initCompParam.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
	initCompParam.compareValue = SYSCLOCK_INCREMENT;
	Timer_A_initCompareMode(TIMER_A1_BASE, &initCompParam);

	Timer_A_startCounter(TIMER_A1_BASE,
						 TIMER_A_CONTINUOUS_MODE
						 );


}


char* sysclock_read(char* strbuff){

	sprintf(strbuff, "%u.%u", sysclock_s, sysclock_ms);
	return strbuff;

}



//******************************************************************************
//
//This is the TIMER1_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
void TIMER1_A0_ISR(void)
{
	sysclock_ms++;

	if (sysclock_ms == 1000){
		sysclock_s++;
		sysclock_ms = 0;
	}

}
