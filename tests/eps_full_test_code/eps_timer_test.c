/*
 EPS test code revised
 tested with oscilloscope
 output period : 50.07ms

 */
#include <eps_timer_test.h>
#include <eps_serial_test.h>
#include <eps_ADC_test.h>
#include <eps_onewire_test.h>
#include <eps_task_scheduler.h>
#include <msp430.h>

volatile float power[20];
volatile float voltage[20];
volatile float current[20];
volatile float mean_voltage = 0;
volatile float mean_current = 0;
volatile float mean_power = 0;
volatile unsigned int cont = 0;


/********** INTERRUPTS **********/

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	measurement_ADC();									// calls ADC measurement function
	volatile int d = 0;
	volatile int e = 0;

	d=adc5_lsb;											// take adc5 lsb
	e=adc5_msb;											// take ad5 msb
	e=e<<8;												// shift msb 8 bits to the left
	d=d+e;												// add msb and lsb to have the full 16 bit value

	current[cont] = 2*(d*0.00061035)/(200*0.0577);		// *2 voltage divider, 0.00061035 ADC resolution, 200 current sensor gain, 0.0577 shunt resistor resistance

	d=adc4_lsb;											// take adc4 lsb
	e=adc4_msb;											// take adc4 msb
	e=e<<8;												// shift msb 8 bits to the left
	d=d+e;												// add msb and lsb to have the full 16 bit value

	voltage[cont] = 2*(d*0.0006103515625);				// *2 voltage divider, 0.0006103515625 ADC resolution

	power[cont] = voltage[cont]*current[cont];

 if(cont==11){											// period = CCR0 * 2 * cont / clock => 50m = 50000*2*cont/(8*10^6) => cont = 3 (starts at 0)
//	 P2OUT ^= 0x01;										// toggle P2.0 to determine frequency of timer output
	 mean_calculation();
     measurement_data_DS2784();
     task_scheduler();
	 text();
	 cont = 0;											// reset cont
  }else{
	    cont ++;										// increments cont to achieve desired output period

  }


}

void config_MSP430_timer(void){

	WDTCTL = WDTPW | WDTHOLD;				  // Stop watchdog timer
//	P2DIR |= 0x01;							  // used to debug timer
//	P5DIR |= BIT5;							  // used to debug clock, sets P5.5 as output
//	P5SEL |= BIT5;							  // used to debug clock, sets P5.5 as SMCLK
    BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
    DCOCTL = CALDCO_8MHZ;					  // Set DCO
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 =50000;							  // timer A capture and compare register
	TACTL = TASSEL_2 + MC_3;                  // SMCLK, contmode
	__bis_SR_register(GIE);					  // enables interrupts

}

void mean_calculation(void)
{
	int i;
	mean_power = 0;
	mean_voltage = 0;
	mean_current = 0;
	for(i=0; i<cont; i++ )
	{
		mean_power = mean_power+ power[i];
		mean_voltage =mean_voltage+ voltage[i];
		mean_current =mean_current+current[i];
	}

	mean_power=mean_power/cont;
	mean_voltage=mean_voltage/cont;
	mean_current=mean_current/cont;
}
