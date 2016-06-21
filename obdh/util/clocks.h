/*
 * clocks.h
 *
 *  Created on: 21 de jun de 2016
 *      Author: mfrata
 */

#ifndef UTIL_CLOCKS_H_
#define UTIL_CLOCKS_H_

#include <msp430.h>

/**
 *     MAIN_clocks_setup will configure the ACLK clock to be sourced by the XT1 32768 Hz
 *  external Crystal. And the SMCLK to be sourced by the XT2 4 MHz Ext. Crystal. SMCLK
 *  out puts 1 MHz.
 *     The MCLK also is sourced by the 4 MHz crystal.
 */
//todo separate into one function to each clk
void MAIN_clocks_setup(void);


#endif /* UTIL_CLOCKS_H_ */
