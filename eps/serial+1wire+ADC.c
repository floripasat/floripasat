#include <msp430.h>
#include <stdio.h>
#include "intrinsics.h"

//configuration functions
void config_MSP430(void);
void config_DS2784(void);

//Measurement functions
void measurement_data_DS2784(void);
void measurement__adc(void);


//1 wire protocol functions
void outp(int bit);
int inp(void);
int OneWireReset(void);
void OneWireWrite(int bit);
int OneWireReadBit(void);
void OWWriteByte(int data);
int OWReadByte(void);

//serial functions
void UART_TX(char * tx_data) ;
void float_send(float c);
void Text(void);
void clear_V(void);

//define

#define P_1WireOUT P1OUT
#define P_1WireIN P1IN
#define DIR_P_1Wire P1DIR

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
volatile int avc_msb=0x00;
volatile int avc_lsb=0x00;
volatile int vr_msb=0x00;
volatile int vr_lsb=0x00;
volatile int tr_msb=0x00;
volatile int tr_lsb=0x00;
volatile int cr_msb=0x00;
volatile int cr_lsb=0x00;
volatile int acr_msb=0x00;
volatile int acr_lsb=0x00;



volatile int cont= 0;

/*************************************************************************/
//                        main
/************************************************************************/

int main(void)
{
	config_MSP430();

	config_DS2784();
	
	measurement__adc();
	measurement_data_DS2784();
	Text();


 __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  if(cont==400){   //123
	  cont=0;
	  Text();

      clear_V();
	  measurement__adc();
	  measurement_data_DS2784();
	  CCR0 =65535;

  }else{
	  cont ++;
	  CCR0 =65535;

  }


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
	UCA0MCTL = UCBRS0;                         // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                      // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
	                                          // Enable USCI_A0 RX interrupt
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

	 //1-wire Clock
 	//BCSCTL1 = CALBC1_8MHZ;          		// 8Mhz cal data for DCO
    //DCOCTL = CALDCO_8MHZ;           		// 8Mhz cal data for DCO
	//P1REN=0x01;		                       //pullup resistor enable   ????/ ojo mirar cual es el resistor pull-up
	//P1OUT |= 0x01;                        // resistor pullup activado no necesito poner a 1 el bus
	 //UARt

	//timer
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 =65535;
	TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

}

/************************************************************************/
/*  - name: config_MSP430
 *  - Description:
 *  - input data: --
 *  - output data: --
 ***********************************************************************/

void config_DS2784(void){
	// CONFIGURATION DS2784

	volatile unsigned int reset=0x1;
	reset= OneWireReset();				// PROTECTION REGISTER
	OWWriteByte(0xCC);
	OWWriteByte(0x6C);
	OWWriteByte(0x00);
	OWWriteByte(0x03);

	reset= OneWireReset();              // PROTECTOR THRESHOLD REGISTER
	OWWriteByte(0xCC);
	OWWriteByte(0x6C);
	OWWriteByte(0x7F);
	OWWriteByte(0xF0);

}

/************************************************************************/
/*  - name: measurement__adc
 *  - Description:this fuccion read the sensors values by the ADC12.
 *  It uses the internal 1.5V reference and performs a single conversion
 *  on channels A0-A5. The conversion results are stored in results_adc register.
 *  - input data: --
 *  - ouput data: ADC results register
 ***********************************************************************/

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

	msp_ts_lsb= ADC12MEM6 & 0xff;
	msp_ts_msb= ADC12MEM6>>8;


}

/************************************************************************/
/*  - name: measurement_data_DS2784
 *  - Description:
 *  - input data: --
 *  - output data: --
 ***********************************************************************/
void measurement_data_DS2784(void){

    volatile unsigned int aux;
    volatile unsigned int reset=0x1;


   // TEMPERATURE MEASUREMENT

    reset= OneWireReset();              // TEMPERATURE MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x0B);
    aux=OWReadByte();
    tr_lsb=aux>>5;

    reset= OneWireReset();              // TEMPERATURE MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x0A);
    aux=OWReadByte();
    tr_msb=aux>>5;
    aux=aux<<3;
    tr_lsb|=aux & 0xF8;



    //AVERAGE CURRENT MEASUREMENT

    reset= OneWireReset();              // AVERAGE CURRENT MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x09);
    avc_lsb=OWReadByte();

    reset= OneWireReset();              // AVERAGE CURRENT MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x08);
    avc_msb=OWReadByte();

    //ACCUMULATED CURRENT MEASUREMENT

    reset= OneWireReset();              // ACCUMULATED CURRENT MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x11);
    acr_lsb=OWReadByte();

    reset= OneWireReset();              // ACCUMULATED CURRENT MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x10);
    acr_msb=OWReadByte();



   //CURRENT MEASUREMENT

    reset= OneWireReset();              //  CURRENT MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x0F);
    cr_lsb=OWReadByte();


    reset= OneWireReset();              // CURRENT MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x0E);
    cr_msb=OWReadByte();

    //VOLTAGE MEASUREMENT

    reset= OneWireReset();           // VOLTAGE MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x0D);
    aux=OWReadByte();
    vr_lsb=aux>>5;

    reset= OneWireReset();              // VOLTAGE MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);
    OWWriteByte(0x69);
    OWWriteByte(0x0C);
    aux=OWReadByte();
    vr_msb=aux>>5;
    aux=aux<<3;
    vr_lsb|=aux & 0xF8;



}



/************************************************************************/
/*  - name: outp
 *  - Description: This function sends bit to 1-wire slave.
 *  - input data: int bit
 *  - output data: --
 ***********************************************************************/

void outp(int bit){


	DIR_P_1Wire |= 0x01;			//sets P1.0 as output

	if(bit == 0){
		P_1WireOUT= 0x0;           //drives P1.0 low
	}
	else{
		P_1WireOUT=0x01;           //releases the bus
	}
}
/************************************************************************/
/*  - name: inp
 *  - Description: This function reads a bit from the 1-wire slave.
 *  - input data: --
 *  - output data: int result
 ***********************************************************************/

int inp(void){
	unsigned int result=0;

	 DIR_P_1Wire=0x00;          //sets P1.0 as input
	 result= P_1WireIN;         //prepares the bit on P1.0 to be returned

	 return result;		        //returns the bit on P1.0

	}

/************************************************************************/
/*  - name: OneWireReset
 *  - Description: This function genererates 1-wire reset. Returns 0
 *    if no presence detect was found, return 1 otherwise.
 *  - input data: --
 *  - output data: int result
 ***********************************************************************/

int OneWireReset(void){

	int result;

	  outp(1);				        //drives P1.0 high
	__delay_cycles(0);			    // delay of 0
	  outp(0);				        //drives P1.0 low
	__delay_cycles(3812);			//delay of 480us, 8,12MHz* 480us=3897

	  outp(1);						//releases the bus
	  result = inp();			        //prepares the result of present detection to be returned
	  __delay_cycles(568);			//delay of 70us, 8,12MHz*70us=568

	  outp(1);
	__delay_cycles(3329);			//delay of 410us, 8,12MHz*410us=3329

	return result;			        //returns the presence detection result

}

/************************************************************************/
/*  - name: OneWireWrite
 *  - Description: this function sends a 1-wire write bit to 1-wire slave.
 *  - input data: int bit
 *  - output data:--
 ***********************************************************************/

void OneWireWrite(int bit){



		if(bit == 1){
			outp(0);				//drives P1.0 low
		__delay_cycles(40);		    //delay of 6us, 8,12 MHz*6us= 44

			outp(1);				//releases the bus
		__delay_cycles(500);		//delay of 64us, 8,12MHz*64us=517

		}else{
	       // Write '0' bit
			outp(0);				//drives P1.0 low
		__delay_cycles(470);		//delay of 60us, 8,12MHz*60us=487
			outp(1);				//releases the bus
		__delay_cycles(60);			// delay of 10us, 8MHz*10us=80

		}

}

/************************************************************************/
/*  - name: OneWireReadBit
 *  - Description: This function reads a 1-wire data bit  to 1-wire slave and returns int.
 *  - input data: --
 *  - output data: int result
 ***********************************************************************/

int OneWireReadBit(void){

	int result;
	outp(0);						//drives P1.0 low
	__delay_cycles(44);		        //delay of 6us, 8,12 MHz*6us= 44

	outp(1);						//releases the bus
	__delay_cycles(70);				//delay of 9us, 8,12MHz*9us=73

	result = inp();					//sample the bit from slave
	__delay_cycles(443);			//delay of 55us, 8,12MHz*55us=446

	return result;

}

/************************************************************************/
/*  - name: OWWriteByte
 *  - Description: This function writes a 1-wire data byte.
 *  - input data: int data
 *  - output data: --
 ***********************************************************************/

void OWWriteByte(int data)
{

	int loop;

	for (loop = 0; loop < 8; loop++)	// Loop to write each bit in the byte, LS-bit first
	{
		OneWireWrite(data & 0x01);

		data >>= 1;						// shift the data byte for the next bit
	}
}

/************************************************************************/
/*  - name: OWReadByte
 *  - Description: This function read a 1-wire data byte and return it
 *  - input data: int data
 *  - output data: --
 ***********************************************************************/

int OWReadByte(void)
{
	int loop, result = 0;
	for (loop = 0; loop < 8; loop++)
	{

		result >>= 1;						// shift the result to get it ready for the next bit

		if (OneWireReadBit())			    // if result is one, then set MS bit
			result |= 0x80;
	}
		return result;
}

/************************************************************************/
/*  - name: Serial
 *  - Description:
 *  - input data:
 *  - output data: --
 ***********************************************************************/


void Text(void){

	UART_TX(" ******************* \r\n");
	UART_TX(" * EPS Measurement * \r\n");
	UART_TX(" ******************* \r\n");
	UART_TX(" ~~ MSP430 ~~ \r\n");


	//ADC0
   volatile int a=adc0_lsb;
   volatile int b=adc0_msb;
   b=b<<8;
   a=a+b;
   volatile float c=a*0.0003663;    //resolution
   UART_TX(" ADC0= ");
   float_send(c);
   UART_TX(" V\r\n");

    //ADC1
   a=adc1_lsb;
   b=adc1_msb;
   b=b<<8;
   a=a+b;
   c=a*0.0003663;    //resolution
   UART_TX(" ADC1= ");
   float_send(c);
   UART_TX(" V\r\n");

   //ADC2
   a=adc2_lsb;
   b=adc2_msb;
   b=b<<8;
   a=a+b;
   c=a*0.0003663;    //resolution
   UART_TX(" ADC2= ");
   float_send(c);
   UART_TX(" V\r\n");

   //ADC3
   a=adc3_lsb;
   b=adc3_msb;
   b=b<<8;
   a=a+b;
   c=a*0.0003663;    //resolution
   UART_TX(" ADC3= ");
   float_send(c);
   UART_TX(" V\r\n");

   //ADC4
   a=adc4_lsb;
   b=adc4_msb;
   b=b<<8;
   a=a+b;
   c=a*0.0003663;    //resolution
   UART_TX(" ADC4= ");
   float_send(c);
   UART_TX(" V\r\n");

   //ADC5
    a=adc5_lsb;
    b=adc5_msb;
    b=b<<8;
    a=a+b;
    c=a*0.0003663;    //resolution
    UART_TX(" ADC5= ");
    float_send(c);
    UART_TX(" V\r\n");

    //ADC6
    a=adc6_lsb;
    b=adc6_msb;
    b=b<<8;
    a=a+b;
    c=a*0.0003663;    //resolution
    UART_TX(" ADC6= ");
    float_send(c);
    UART_TX(" V\r\n");

    //ADC7
    a=adc7_lsb;
    b=adc7_msb;
    b=b<<8;
    a=a+b;
    c=a*0.0003663;    //resolution
    UART_TX(" ADC7= ");
    float_send(c);
    UART_TX(" V\r\n");

    //ADC10 Temp
    a= msp_ts_lsb;
    b= msp_ts_msb;
    b=b<<8;
    a=a+b;
    c=a*0.1031549;    //resolution
    UART_TX(" Temperature= ");
    float_send(c);
    UART_TX(" ºC\r\n");

    UART_TX(" ~~ DS2784 ~~ \r\n");

    //Average Current
    a=  avc_lsb;
    b=  avc_msb;
    b=b<<8;
    a=a+b;
    c=a*0.0000015625/0.025;    //resolution
    UART_TX(" Average Current= ");
    float_send(c);
    UART_TX(" A\r\n");

    //Temperature
    a=  tr_lsb;
    b=  tr_msb;
    b=b<<8;
    a=a+b;
    c=a*0.125;    //resolution
    UART_TX(" Temperature= ");
    float_send(c);
    UART_TX(" ºC\r\n");

    //Voltage
    a=  vr_lsb;
    b=  vr_msb;
    b=b<<8;
    a=a+b;
    c=a*0.004886;    //resolution
    UART_TX(" Voltage= ");
    float_send(c);
    UART_TX(" V\r\n");

    //Current
    a=  cr_lsb;
    b=  cr_msb;
    b=b<<8;
    a=a+b;
    c=a*0.0000015625/0.025;    //resolution
    UART_TX("Current= ");
    float_send(c);
    UART_TX(" A\r\n");

    //Accumulated Current
    a=  acr_lsb;
    b=  acr_msb;
    b=b<<8;
    a=a+b;
    c=a*0.00000625/0.025;    //resolution
    UART_TX("Accumulated Current= ");
    float_send(c);
    UART_TX(" Ah\r\n");




}

/************************************************************************/
/*  - name: Float_serial
 *  - Description:
 *  - input data:
 *  - output data:
 ***********************************************************************/

void float_send(float c){

    volatile long int d;
	volatile  unsigned int hundreds, tens, units, tenths, hundredths, thousandths, tenthousandths,thousandth, ten_thousandths;
	volatile long int remainder;
    unsigned char string[30];

    c *= 10000;
    d = (long int)c;
    tens = d/100000;
    remainder =d - tens*100000;
    units = remainder/10000;
    remainder = remainder - units*10000;
	tenths = remainder/1000;
    remainder = remainder - tenths*1000;
    hundredths = remainder/100;
    remainder = remainder - hundredths *100;
    thousandth = remainder/10;
	remainder = remainder -thousandth*10;
	ten_thousandths=remainder;
    sprintf(string, "%d%d.%d%d%d%d", tens, units, tenths, hundredths,thousandth,ten_thousandths);
	UART_TX(string);

}

/************************************************************************/
/*  - name: UART_TX
 *  - Description:
 *  - input data:
 *  - output data:
 ***********************************************************************/

void UART_TX(char * tx_data)              // Define a function which accepts a character pointer to an array
{
	unsigned int i=0;
	while(tx_data[i])                     // Increment through array, look for null pointer (0) at end of string
	  {
	     while ((UCA0STAT & UCBUSY));     // Wait if line TX/RX module is busy with data
	     UCA0TXBUF = tx_data[i];          // Send out element i of tx_data array on UART bus
	     i++;                             // Increment variable for array address
	  }
}

/************************************************************************/
/*  - name: clear_V
 *  - Description: clear variables
 *  - input data:
 *  - output data:
 ***********************************************************************/

void clear_V(void){

	adc0_msb=0x00;
	adc0_lsb=0x00;
	adc1_msb=0x00;
	adc1_lsb=0x00;
	adc2_msb=0x00;
	adc2_lsb=0x00;
	adc3_msb=0x00;
	adc3_lsb=0x00;
	adc4_msb=0x00;
	adc4_lsb=0x00;
	adc5_msb=0x00;
	adc5_lsb=0x00;
	adc6_msb=0x00;
	adc6_lsb=0x00;
	adc7_msb=0x00;
	adc7_lsb=0x00;
	msp_ts_msb=0x00;
	msp_ts_lsb=0x00;
	avc_msb=0x00;
	avc_lsb=0x00;
	vr_msb=0x00;
	vr_lsb=0x00;
	tr_msb=0x00;
	tr_lsb=0x00;
	cr_msb=0x00;
	cr_lsb=0x00;
	acr_msb=0x00;
	acr_lsb=0x00;


}

