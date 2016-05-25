/*
 EPS test code revised
 tested with oscilloscope
 output period : 50.07ms

 */
#include <eps_timer_test.h>
#include <eps_onewire_test.h>
#include <eps_i2c.h>
#include <watchdog.h>
#include <msp430.h>

volatile unsigned int cont = 0;
volatile unsigned int contb = 0;


/********** INTERRUPTS **********/

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
//	__bis_SR_register(GIE);
	if(cont==11){											// period = CCR0 * 2 * cont / clock => 50m = 50000*2*cont/(8*10^6) => cont = 3 (starts at 0)
		cont = 0;												// reset cont
		measurement_data_DS2784();
	    wdt_reset_counter();
		make_frame();
	    wdt_reset_counter();
  }else{
	    cont ++;											// increments cont to achieve desired output period
	    wdt_reset_counter();
  }
}

void make_frame(void)
{
	EPSData[0] = cr_msb;
	EPSData[1] = cr_lsb;
	EPSData[2] = vr_msb1;
	EPSData[3] = vr_lsb1;
	EPSData[4] = vr_msb2;
	EPSData[5] = vr_lsb2;
	EPSData[6] = tr_msb;
	EPSData[7] = tr_lsb;
	EPSData[8] = acr_msb;
	EPSData[9] = acr_lsb;
	EPSData[10] =  RG_Protection;
	EPSData[11] = 0;
	EPSData[12] = 0;
	EPSData[13] = 0;
	EPSData[14] = 0;
	EPSData[15] = 0;
	EPSData[16] = 0;

}

// Timer B0 interrupt service routine

#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
//	reboot();
	/*
	if(contb >= 29){
		contb = 0;
		reboot();
	}
	else{
		contb++;
	}
	*/
}

