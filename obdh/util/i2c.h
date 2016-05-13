#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>

#define MPU 	1
#define EPS 	0

#define MPU_I2C_ADRESS		0x68
#define EPS_I2C_ADRESS		0x13

//unsigned int stillReading; TODO rm

unsigned char *PRxData;                     // Pointer to RX data
unsigned char *PTxData;                     // Pointer to TX data
unsigned char RXByteCtr;
unsigned char TXByteCtr;

void Port_Mapping_UCB0(void);
void i2c_setup(unsigned int device);
void i2c_read_epsFrame(char *Buffer, unsigned int bytes);
void i2c_tx(void);


#endif /* I2C_H_ */
