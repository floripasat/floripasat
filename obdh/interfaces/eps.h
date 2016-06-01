/*
 * eps.h
 *
 *  Created on: 11 de mai de 2016
 *      Author: mario
 */

#ifndef INTERFACES_EPS_H_
#define INTERFACES_EPS_H_

#include "../util/debug.h"
#include "../util/i2c.h"
#include "../hal/engmodel1.h"

void eps_read(char* data);
char* eps_data2string(char* stringBuffer, char* epsData);

#endif /* INTERFACES_EPS_H_ */
