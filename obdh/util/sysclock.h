/*
 * sysclock.h
 *
 *  Created on: 25 de mai de 2016
 *      Author: mario
 */

#ifndef UTIL_SYSCLOCK_H_
#define UTIL_SYSCLOCK_H_

#include "driverlib.h"
#include "misc.h"

void  sysclock_setup(void);
float sysclock_read (void);
uint16_t sysclock_read_s  (void);
uint16_t sysclock_read_ms (void);
void  sysclock_tic(void);
float sysclock_toc(void);


#endif /* UTIL_SYSCLOCK_H_ */
