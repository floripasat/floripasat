/*
 * eps_onewire_test.h
 *
 *  Created on: 12/04/2016
 *      Author: Bruno Eiterer
 */

#ifndef EPS_ONEWIRE_TEST_H_


void config_DS2784(void);

void measurement_data_DS2784(void);

void outp(int bit);
int inp(void);
int OneWireReset(void);
void OneWireWrite(int bit);
int OneWireReadBit(void);
void OWWriteByte(int data);
int OWReadByte(void);

#endif /* EPS_ONEWIRE_TEST_H_ */
#define EPS_ONEWIRE_TEST_H_

