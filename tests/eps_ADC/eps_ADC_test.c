#include <msp430.h> 

/*
 * main.c
 */


volatile int adc0_msb=0x00;
volatile int adc0_lsb=0x00;
volatile int adc1_msb=0x00;
volatile int adc1_lsb=0x00;
volatile int adc2_msb=0x00;
volatile int adc2_lsb=0x00;
volatile int adc3_msb=0x00;
volatile int adc3_lsb=0x00;
volatile int adc4_msb=0x00;
volatile int adc4_lsb=0x00;
volatile int adc5_msb=0x00;
volatile int adc5_lsb=0x00;
volatile int adc6_msb=0x00;
volatile int adc6_lsb=0x00;
volatile int adc7_msb=0x00;
volatile int adc7_lsb=0x00;
volatile int msp_ts_msb=0x00;
volatile int msp_ts_lsb=0x00;

void config_MSP430_ADC(void);
void measurement_ADC(void);


int main(void) {
    config_MSP430_ADC();
    while(1){
	measurement_ADC();
    }
}




void measurement_ADC(void)
{
	ADC12CTL0 |= ADC12SC;                     				// Start convn - software trigger
	adc0_lsb= ADC12MEM0 & 0xff;				  				// bitwise and operation with '0000000011111111b' to extract LSB
	adc0_msb= ADC12MEM0>>8;									// 8 bit shift to extract MSB
	adc1_lsb= ADC12MEM1 & 0xff;								// bitwise and operation with '0000000011111111b' to extract LSB
	adc1_msb= ADC12MEM1>>8;									// 8 bit shift to extract MSB
	adc2_lsb= ADC12MEM2 & 0xff;								// bitwise and operation with '0000000011111111b' to extract LSB
	adc2_msb= ADC12MEM2>>8;									// 8 bit shift to extract MSB
	adc3_lsb= ADC12MEM3 & 0xff;								// bitwise and operation with '0000000011111111b' to extract LSB
	adc3_msb= ADC12MEM3>>8;									// 8 bit shift to extract MSB
	adc4_lsb= ADC12MEM4 & 0xff;								// bitwise and operation with '0000000011111111b' to extract LSB
	adc4_msb= ADC12MEM4>>8;									// 8 bit shift to extract MSB
	adc5_lsb= ADC12MEM5 & 0xff;								// bitwise and operation with '0000000011111111b' to extract LSB
	adc5_msb= ADC12MEM5>>8;									// 8 bit shift to extract MSB
	msp_ts_lsb= ADC12MEM6 & 0xff;							// bitwise and operation with '0000000011111111b' to extract LSB
	msp_ts_msb= ADC12MEM6>>8;								// 8 bit shift to extract MSB


}
