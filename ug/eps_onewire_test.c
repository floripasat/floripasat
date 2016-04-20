#include <msp430.h>
#include <stdio.h>
#include "intrinsics.h"
#include "eps_onewire_test.h"

#define P_WireOUT P5OUT
#define P_WireIN P5IN
#define DIR_P_Wire P5DIR
#define BitWire	BIT5

#define protection_register 0x00
#define protector_threshold_register 0x7F
#define status_register 0x01
#define control_register 0x60
#define accumulated_current_MSB_register 0x10
#define accumulated_current_LSB_register 0x11
#define temperature_MSB_register 0x0A
#define temperature_LSB_register 0x0B
#define average_current_MSB_register 0x08
#define average_current_LSB_register 0x09
#define current_gain_MSB_register 0x78
#define current_gain_LSB_register 0x79
#define current_MSB_register 0x0E
#define current_LSB_register 0x0F
#define voltage_MSB1_register 0x0C
#define voltage_LSB1_register 0x0D



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

volatile unsigned int RG_Protection;

unsigned char protection_register_msb = 0x00;
unsigned char protection_register_lsb = 0x00;

volatile unsigned int count = 0;


void config_MSP430_ONE_WIRE(void){
    P4SEL |= 0x20;
    P4OUT |= 0X20;

}


/************************************************************************/
/*  - name: outp
 *  - Description: This function sends bit to 1-wire slave.
 *  - input data: int bit
 *  - output data: --
 ***********************************************************************/

void outp(int bit){


	DIR_P_Wire |= BitWire;			//sets P5.5 as output

	if(bit == 0){
		P_WireOUT &= ~BitWire;           //drives P1.0 low
	}
	else{
		//P_WireOUT |= BitWire;           //releases the bus
	DIR_P_Wire &= ~BitWire;
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

	 DIR_P_Wire &= ~BitWire;          //sets P5.5 as input
	 result= P_WireIN & BitWire;         //prepares the bit on P1.0 to be returned

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

	int result=0;

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
 *  - input data:
 *  - output data: int data
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




void config_DS2784(void){
	// CONFIGURATION DS2784

	volatile unsigned int reset=0x1;
	reset= OneWireReset();				// PROTECTION REGISTER
	OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);					// write operation
	OWWriteByte(0x6C);					// write operation
	OWWriteByte(protection_register);	// register address
	OWWriteByte(0x03);					// value to be written

	reset= OneWireReset();              			// PROTECTOR THRESHOLD REGISTER
	OWWriteByte(0xCC);								// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);								// write operation
	OWWriteByte(protector_threshold_register);		// register address
	OWWriteByte(0x5C);								// value to be written

	reset= OneWireReset();				// STATUS REGISTER
	OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);					// write operation
	OWWriteByte(status_register);		// register address
	OWWriteByte(0x00);					// value to be written


	reset= OneWireReset();				// CONTROL REGISTER
	OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);					// write operation
	OWWriteByte(control_register);		// register address
	OWWriteByte(0x0C);					// value to be written

	reset= OneWireReset();								// ACCUMULATED CURRENT - MSB REGISTER
	OWWriteByte(0xCC);									// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);									// write operation
	OWWriteByte(accumulated_current_MSB_register);		// register address
	OWWriteByte(0x0A);									// value to be written

	reset= OneWireReset();								// ACCUMULATED CURRENT - LSB REGISTER
	OWWriteByte(0xCC);									// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);									// write operation
	OWWriteByte(accumulated_current_LSB_register);		// register address
	OWWriteByte(0x50);									// value to be written

}




/************************************************************************/
/*  - name: measurement_data_DS2784
 *  - Description:
 *  - input data: --
 *  - output data: --
 ***********************************************************************/
void measurement_data_DS2784(void){

    volatile unsigned int aux;
    volatile unsigned int reset=0x00;


   // TEMPERATURE MEASUREMENT

    reset= OneWireReset();              		// TEMPERATURE MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);							// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);							// read operation
    OWWriteByte(temperature_LSB_register);		// register address
    aux=OWReadByte();
    tr_lsb=aux>>5;

    reset= OneWireReset();              		// TEMPERATURE MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);							// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);							// read operation
    OWWriteByte(temperature_MSB_register);		// register address
    aux=OWReadByte();
    tr_msb=aux>>5;
    aux=aux<<3;
    tr_lsb|=aux & 0xF8;



    //AVERAGE CURRENT MEASUREMENT

    reset= OneWireReset();              			// AVERAGE CURRENT MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);								// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);								// read operation
    OWWriteByte(average_current_LSB_register);		// register address
    avc_lsb=OWReadByte();

    reset= OneWireReset();              			// AVERAGE CURRENT MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);								// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);								// read operation
    OWWriteByte(average_current_MSB_register);		// register address
    avc_msb=OWReadByte();


    //ACCUMULATED CURRENT MEASUREMENT

    reset= OneWireReset();              				// ACCUMULATED CURRENT MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);									// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);									// read operation
    OWWriteByte(accumulated_current_LSB_register);		// register address
    acr_lsb=OWReadByte();

    reset= OneWireReset();              			// ACCUMULATED CURRENT MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);								// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);								// read operation
    OWWriteByte(accumulated_current_MSB_register);	// register address
    acr_msb=OWReadByte();


    //CURRENT GAIN CALIBRATION

	reset= OneWireReset();              		// LSB CURRENT GAIN REGISTER
    OWWriteByte(0xCC);							// eeprom address (only one slave on bus, CC is used)
	OWWriteByte(0x6C);							// write operation
	OWWriteByte(current_gain_LSB_register);		// register address
	OWWriteByte(0x00);							// value to be written

	reset= OneWireReset();              		// MSB CURRENT GAIN REGISTER
	OWWriteByte(0xCC);							// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x6C);							// write operation
    OWWriteByte(current_gain_MSB_register);		// register address
	OWWriteByte(0x04);							// value to be written


   //CURRENT MEASUREMENT

    reset= OneWireReset();              //  CURRENT MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);					// read operation
    OWWriteByte(current_LSB_register);	// register address
    cr_lsb=OWReadByte();


    reset= OneWireReset();              // CURRENT MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);					// read operation
    OWWriteByte(current_MSB_register);	// register address
    cr_msb=OWReadByte();

    //VOLTAGE MEASUREMENT

    reset= OneWireReset();           	// VOLTAGE MEASUREMENT - LSB REGISTER
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);					// read operation
    OWWriteByte(voltage_LSB1_register);  // register address
    aux=OWReadByte();
    vr_lsb=aux>>5;

    reset= OneWireReset();              // VOLTAGE MEASUREMENT - MSB REGISTER
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);					// read operation
    OWWriteByte(voltage_MSB1_register);	// register address
    aux=OWReadByte();
    vr_msb=aux>>5;
    aux=aux<<3;
    vr_lsb|=aux & 0xF8;

    reset= OneWireReset();				// PROTECTION REGISTER
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x69);					// read operation
    OWWriteByte(protection_register);	// register address
    RG_Protection=OWReadByte();


    reset= OneWireReset();				// PROTECTION REGISTER CLEAR
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x6C);					// write operation
    OWWriteByte(protection_register);	// register address
    OWWriteByte(0x03);					// value to be written

    reset= OneWireReset();				// CONTROL REGISTER
    OWWriteByte(0xCC);					// eeprom address (only one slave on bus, CC is used)
    OWWriteByte(0x6C);					// write operation
    OWWriteByte(control_register);		// register address
    OWWriteByte(0x00);					// value to be written

}



