/*
 * imu.c
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#include "imu.h"

unsigned char Debug_MPU_Data[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//TODO rm
char imuTmpStr[100];


void imu_config(void){
	imu_i2c_write(MPU9150_PWR_MGMT_1, 0x00);

	if (IMU_ACC_RANGE == 2.0) {
		imu_i2c_write(MPU9150_ACCEL_CONFIG, 0x00);   // config for +-2g range
	} else {
		imu_i2c_write(MPU9150_ACCEL_CONFIG, 0x18);   // config for +-16g range
	}

}


void imu_read(char* imuData){

	imu_i2c_read(MPU9150_ACCEL_XOUT_H, imuData, IMU_DATA_LENGTH );

}


char* imu_data2string(char* stringBuffer, char* imuData, float accRange, float gyrRange){

	//	IMU MPU6050 response:
	//	[accXH][accXL][accYH][accYL][accZH][accZL][tempH][tempL][gyrXH][gyrXL][gyrYH][gyrYL][gyrZH][gyrZL]

	char accXH = imuData[0];
	char accXL = imuData[1];
	char accYH = imuData[2];
	char accYL = imuData[3];
	char accZH = imuData[4];
	char accZL = imuData[5];

	char tempH = imuData[6];
	char tempL = imuData[7];

	char gyrXH = imuData[8];
	char gyrXL = imuData[9];
	char gyrYH = imuData[10];
	char gyrYL = imuData[11];
	char gyrZH = imuData[12];
	char gyrZL = imuData[13];

	float temp = (float) ((( tempH << 8 ) | tempL ) / 340.0 + 35.0 );

	float accX = (float)( ((accXH<<8 | accXL)*accRange)/32768.0 );
	float accY = (float)( ((accYH<<8 | accYL)*accRange)/32768.0 );
	float accZ = (float)( ((accZH<<8 | accZL)*accRange)/32768.0 );

	float gyrX = (float)( ((gyrXH<<8 | gyrXL)*gyrRange)/32768.0 );
	float gyrY = (float)( ((gyrYH<<8 | gyrYL)*gyrRange)/32768.0 );
	float gyrZ = (float)( ((gyrZH<<8 | gyrZL)*gyrRange)/32768.0 );

	sprintf(stringBuffer, "\tTemperature: %.3f C"
						  "\t\tAcc (X,Y,Z):\t%.3f\t%.3f\t%.3f G"
						  "\t\tGyr (X,Y,Z):\t%.3f\t%.3f\t%.3f g/S",
						  temp, accX,accY,accZ, gyrX,gyrY,gyrZ);

	return stringBuffer;
}


void imu_i2c_write(unsigned char reg_adrr, unsigned char data) {
	unsigned char TxData[] = { reg_adrr, data };
	PTxData = (unsigned char *) TxData;
	TXByteCtr = sizeof TxData;
	UCB1CTL1 |= UCTR + UCTXSTT;
	while (UCB1CTL1 & UCTXSTP);
}

void imu_i2c_read(unsigned char reg_adrr, char buffer[],unsigned int bytes) {
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
