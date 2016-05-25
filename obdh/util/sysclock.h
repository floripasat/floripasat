/*
 * sysclock.h
 *
 *  Created on: 25 de mai de 2016
 *      Author: mario
 */

#ifndef UTIL_SYSCLOCK_H_
#define UTIL_SYSCLOCK_H_

#include "driverlib.h"

char* sysclock_read(char* strbuff);
void  sysclock_setup(void);

#endif /* UTIL_SYSCLOCK_H_ */
