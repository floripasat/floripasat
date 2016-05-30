/*
 * eps.c
 *
 *  Created on: 11 de mai de 2016
 *      Author: mario
 */

#include "eps.h"

void eps_read(char* imuData){

	imuData[0] = '{';
	imuData[1] = '{';
	imuData[2] = '{';
	int i =0;
	for (i=0; i<17; i++){
		imuData[i] = i;
	}
	imuData[0] = '}';
	imuData[0] = '\n';
	imuData[0] = '\r';

	__delay_cycles(DELAY_100_MS_IN_CYCLES);

//	i2c_read_epsFrame(EPS_data_buffer,EPS_DATA_LENGTH);
//	frame2string(EPS_data_buffer,Debug_EPS_Data, sizeof Debug_EPS_Data); //TODO rm
//	debug(Debug_EPS_Data);



}


