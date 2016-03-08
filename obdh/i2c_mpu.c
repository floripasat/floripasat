//Code by : Matheus Frata
/*Mpu comunication with i2c without uart.
 * Adpatation from arduino to msp430 - http://playground.arduino.cc/Main/MPU-9150
 */
#include <msp430.h>

#define MPU9150_SELF_TEST_X        0x0D   // R/W
#define MPU9150_SELF_TEST_Y        0x0E   // R/W
#define MPU9150_SELF_TEST_Z        0x0F   // R/W
#define MPU9150_SELF_TEST_A        0x10   // R/W
#define MPU9150_SMPLRT_DIV         0x19   // R/W
#define MPU9150_CONFIG             0x1A   // R/W
#define MPU9150_GYRO_CONFIG        0x1B   // R/W
#define MPU9150_ACCEL_CONFIG       0x1C   // R/W
#define MPU9150_FF_THR             0x1D   // R/W
#define MPU9150_FF_DUR             0x1E   // R/W
#define MPU9150_MOT_THR            0x1F   // R/W
#define MPU9150_MOT_DUR            0x20   // R/W
#define MPU9150_ZRMOT_THR          0x21   // R/W
#define MPU9150_ZRMOT_DUR          0x22   // R/W
#define MPU9150_FIFO_EN            0x23   // R/W
#define MPU9150_I2C_MST_CTRL       0x24   // R/W
#define MPU9150_I2C_SLV0_ADDR      0x25   // R/W
#define MPU9150_I2C_SLV0_REG       0x26   // R/W
#define MPU9150_I2C_SLV0_CTRL      0x27   // R/W
#define MPU9150_I2C_SLV1_ADDR      0x28   // R/W
#define MPU9150_I2C_SLV1_REG       0x29   // R/W
#define MPU9150_I2C_SLV1_CTRL      0x2A   // R/W
#define MPU9150_I2C_SLV2_ADDR      0x2B   // R/W
#define MPU9150_I2C_SLV2_REG       0x2C   // R/W
#define MPU9150_I2C_SLV2_CTRL      0x2D   // R/W
#define MPU9150_I2C_SLV3_ADDR      0x2E   // R/W
#define MPU9150_I2C_SLV3_REG       0x2F   // R/W
#define MPU9150_I2C_SLV3_CTRL      0x30   // R/W
#define MPU9150_I2C_SLV4_ADDR      0x31   // R/W
#define MPU9150_I2C_SLV4_REG       0x32   // R/W
#define MPU9150_I2C_SLV4_DO        0x33   // R/W
#define MPU9150_I2C_SLV4_CTRL      0x34   // R/W
#define MPU9150_I2C_SLV4_DI        0x35   // R
#define MPU9150_I2C_MST_STATUS     0x36   // R
#define MPU9150_INT_PIN_CFG        0x37   // R/W
#define MPU9150_INT_ENABLE         0x38   // R/W
#define MPU9150_INT_STATUS         0x3A   // R
#define MPU9150_ACCEL_XOUT_H       0x3B   // R
#define MPU9150_ACCEL_XOUT_L       0x3C   // R
#define MPU9150_ACCEL_YOUT_H       0x3D   // R
#define MPU9150_ACCEL_YOUT_L       0x3E   // R
#define MPU9150_ACCEL_ZOUT_H       0x3F   // R
#define MPU9150_ACCEL_ZOUT_L       0x40   // R
#define MPU9150_TEMP_OUT_H         0x41   // R
#define MPU9150_TEMP_OUT_L         0x42   // R
#define MPU9150_GYRO_XOUT_H        0x43   // R
#define MPU9150_GYRO_XOUT_L        0x44   // R
#define MPU9150_GYRO_YOUT_H        0x45   // R
#define MPU9150_GYRO_YOUT_L        0x46   // R
#define MPU9150_GYRO_ZOUT_H        0x47   // R
#define MPU9150_GYRO_ZOUT_L        0x48   // R
#define MPU9150_EXT_SENS_DATA_00   0x49   // R
#define MPU9150_EXT_SENS_DATA_01   0x4A   // R
#define MPU9150_EXT_SENS_DATA_02   0x4B   // R
#define MPU9150_EXT_SENS_DATA_03   0x4C   // R
#define MPU9150_EXT_SENS_DATA_04   0x4D   // R
#define MPU9150_EXT_SENS_DATA_05   0x4E   // R
#define MPU9150_EXT_SENS_DATA_06   0x4F   // R
#define MPU9150_EXT_SENS_DATA_07   0x50   // R
#define MPU9150_EXT_SENS_DATA_08   0x51   // R
#define MPU9150_EXT_SENS_DATA_09   0x52   // R
#define MPU9150_EXT_SENS_DATA_10   0x53   // R
#define MPU9150_EXT_SENS_DATA_11   0x54   // R
#define MPU9150_EXT_SENS_DATA_12   0x55   // R
#define MPU9150_EXT_SENS_DATA_13   0x56   // R
#define MPU9150_EXT_SENS_DATA_14   0x57   // R
#define MPU9150_EXT_SENS_DATA_15   0x58   // R
#define MPU9150_EXT_SENS_DATA_16   0x59   // R
#define MPU9150_EXT_SENS_DATA_17   0x5A   // R
#define MPU9150_EXT_SENS_DATA_18   0x5B   // R
#define MPU9150_EXT_SENS_DATA_19   0x5C   // R
#define MPU9150_EXT_SENS_DATA_20   0x5D   // R
#define MPU9150_EXT_SENS_DATA_21   0x5E   // R
#define MPU9150_EXT_SENS_DATA_22   0x5F   // R
#define MPU9150_EXT_SENS_DATA_23   0x60   // R
#define MPU9150_MOT_DETECT_STATUS  0x61   // R
#define MPU9150_I2C_SLV0_DO        0x63   // R/W
#define MPU9150_I2C_SLV1_DO        0x64   // R/W
#define MPU9150_I2C_SLV2_DO        0x65   // R/W
#define MPU9150_I2C_SLV3_DO        0x66   // R/W
#define MPU9150_I2C_MST_DELAY_CTRL 0x67   // R/W
#define MPU9150_SIGNAL_PATH_RESET  0x68   // R/W
#define MPU9150_MOT_DETECT_CTRL    0x69   // R/W
#define MPU9150_USER_CTRL          0x6A   // R/W
#define MPU9150_PWR_MGMT_1         0x6B   // R/W
#define MPU9150_PWR_MGMT_2         0x6C   // R/W
#define MPU9150_FIFO_COUNTH        0x72   // R/W
#define MPU9150_FIFO_COUNTL        0x73   // R/W
#define MPU9150_FIFO_R_W           0x74   // R/W
#define MPU9150_WHO_AM_I           0x75   // R

//MPU9150 Compass
#define MPU9150_CMPS_XOUT_L        0x4A   // R
#define MPU9150_CMPS_XOUT_H        0x4B   // R
#define MPU9150_CMPS_YOUT_L        0x4C   // R
#define MPU9150_CMPS_YOUT_H        0x4D   // R
#define MPU9150_CMPS_ZOUT_L        0x4E   // R
#define MPU9150_CMPS_ZOUT_H        0x4F   // R

volatile unsigned char *PTxData;                     // Pointer to TX data
volatile unsigned char *PRxData;                     // Pointer to RX data
unsigned char RXBuffer;
char TXByteCtr;
char RXByteCtr;

void write_i2c(volatile unsigned char reg_adrr,volatile unsigned char data);
void setup_i2c(volatile unsigned char dev_adrr);
char read_i2c(volatile unsigned char reg_adrr);
void MPU9150_setupCompass(void);
int MPU9150_readSensor(int addrH, int addrL);
void clear(void);

#define x  0
#define y  1
#define z  2

int mag[3];
int acc[3];
int gyr[3];
float temp;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  __bis_SR_register(GIE);
  setup_i2c(0x68);
  write_i2c(MPU9150_PWR_MGMT_1, 0x00);
  MPU9150_setupCompass();
  while (1)
  {
	 temp = (float)MPU9150_readSensor(MPU9150_TEMP_OUT_H,MPU9150_TEMP_OUT_L)/340+35;

	 acc[x]= MPU9150_readSensor(MPU9150_ACCEL_XOUT_H,MPU9150_ACCEL_XOUT_L);
	 acc[y]= MPU9150_readSensor(MPU9150_ACCEL_YOUT_H,MPU9150_ACCEL_YOUT_L);
	 acc[z]= MPU9150_readSensor(MPU9150_ACCEL_ZOUT_H,MPU9150_ACCEL_ZOUT_L);

	 gyr[x]= MPU9150_readSensor(MPU9150_GYRO_XOUT_H,MPU9150_GYRO_XOUT_L);
	 gyr[y]= MPU9150_readSensor(MPU9150_GYRO_YOUT_H,MPU9150_GYRO_YOUT_L);
	 gyr[z]= MPU9150_readSensor(MPU9150_GYRO_ZOUT_H,MPU9150_GYRO_ZOUT_L);

	 mag[x]= MPU9150_readSensor(MPU9150_CMPS_XOUT_H,MPU9150_CMPS_XOUT_L);
	 mag[y]= MPU9150_readSensor(MPU9150_CMPS_YOUT_H,MPU9150_CMPS_YOUT_L);
	 mag[z]= MPU9150_readSensor(MPU9150_CMPS_ZOUT_H,MPU9150_CMPS_ZOUT_L);
  }
}



#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6: break;                           // Vector  6: STTIFG
  case  8: break;                           // Vector  8: STPIFG
  case 10:                            		// Vector 10: RXIFG
	if (RXByteCtr)                          // Check TX byte counter
	{
	  RXBuffer = UCB0RXBUF;
	  PRxData = &RXBuffer;             	    // Load TX buffer
	  RXByteCtr--;                          // Decrement TX byte counter
	}
	else
	{
	  UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
	  UCB0IFG &= ~UCRXIFG;                  // Clear USCI_B0 TX int flag
	  UCB0IE &= ~UCRXIE;
	  __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
	}
	break;
  case 12:                                  // Vector 12: TXIFG
	if (TXByteCtr)                          // Check TX byte counter
	{
	  UCB0TXBUF = *PTxData++;               // Load TX buffer
	  TXByteCtr--;                          // Decrement TX byte counter
	}
	else
	{
	  UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
	  UCB0IFG &= ~UCTXIFG;                  // Clear USCI_B0 TX int flag
	  UCB0IE &= ~UCTXIE;
	  __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
	}
	break;
  default: break;
  }
}
void write_i2c(volatile unsigned char reg_adrr, volatile unsigned char data){
	volatile unsigned char TxData[] = {reg_adrr, data};
	PTxData = (volatile unsigned char *)TxData;
	TXByteCtr = sizeof TxData;
	UCB0CTL1 |= UCTR + UCTXSTT;
	UCB0IE |= UCTXIE;
	__bis_SR_register(LPM0_bits);
	while (UCB0CTL1 & UCTXSTP);
}
void setup_i2c(volatile unsigned char dev_adrr){
	  P3SEL |= 0x03;                            // Assign I2C pins to USCI_B0
	  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	  UCB0BR1 = 0;
	  UCB0I2CSA = dev_adrr;                         // Slave Address is 048h
	  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

}
char read_i2c(volatile unsigned char reg_adrr){
	char Data;
	PTxData = &reg_adrr;
	TXByteCtr = 1;
	UCB0CTL1 |= UCTR + UCTXSTT;
	UCB0IE |= UCTXIE;
	__bis_SR_register(LPM0_bits);
	while (UCB0CTL1 & UCTXSTP);
	RXByteCtr = 1;
	UCB0CTL1 &= ~UCTR;
	UCB0CTL1 |= UCTXSTT;
	UCB0IE |= UCRXIE;
	__bis_SR_register(LPM0_bits);
	Data = *PRxData;
	return Data;
}

void MPU9150_setupCompass(){
	write_i2c(0x0A, 0x00); //PowerDownMode
	write_i2c(0x0A, 0x0F); //SelfTest
	write_i2c(0x0A, 0x00); //PowerDownMode
	write_i2c(0x24, 0x40); //Wait for Data at Slave0
	write_i2c(0x25, 0x8C); //Set i2c address at slave0 at 0x0C
	write_i2c(0x26, 0x02); //Set where reading at slave 0 starts
	write_i2c(0x27, 0x88); //set offset at start reading and enable
	write_i2c(0x28, 0x0C); //set i2c address at slv1 at 0x0C
	write_i2c(0x29, 0x0A); //Set where reading at slave 1 starts
	write_i2c(0x2A, 0x81); //Enable at set length to 1
	write_i2c(0x64, 0x01); //overvride register
	write_i2c(0x67, 0x03); //set delay rate
	write_i2c(0x01, 0x80);
	write_i2c(0x34, 0x04); //set i2c slv4 delay
	write_i2c(0x64, 0x00); //override register
	write_i2c(0x6A, 0x00); //clear usr setting
	write_i2c(0x64, 0x01); //override register
	write_i2c(0x6A, 0x20); //enable master i2c mode
	write_i2c(0x34, 0x13); //disable slv4
}
void clear(void){
	PTxData   = 0;
	PRxData   = 0;
	RXBuffer  = 0;
	TXByteCtr = 0;
	RXByteCtr = 0;
	UCB0TXBUF = 0;
}
int MPU9150_readSensor(int addrH, int addrL){
  int H,L;
  H = read_i2c(addrH);
  clear();
  L = read_i2c(addrL);
  return (int)((H<<8)+L);
}
