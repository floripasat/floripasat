/*
 * obdh.h
 *
 *  Created on: 30 de mai de 2016
 *      Author: mario
 */

// Interface with internal components of the OBDH SoC


#ifndef INTERFACES_OBDH_H_
#define INTERFACES_OBDH_H_

#include <msp430.h>


// Define some macros that allow us to direct-access the ADC12 calibration
// constants that we need. See device datasheet for the full TLV table memory
// mapping.

// Calibration constant for ADC 1.5-V Reference, Temp. Sensor 30°C
#define CALADC12_15V_30C        (*((unsigned int *)0x1A1A))

// Calibration constant for ADC 1.5-V Reference, Temp. Sensor 85°C
#define CALADC12_15V_85C        (*((unsigned int *)0x1A1C))

unsigned int temp;
volatile float temperatureDegC;
volatile float temperatureDegF;

void obdh_read(char* obdhData);
void obdh_temp_convert(unsigned int temp);
void obdh_temp_read(int temp);
void obdh_temp_setup(void);



#endif /* INTERFACES_OBDH_H_ */
