/*
 * imu.h
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#ifndef INTERFACES_IMU_H_
#define INTERFACES_IMU_H_

#include "../util/i2c.h"
void readImu(void);

void i2c_IMU_read(unsigned char , char* ,unsigned int );
void i2c_IMU_write(unsigned char , unsigned char );


#endif /* INTERFACES_IMU_H_ */
