#include <msp430.h>


//configuration function
void config_MSP430(void);

//Measurement function
void measurement__adc(void);

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

int main(void)
{
	config_MSP430();

	measurement__adc();


 __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}






/************************************************************************/
/*  - name: config_MSP430
 *  - Description:
 *  - input data: --
 *  - output data: --
 ***********************************************************************/


void config_MSP430(void){

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
    DCOCTL = CALDCO_8MHZ;

    P3SEL = 0x30;
		 	    // P3SEL2=0x30;
	UCA0CTL1 |= UCSSEL_2;                      // SMCLK
    UCA0BR0 = 0x41;                            // 1MHz 9600
	UCA0BR1 = 0x3;                             // 1MHz 9600
    P4SEL = 0x20;
    P4OUT=0X20;


	//ADC Msp430
	ADC12CTL0 = ADC12ON+MSC+SHT0_2 + REFON;  // Turn on ADC12, set sampling time, 16 ADC12CLK cycles, Vref=1.5V
	ADC12CTL1 = SHP + CONSEQ_1;
	ADC12MCTL0 = INCH_0+SREF_1;                   // ref+=VREF+, channel = A0
    ADC12MCTL1 = INCH_1+SREF_1;                   // ref+=VREF+, channel = A1
	ADC12MCTL2 = INCH_2+SREF_1;                   // ref+=VREF+, channel = A2
	ADC12MCTL3 = INCH_3+SREF_1;                   // ref+=VREF+, channel = A3
	ADC12MCTL4 = INCH_4+SREF_1;                   // ref+=VREF+, channel = A4
	ADC12MCTL5 = INCH_5+SREF_1;              // ref+=AVcc, channel = A6, end seq.
	ADC12MCTL6 = INCH_10+SREF_1+EOS;                // Vr+=Vref+
	ADC12CTL0 |= ENC;                       // Enable conversions

	
}

	void measurement__adc(void){                             // ADC  function

	ADC12CTL0 |= ADC12SC;                     // Start convn - software trigger

	adc0_lsb= ADC12MEM0 & 0xff;
	adc0_msb= ADC12MEM0>>8;
	adc1_lsb= ADC12MEM1 & 0xff;
	adc1_msb= ADC12MEM1>>8;
	adc2_lsb= ADC12MEM2 & 0xff;
	adc2_msb= ADC12MEM2>>8;
	adc3_lsb= ADC12MEM3 & 0xff;
	adc3_msb= ADC12MEM3>>8;
	adc4_lsb= ADC12MEM4 & 0xff;
	adc4_msb= ADC12MEM4>>8;
	adc5_lsb= ADC12MEM5 & 0xff;
	adc5_msb= ADC12MEM5>>8;



}
