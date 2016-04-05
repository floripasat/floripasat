#include <msp430.h>


void task_scheduler(void);

volatile int adc4_msb=0x0B;
volatile int adc4_lsb=0x51;
volatile int adc5_msb=0x00;
volatile int adc5_lsb=0x00;

volatile float volt = 0;
volatile float curr = 0;
volatile float previous_power = 0.2;
volatile float mean_power = 0;
volatile float mean_voltage = 0;
volatile float mean_current = 0;

volatile unsigned int LCA = 0;						// variable used to determine the load current action
volatile float accumulated_current= 0.57; 				// variable used to save the battery accumulated current value


/*************************************************************************/
//                        main
/************************************************************************/

int main(void)
{
	task_scheduler();
}

/*****************************************************************************/
/* - name: task_scheduler
 * - description: this function is used as a simple task scheduler. It controls the battery voltage by changing the current drained by the load.
 *  The action on the load current is determined by a comparison between the current measured power and a previous measured power. If the previous power is higher, than the load current is decreased.
 *  Else, the load current is increased.
 */

void task_scheduler(void){

	volatile int d = 0;
	volatile int e = 0;

	d=adc5_lsb;											// take adc5 lsb
	e=adc5_msb;											// take ad5 msb
	e=e<<8;												// shift msb 8 bits to the left
	d=d+e;												// add msb and lsb to have the full 16 bit value
	curr = 2*(d*0.00061035)/(200*0.0577);				// *2 voltage divider, 0.00061035 ADC resolution, 200 current sensor gain, 0.0577 shunt resistor resistance

	d=adc4_lsb;											// take adc4 lsb
    e=adc4_msb;											// take adc4 msb
	e=e<<8;												// shift msb 8 bits to the left
	d=d+e;												// add msb and lsb to have the full 16 bit value
	volt = 2*(d*0.0006103515625);						// *2 voltage divider, 0.0006103515625 ADC resolution

	mean_power = volt*curr;

	if(curr>0.02)
	{
		if(previous_power<mean_power)					// determine if previous load current action increased the input power
	    	{
			LCA = 0;									// set action to decrease load current (increase battery voltage)
	    	}
		else
		{
			if(previous_power>mean_power){				// determine if previous load current action decreased the input power
					LCA = 1;							// set action to increase load current (decrease battery voltage)
	    		}
			else{
					LCA = 4;							// default LCA
				}
		}
	}

	else{
		if(accumulated_current<0.55)					// determine if battery voltage is lower than 2.6V
		{
			LCA = 3;									// set action to turn off load
		}
		if(accumulated_current>0.56)					// determine if battery voltage is higher than 2.6V
		{
			LCA = 2;									// set action as eclipse (load current on)
		}
	}
	previous_power = mean_power;						// saves current input power for next iteration

}
