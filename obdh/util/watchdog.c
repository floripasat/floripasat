/*
 * watchdog.c
 *
 *  Created on: 11 de mai de 2016
 *      Author: mario
 */

#include "watchdog.h"

void watchdog_setup(void) {

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

}
