/**
 * RTC implementation for
 */
#include <msp430.h>

unsigned int Sec;
void MAIN_clocks_setup(void);
static void RTC_setup(void);

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    P1DIR |= BIT7;                            // P1.0 Output
    P1OUT &= ~BIT7;                           // Clear LED to start

    MAIN_clocks_setup();

    RTC_setup();

    __bis_SR_register(GIE);       // Enter LPM3 mode with interrupts
                                  // enabled
    while (1) {
    }

}


/**
 *     MAIN_clocks_setup will configure the ACLK clock to be sourced by the XT1 32768 Hz
 *  external Crystal. And the SMCLK to be sourced by the XT2 4 MHz Ext. Crystal. SMCLK
 *  out puts 1 MHz.
 *     The MCLK also is sourced by the 4 MHz crystal.
 */
//todo separate into one function to each clk
void MAIN_clocks_setup(void) {

    P7SEL |= BIT2+BIT3;                       // Port select XT2
    UCSCTL6 &= ~(XT1OFF + XT2OFF);            // XT1 On
    UCSCTL6 |= XCAP_3;                        // Sets internal load cap to 12pF(Datasheet)
    //todo try to remove this while, to a set timer (500ms acordding to the datasheet)
    P1OUT ^= BIT7;
    do {
                                             // Clear XT2,XT1,DCO fault flags
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;                   // Clear fault flags
    } while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
    P1OUT ^= BIT7;
    UCSCTL6 &= ~(XT1DRIVE_3 + XT2DRIVE0);    // Xtal is now stable, reduce drive strength

    UCSCTL4 |= SELA_0     //Selects the ACLK source XT1CLK
             + SELS_5     //Selects the SMCLK source XT2CLK when available, otherwise DCOCLKDIV
             + SELM_5;    //Selects the MCLK source XT2CLK when available, otherwise DCOCLKDIV

    UCSCTL5 |= DIVS_2;    //SMCLK source divider = 4

// Descomment this to see the clocks output to the pins below
//    P1DIR |= BIT0;                            // ACLK set out to pins
//    P1SEL |= BIT0;
//
//    P3DIR |= BIT4;                            // SMCLK set out to pins
//    P3SEL |= BIT4;
}
/******************************************************************************************/

/**
 *     RTC_setup will configure the RTC_B to the calendar mode, generating one interruption
 * every second. RTC uses a external crystal(XT1) by default, it can't be modified.
 */
static void RTC_setup(void) {
    RTCCTL01 |= RTCRDYIE    //Real-time clock ready interrupt enable(every second)
               + RTCOFIE    //32-kHz crystalo scillator fault interrupt enable.
               + RTCHOLD;   //Real-time clock hold
    RTCSEC = 0x00;          //Start Seconds at Seconds = 0x00
    RTCCTL01 &= ~(RTCHOLD); // Start RTC calendar mode
}
/******************************************************************************************/

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt void RTCISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(RTC_VECTOR))) RTCISR (void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(RTCIV, 14)) {
    case 0:
        break;                           // Vector  0:  No interrupt
    case 2:                              // Vector  2:  RTCRDYIFG
//        P1OUT ^= BIT7;
        break;
    case 4:
        break;                           // Vector  4:  RTCEVIFG
    case 6:
        break;                           // Vector  6:  RTCAIFG
    case 8:
        break;                           // Vector  8:  RT0PSIFG
    case 10:
        break;                           // Vector 10:  RT1PSIFG
    case 12:
        break;                           // Vector 12:  RTCOFIFG
    case 14:
        break;                           // Vector 14:  Reserved
    default:
        break;
    }
}
