/*
 * obdh.c
 *
 *  Created on: 30 de mai de 2016
 *      Author: mario
 */

// Interface with internal components of the OBDH SoC

#include "obdh.h"
#include "../hal/engmodel1.h"

void obdh_read(char* obdhData) {

    //     Clear frame memory space
    int i;
    uint16_t sysclock_s;
    uint16_t sysclock_ms;
    for (i = 0; i < OBDH_DATA_LENGTH; i++) {
        obdhData[i] = 0x00;
    }

    sysclock_s = sysclock_read_s();
    sysclock_ms = sysclock_read_ms();
    obdh_temp_read();

    obdhData[0] = sysclock_s >> 8;		//sysclock  S high
    obdhData[1] = sysclock_s;		//sysclock  S low
    obdhData[2] = sysclock_ms >> 8;		//sysclock MS high
    obdhData[3] = sysclock_ms;		//sysclock MS low
    obdhData[4] = obdhTemperatureBuffer >> 8;		//temperature high
    obdhData[5] = obdhTemperatureBuffer;		//temperature low
    obdhData[6] = 5;		//system status code
}

char* obdh_data2string(char* stringBuffer, char* obdhData) {

    if (DEBUG_LOG_ENABLE) {

        temperatureDegC = (float) (((long) obdhTemperatureBuffer
                - CALADC12_15V_30C) * (85 - 30))
                / (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
        // Temperature in Fahrenheit Tf = (9/5)*Tc + 32
        //	temperatureDegF = temperatureDegC * 9.0f / 5.0f + 32.0f;

        sprintf(stringBuffer, "    Internal OBDH Temperature: %.3f C",
                temperatureDegC);
    }
    return stringBuffer;
}



void obdh_temp_convert(unsigned int temp){
	temperatureDegC = (float)(((long)temp - CALADC12_15V_30C) * (85 - 30)) /
	        (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
	// Temperature in Fahrenheit Tf = (9/5)*Tc + 32
	temperatureDegF = temperatureDegC * 9.0f / 5.0f + 32.0f;
}

void obdh_temp_read(void){
    ADC12CTL0 &= ~ADC12SC;
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
    ADC12IE = 0x001;                        // ADC_IFG upon conv result-ADCMEMO
}

void obdh_setup(void){


//	Internal temperature reading setup
	  REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
	                                            // ADC12_A ref control registers
	  ADC12CTL0 = ADC12SHT0_8 | ADC12REFON | ADC12ON;
	                                            // Internal ref = 1.5V
	  ADC12CTL1 = ADC12SHP;                     // enable sample timer
	  ADC12MCTL0 = ADC12SREF_1 | ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
	  __delay_cycles(DELAY_1_MS_IN_CYCLES);   // Allow ~100us (at default UCS settings)
	                                            // for REF to settle
	  ADC12CTL0 |= ADC12ENC;
}



/*
 * ADC ( temperature ) INTERRUPT VECTOR
*/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch (__even_in_range(ADC12IV, ADC12IV_ADC12IFG15))
  {
    case ADC12IV_NONE: break;                 // Vector  0:  No interrupt
    case ADC12IV_ADC12OVIFG: break;           // Vector  2:  ADC overflow
    case ADC12IV_ADC12TOVIFG: break;          // Vector  4:  ADC timing overflow
    case ADC12IV_ADC12IFG0:                   // Vector  6:  ADC12IFG0
        obdhTemperatureBuffer = ADC12MEM0;                     // Move results, IFG is cleared
//        debug_uint("temp = ADC12MEM0:", obdhTemperatureBuffer);
      break;
    case ADC12IV_ADC12IFG1: break;            // Vector  8:  ADC12IFG1
    case ADC12IV_ADC12IFG2: break;            // Vector 10:  ADC12IFG2
    case ADC12IV_ADC12IFG3: break;            // Vector 12:  ADC12IFG3
    case ADC12IV_ADC12IFG4: break;            // Vector 14:  ADC12IFG4
    case ADC12IV_ADC12IFG5: break;            // Vector 16:  ADC12IFG5
    case ADC12IV_ADC12IFG6: break;            // Vector 18:  ADC12IFG6
    case ADC12IV_ADC12IFG7: break;            // Vector 20:  ADC12IFG7
    case ADC12IV_ADC12IFG8: break;            // Vector 22:  ADC12IFG8
    case ADC12IV_ADC12IFG9: break;            // Vector 24:  ADC12IFG9
    case ADC12IV_ADC12IFG10: break;           // Vector 26:  ADC12IFG10
    case ADC12IV_ADC12IFG11: break;           // Vector 28:  ADC12IFG11
    case ADC12IV_ADC12IFG12: break;           // Vector 30:  ADC12IFG12
    case ADC12IV_ADC12IFG13: break;           // Vector 32:  ADC12IFG13
    case ADC12IV_ADC12IFG14: break;           // Vector 34:  ADC12IFG14
    case ADC12IV_ADC12IFG15: break;           // Vector 34:  ADC12IFG14
    default: break;
  }
}


