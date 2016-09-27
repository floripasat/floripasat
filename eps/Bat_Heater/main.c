#include <msp430.h> 
#include <eps_serial.h>
#include <ADS1248.h>
#include <PWM.h>
#include <pid.h>
#include <stdlib.h>


void config_MSP430(void);

volatile float duty_cycle = 0;

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	volatile unsigned int n =0;
	volatile unsigned long t = 0;
	volatile float temperature = 0;
	volatile float room_temperature = 0;
	volatile extern long temp[];
    volatile Pid *parameters = malloc(sizeof *parameters);
    volatile int x = 0;
    parameters->LastProcessValue = 0;
    parameters->SumError = 0;
    parameters->ScalingFactor = 1;
    parameters->PFactor = 100000000;
    parameters->IFactor = 0;
    parameters->DFactor = 0;
    parameters->MaxError = INT_MAX;
    parameters->MaxSumError = INT_MAX;

    config_MSP430();
    config_ADS1248(0);
    while(1)
    {

    	read_ADS1248(0);
    	t = (temp[0] << 16) + (temp[1] << 8) + temp[2];
    	room_temperature = (t*0.000139326 - 1000)/3.85;

    	read_ADS1248(6);
    	t = (temp[0] << 16) + (temp[1] << 8) + temp[2];
    	temperature = (t*0.000139326 - 1000)/3.85;

    	duty_cycle = Pid_Control(30,temperature,parameters);

    	TBCCR3 = (1-duty_cycle)*PWM_PERIOD/2;

      	float_send(duty_cycle);
    	uart_tx(",");
    	float_send(temperature);
       	uart_tx(",");
       	float_send(room_temperature);
       	uart_tx("\r\n");

    }
}



void config_MSP430(void)
{



	/*** clock configuration ***/
	  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
	  DCOCTL = CALDCO_8MHZ;					  	// Set DCO
	  BCSCTL2 = DIVS_3;

	/*** SPI configuration ***/
	UCB1CTL0 |=  UCMSB + UCMST + UCSYNC;  				// 3-pin, 8-bit SPI master
	UCB1CTL1 |= UCSSEL_2;                     			// SMCLK
	UCB1BR0 |= 0x02;                          			// BRCLK = SMCLK/2
	UCB1BR1 = 0;                              			//
	UCB1CTL1 &= ~UCSWRST;                     			// **Initialize USCI state machine**
	P5OUT &= ~BIT0;                           			// reset slave - RST - active low
	P5OUT |= BIT0;                            			// Now with SPI signals initialized,

	/*** ADS1248 configuration ***/
	  P5DIR |= BIT0 + BIT4;     //
	  P5OUT = BIT0;                             // Set slave reset - P3.
	  P5SEL |= 0x0E;                            // P5.1,2,3 USCI_B1 option select
	  P4DIR |= BIT6;
	  P4OUT |= BIT6;

	/*** Heater PWM configuration***/
	  P4DIR |= BIT3;                            // P4.3 output
	  P4SEL |= BIT3;
	  TBCCR0 = PWM_PERIOD/2;                      // PWM Period/2
	  TBCCTL3 = OUTMOD_6;                         // CCR2 toggle/set
	  TBCCR3 = duty_cycle*PWM_PERIOD/2;       // CCR2 PWM duty cycle
	  TBCTL = TBSSEL_2 + MC_3;                  // SMCLK, up-down mode

	/*** UART configuration ***/
	  P3SEL |= 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
	  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCA0BR0 = 104;                            // 1MHz 9600; (104)decimal = 0x068h
	  UCA0BR1 = 0;                              // 1MHz 9600
	  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

//	  P4DIR |= BIT3;
//	  P4OUT |= BIT3;

}


