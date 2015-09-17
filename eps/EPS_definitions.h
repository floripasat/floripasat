#include <msp430.h>

//---- start,end & header bytes ----//

#define	start_byte 			0x23	// '#' character
#define header_start_byte	0x25	// '%' character
#define end_byte			0x21	// '!' character

//----------------------------------//

//---- ADC bytes ----//

#define	adc0_msb	0x1
#define	adc0_lsb	0x2
#define adc1_msb	0x3
#define adc1_lsb	0x4
#define	adc2_msb	0x1
#define	adc2_lsb	0x2
#define	adc3_msb	0x1
#define	adc3_lsb	0x2
#define	adc4_msb	0x1
#define	adc4_lsb	0x2
#define	adc5_msb	0x1
#define	adc5_lsb	0x2
#define	adc6_msb	0x1
#define	adc6_lsb	0x2
#define	adc7_msb	0x1
#define	adc7_lsb	0x2

//----------------------------------//

//---- MSP430f249 internal temperature sensor bytes ----//

#define msp_ts_msb 0x10
#define msp_ts_lsb 0x11

//----------------------------------//

//---- DS2784 battery monitor bytes ----//

#define avc_msb 0x9		// average current msb
#define avc_lsb 0x8		// average current lsb
#define tr_msb 	0x7		// temperature register msb
#define tr_lsb 	0x6		// temperature register lsb
#define vr_msb 	0x10	// voltage register msb
#define vr_lsb 	0x5		// voltage register lsb
#define cr_msb	0x4		// current register msb
#define cr_lsb	0x3		// current register lsb
#define acr_msb	0xff	// accumulated current register msb
#define acr_lsb 0xff	// accumulated current register lsb
#define fault	0x0		// battery charger fault byte


//----------------------------------//

//---- Voltage Regulator Control Bytes ----//

#define ctr_reg_1		P4.2	// pin for control of 3v3 regulator number 1
#define ctr_reg_2		P4.4	// pin for control of 3v3 regulator number 2
#define ctr_reg_3		P4.6	// pin for control of 5v regulator

//---- MPPT Control Bytes ----//

#define ctr_mppt_1	0x0	//
#define ctr_mppt_2	0x0	//
#define ctr_mppt_3	0x0	//
#define ctr_mppt_4	0x0	//
#define ctr_mppt_5	0x0	//
#define ctr_mppt_6	0x0	//


//---- Status and Cyclic Redundancy Check Bytes ----//

#define mppt_st	0x0		// mppt status byte
#define reg_st	P4OUT	// voltage regulators status byte
#define	crc		0x0		// cyclic redundancy check byte





