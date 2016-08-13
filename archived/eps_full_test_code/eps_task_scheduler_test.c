#include <msp430.h>
#include <eps_task_scheduler.h>


void task_scheduler(void);

volatile unsigned int LCA = 0;						// variable used to determine the load current action.
volatile float previous_power = 0;					// variable used to determine if previous LCA increased or decreased power
volatile float accumulated_current = 0;				// variable used to determine the accumulated current available on the battery


/*****************************************************************************/
/* - name: task_scheduler
 * - description: this function is used as a simple task scheduler. It controls the battery voltage by changing the current drained by the load.
 *  The action on the load current is determined by a comparison between the current measured power and a previous measured power. If the previous power is higher, than the load current is decreased.
 *  Else, the load current is increased.
 */

void task_scheduler(void){

	if(mean_current>0.02)
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
