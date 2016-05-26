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
	i2c_IMU_write(MPU9150_PWR_MGMT_1, 0x00);
	i2c_IMU_write(MPU9150_ACCEL_CONFIG, 0x00);
//	i2c_IMU_write(MPU9150_ACCEL_CONFIG, 0x18); //para leitura durante a subida
}


void imu_read(void){
//	debug("Reading MPU init");

	i2c_IMU_read(MPU9150_ACCEL_XOUT_H, imuData, sizeof imuData);
//	frame2string(MPU_data_buffer,Debug_MPU_Data, sizeof Debug_MPU_Data); //TODO rm

	debug("Decoding IMU data...");

//	IMU response:
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


	int temp = (signed int) ((( tempH << 8 ) | tempL ) / 340 + 35 );
	int accX = (signed int)  (( accXH << 8 ) | accXL );
	int accY = (signed int)  (( accYH << 8 ) | accYL );
	int accZ = (signed int)  (( accZH << 8 ) | accZL );
	int gyrX = (signed int)  (( gyrXH << 8 ) | gyrXL );
	int gyrY = (signed int)  (( gyrYH << 8 ) | gyrYL );
	int gyrZ = (signed int)  (( gyrZH << 8 ) | gyrZL );

	debug_int("temp:", temp);
	debug_int("accX:", accX);
	debug_int("accY:", accY);
	debug_int("accZ:", accZ);
	debug_int("gyrX:", gyrX);
	debug_int("gyrY:", gyrY);
	debug_int("gyrZ:", gyrZ);

//	debug( imu_data2string(imuTmpStr, MPU_data_buffer) );

//	wdt_reset_counter();
}


char* imu_data2string(char* aa1, char* imuData){

	sprintf(aa1, "%d", 123 );

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
