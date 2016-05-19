#include <msp430.h>
#include "mpu_i2c.h"
#include "mpu_9150.h"
#include "mpu_uart.h"

#define x  0
#define y  1
#define z  2

int acc[3];
char buffer[14];
unsigned i;

void main(void) {

	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	__bis_SR_register(GIE);
	setup_i2c(0x68);

	write_i2c(MPU9150_PWR_MGMT_1, 0x00);

	write_i2c(MPU9150_ACCEL_CONFIG, 0x00); // para leitura durante a microgravidade
//	write_i2c(MPU9150_ACCEL_CONFIG, 0x18); //para leitura durante a subida

	while (1) {
		read_i2c(MPU9150_ACCEL_XOUT_H, buffer, sizeof buffer);
		__delay_cycles(500000);

	}
}
