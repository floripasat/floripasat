/*
 EPS test code revised
 tested with oscilloscope
 output period : 50.07ms

 */
#include <eps_timer_test.h>
#include <eps_onewire_test.h>
#include <eps_i2c.h>
#include <msp430.h>

volatile unsigned int cont = 0;


/********** INTERRUPTS **********/

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{

	if(cont==11){											// period = CCR0 * 2 * cont / clock => 50m = 50000*2*cont/(8*10^6) => cont = 3 (starts at 0)
//	 P2OUT ^= 0x01;											// toggle P2.0 to determine frequency of timer output
     measurement_data_DS2784();
     make_frame();											//
	 cont = 0;												// reset cont
  }else{
	    cont ++;											// increments cont to achieve desired output period

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
