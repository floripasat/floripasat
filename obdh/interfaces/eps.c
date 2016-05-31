/*
 * eps.c
 *
 *  Created on: 11 de mai de 2016
 *      Author: mario
 */

#include "eps.h"

void eps_read(char* data){
	i2c_read_eps(data,EPS_DATA_LENGTH);
}


