#include <eps_timer_test.h>
#include <eps_onewire_test.h>
#include <eps_i2c.h>
#include <watchdog.h>
#include <msp430.h>
#include <eps_serial.h>
#include <ADS1248.h>

volatile unsigned int cont = 0;
volatile unsigned int contb = 0;
volatile unsigned int z=0;

/********** INTERRUPTS **********/

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	__bis_SR_register(GIE);
	if(cont==11){											// period = CCR0 * 2 * cont / clock => 50m = 50000*2*cont/(8*10^6) => cont = 3 (starts at 0)
		cont = 0;												// reset cont
		measurement_data_DS2784();
	    wdt_reset_counter();
		make_frame();
	    wdt_reset_counter();
	    for(z=0;z<10;z++)
	    {
	    	uart_tx(EPSData_beacon[z]);
	    	wdt_reset_counter();
	    }
  }
	else
  {
	    cont ++;											// increments cont to achieve desired output period
	    wdt_reset_counter();
  }
}

void make_frame(void)
{
	EPSData[0] = '{';
	EPSData[1] = '{';
	EPSData[2] = '{';
	EPSData[3] = cr_msb;
	EPSData[4] = cr_lsb;
	EPSData[5] = vr_msb1;
	EPSData[6] = vr_lsb1;
	EPSData[7] = vr_msb2;
	EPSData[8] = vr_lsb2;
	EPSData[9] = tr_msb;
	EPSData[10] = tr_lsb;
	EPSData[11] = acr_msb;
	EPSData[12] = acr_lsb;
	EPSData[13] =  RG_Protection;
	EPSData[14] = temp[0];
	EPSData[15] = temp[1];
	EPSData[16] = temp[2];
	EPSData[17] = 0;
	EPSData[18] = 0;
	EPSData[19] = 0;
	EPSData[20] = '}';
	EPSData[21] = '\n';
	EPSData[22] = '\r';

	EPSData_beacon[0] = '{';
	EPSData_beacon[1] = '{';
	EPSData_beacon[2] = '{';
	EPSData_beacon[3] = vr_msb1;
	EPSData_beacon[4] = vr_lsb1;
	EPSData_beacon[5] = vr_msb2;
	EPSData_beacon[6] = vr_lsb2;
	EPSData_beacon[7] = '}';
	EPSData_beacon[8] = '\n';
	EPSData_beacon[9] = '\r';
}

