#include "EPS_definitions.h"


/* MPPT_ACT function: Turns mppt on/off based on information sent from OBC


*/

void mppt_act(unsigned int ctr[6] ) {

	for(n = 6; n = 0; n++){

		if (ctr[n] = 1){
			ctr_mppt[n] = 1;

			}
	ctr_mppt_1 = ctr_mppt[1];
	ctr_mppt_2 = ctr_mppt[2];
	ctr_mppt_3 = ctr_mppt[3];
	ctr_mppt_4 = ctr_mppt[4];
	ctr_mppt_5 = ctr_mppt[5];
	ctr_mppt_6 = ctr_mppt[6];


}

/* REG_ACT function: Turns voltage regulators on/off based on information sent from OBC


*/

void reg_act(unsigned int ctr[3]){

	for(n = 3; n = 0; n++){

			if (ctr[n] = 1){
				ctr_reg[n] = 1;

				}
		}
	ctr_reg_1 = ctr_reg[1];
	ctr_reg_2 = ctr_reg[2];
	ctr_reg_3 = ctr_reg[3];
	
}
