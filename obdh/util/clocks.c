/******************************************************************************************/
/*
 * clocks.c
 *
 *  Created on: 21 de jun de 2016
 *      Author: mfrata
 *
 */
/******************************************************************************************/

#include "clocks.h"

void MAIN_clocks_setup(void) {

    P7SEL |= BIT2+BIT3;                       // Port select XT2
    UCSCTL6 &= ~(XT1OFF + XT2OFF);            // XT1 On
    UCSCTL6 |= XCAP_3;                        // Sets internal load cap to 12pF(Datasheet)
    //todo try to remove this while, to a set timer (500ms acordding to the datasheet)
    //341.18 uS measured at the oscilloscope
    do {
                                             // Clear XT2,XT1,DCO fault flags
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;                   // Clear fault flags
    } while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
    UCSCTL6 &= ~(XT1DRIVE_3 + XT2DRIVE0);    // Xtal is now stable, reduce drive strength

    UCSCTL4 |= SELA_0     //Selects the ACLK source XT1CLK
             + SELS_5     //Selects the SMCLK source XT2CLK when available, otherwise DCOCLKDIV
             + SELM_5;    //Selects the MCLK source XT2CLK when available, otherwise DCOCLKDIV

    UCSCTL5 |= DIVS_2;    //SMCLK source divider = 4

// Uncomment this to see the clocks output to the pins below

//    P1DIR |= BIT0;                            // ACLK set out to pins
//    P1SEL |= BIT0;
//
//    P3DIR |= BIT4;                            // SMCLK set out to pins
//    P3SEL |= BIT4;
}
/******************************************************************************************/
