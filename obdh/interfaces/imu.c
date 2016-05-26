/*
 * imu.c
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#include "imu.h"

void readImu(void){
//	debug("Reading MPU init");
//	i2c_IMU_read(MPU9150_ACCEL_XOUT_H, MPU_data_buffer, sizeof MPU_data_buffer);
//	frame2string(MPU_data_buffer,Debug_MPU_Data, sizeof Debug_MPU_Data); //TODO rm
//	debug(Debug_MPU_Data);
//	debug("Reading MPU done");
//	wdt_reset_counter();
}



void i2c_IMU_write(unsigned char reg_adrr, unsigned char data) {
	unsigned char TxData[] = { reg_adrr, data };
	PTxData = (unsigned char *) TxData;
	TXByteCtr = sizeof TxData;
	UCB1CTL1 |= UCTR + UCTXSTT;
	while (UCB1CTL1 & UCTXSTP);
}

void i2c_IMU_read(unsigned char reg_adrr, char buffer[],unsigned int bytes) {
	PTxData = &reg_adrr;
	TXByteCtr = 1;
	UCB1CTL1 |= UCTR + UCTXSTT;
	while (UCB1CTL1 & UCTXSTP);
	RXByteCtr = bytes;
	PRxData = buffer;
	UCB1CTL1 &= ~UCTR;
	UCB1CTL1 |= UCTXSTT;
	while (UCB1CTL1 & UCTXSTP);
}
