#include <msp430.h>
#include "EPS_1wire.h"


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


//configuration functions
void config_MSP430(void);
void config_DS2784(void);

//Measurement functions
void measurement_data_DS2784(void);


//1 wire protocol functions
void outp(int bit);
int inp(void);
int OneWireReset(void);
void OneWireWrite(int bit);
int OneWireReadBit(void);
void OWWriteByte(int data);
int OWReadByte(void);

//define

#define P_1WireOUT P1OUT
#define P_1WireIN P1IN
#define DIR_P_1Wire P1DIR





volatile int cont= 0;



/*************************************************************************/
//                        main
/************************************************************************/

void  ONE_wire_main(void)
{
	config_MSP430();

	config_DS2784();

	measurement_data_DS2784();


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
    P4SEL = 0x20;
    P4OUT=0X20;


	

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
/*  - name: measurement_data_DS2784
 *  - Description:
 *  - input data: --
 *  - output data: --
 ***********************************************************************/
void measurement_data_DS2784(void){

    volatile unsigned int aux;
    volatile unsigned int reset=0x1;


/*   // TEMPERATURE MEASUREMENT

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

    */
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

    CCTL0 = ~CCIE;



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

