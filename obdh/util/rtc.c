/*
 * rtc_builtin.c
 *
 *  Created on: 23 de mai de 2016
 *      Author: mario
 */


void RTCA_setup(void) {

//	RTCCTL01 = RTCMODE; // + RTCTEVIE;
//	  RTCCTL23 = RTCCALF_1; // 512Hz output
//	  P2DIR |= BIT6;
//	  P2SEL |= BIT6;
//	  RTCPS0CTL = RT0PSIE + RT0IP_7; // 32768/256 = 128 interrupts per sec


}

unsigned long RTCA_counter(void) {

	return 0;
}
