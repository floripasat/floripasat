/*
 * uG.h
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#ifndef INTERFACES_UG_H_
#define INTERFACES_UG_H_

#include <stdint.h>
#include "../hal/engmodel1.h"
#include "../util/crc.h"

void uG_encode_dataframe (char*     ugFrame,
						  char*    obdhData,
						  char*   radioData,
						  char*     epsData,
						  char*     imuData );

void uG_encode_crc ( char* ugFrame );


void send2uZed(void);

void uG_send(char* dataframe, uint16_t length);


#endif /* INTERFACES_UG_H_ */
