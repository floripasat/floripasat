#include <msp430.h> 
#include <eps_onewire_test.h>
#include <eps_i2c.h>
#include <eps_timer_test.h>
#include <eps_serial.h>
#include <watchdog.h>


void config_MSP430(void);


void main(void) {
    config_MSP430();
    wdt_reset_counter();
    config_MSP430_UART();
    config_DS2784();
    __bis_SR_register(GIE);        // Enter LPM0 w/ interrupts
    wdt_reset_counter();
    while(1);
}


void config_MSP430(void)
{
	P1DIR |= BIT6;
	P1OUT ^= BIT6;
	P3DIR |= BIT6;

	/*** clock configuration ***/
	  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
	  DCOCTL = CALDCO_8MHZ;					  	// Set DCO

	/*** WDT configuration ***/
	watchdog_setup(WATCHDOG,_188_mSEC);

	/*** I2C Configuration ***/
	  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
	  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
	  UCB0I2COA = 0x13;                         // Own Address is 0ABh
	  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	//  UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable STT and STP interrupt
	  IE2 |= UCB0TXIE;                          // Enable TX interrupt

	/*** timer configuration ***/
	  CCTL0 = CCIE;                             // CCR0 interrupt enabled
	  CCR0 =50000;							    // timer A capture and compare register
	  TACTL = TASSEL_2 + MC_3;                   // SMCLK, contmode

//	  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
//	  TBCTL = TBSSEL_1 + MC_1 + ID_3;           // ACLK, contmode, clock divider /8
//	  TBCCR0 = 2660;
}


