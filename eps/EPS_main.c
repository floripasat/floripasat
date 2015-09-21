#include <msp430.h>

#include "EPS_protocol.h"
#include "EPS_ADC.h"
#include "EPS_1wire.h"
#include "EPS_I2C.h"


/*
 * main.c
 */
void main(void){
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    ADC_main();				 // functon to read the MAX9634 outputs via ADC

    ONE_wire_main();		// function to configure and read measurements from DS2784

    write_data_package();	// fuction to package the data to be sent to OBC via I2C

    I2C_main();				// function that enables Tx/Rx via I2C with OBC



	

}







