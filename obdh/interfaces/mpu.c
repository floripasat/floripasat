#include "../interfaces/mpu.h"


void mpu_config(void){
	i2c_IMU_write(MPU9150_PWR_MGMT_1, 0x00);
	i2c_IMU_write(MPU9150_ACCEL_CONFIG, 0x00);
//	i2c_IMU_write(MPU9150_ACCEL_CONFIG, 0x18); //para leitura durante a subida
}
