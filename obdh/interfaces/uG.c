/*
 * uG.c
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#include "uG.h"
#include "../util/uart.h"



void uG_encode_dataframe (char*     ugFrame,
						  char*    obdhData,
						  char*   radioData,
						  char*     epsData,
						  char*     imuData,
						  uint8_t frameCRC8 ) {

	// Clear frame memory space (mark with known signature)
	int i;
	for (i=0; i<UG_FRAME_LENGTH; i++){
		ugFrame[i] = 0x20; // ASCII space
	}

	// Frame sent to uG Host mission: 41 Bytes
	// SOF (3B) + Payload (35B) + EOF (3B)
	// Ex: {{{BBB..BBB}\n\r
	// 7b 7b 7b 00 01 02 03 04  05 05 00 00 00 00 00 00 00 00 00 00 00 01 00 00 09 00 0d 01 02 03 04 05 06 07 08 09 0a 06 7d 0a 0d

	//Start of Frame
	ugFrame[0] = '{';				// 0x7B
	ugFrame[1] = '{';				// 0x7B
	ugFrame[2] = '{';				// 0x7B

	// Payload
	ugFrame[3]  = obdhData[0];		//Sysclock  S H
	ugFrame[4]  = obdhData[1];		//Sysclock  S L
	ugFrame[5]  = obdhData[2];		//Sysclock MS H
	ugFrame[6]  = obdhData[3];		//Sysclock MS L
	ugFrame[7]  = obdhData[4];		//Internal Temperature H
	ugFrame[8]  = obdhData[5];  	//Internal Temperature L
	ugFrame[9]  = obdhData[6];		//Status Code

	ugFrame[10] = imuData[0];		//Acc X H
	ugFrame[11] = imuData[1];		//Acc X L
	ugFrame[12] = imuData[2];		//Acc Y H
	ugFrame[13] = imuData[3];		//Acc Y L
	ugFrame[14] = imuData[4];		//Acc Z H
	ugFrame[15] = imuData[5];		//Acc Z L
	ugFrame[16] = imuData[6];		//Gyr X H
	ugFrame[17] = imuData[7];		//Gyr X L
	ugFrame[18] = imuData[8];		//Gyr Y H
	ugFrame[19] = imuData[9];		//Gyr Y L
	ugFrame[20] = imuData[10];		//Gyr Z H
	ugFrame[21] = imuData[11];		//Gyr Z L

	ugFrame[22] = radioData[0];		//Counter H
	ugFrame[23] = radioData[1];		//Counter L
	ugFrame[24] = radioData[2];		//Counter H
	ugFrame[25] = radioData[3];		//Counter L

	ugFrame[26] = epsData[0];		// Current H
	ugFrame[27] = epsData[1];		// Current L
	ugFrame[28] = epsData[2];		// Voltage BAT1 H
	ugFrame[29] = epsData[3];		// Voltage BAT1 L
	ugFrame[30] = epsData[4];		// Voltage BAT2 H
	ugFrame[31] = epsData[5];		// Voltage BAT2 L
	ugFrame[32] = epsData[6];		// Temperature  H
	ugFrame[33] = epsData[7];		// Temperature  L
	ugFrame[34] = epsData[8];		// Current Accum. H
	ugFrame[35] = epsData[9];		// Current Accum  L
	ugFrame[36] = epsData[10];		// Bat Mon. Protection Reg.

	ugFrame[37] = frameCRC8;		//CRC8

	// End of Frame
	ugFrame[38] = '}';				// 0x7D
	ugFrame[39] = '\n';				// 0x0A
	ugFrame[40] = '\r';				// 0x0D

}

void uG_send(char* dataframe, uint16_t length){

	int i;
	for (i=0; i<length; i++){
		uart_tx_char(dataframe[i]);
	}

}


void send2uZed(void){
//	debug("Sending to uZED/uG init");
//	debug("Sending FSAT FRAME TO uZED...\n\r"); //TODO rm
//    uart_tx(FSAT_frame);
//	frame2string(FSAT_frame,Debug_FSAT_Frame, sizeof Debug_FSAT_Frame); //TODO rm
//	debug(Debug_FSAT_Frame); //todo rm
//	debug("Sending to uZED/uG done");
//	wdt_reset_counter();
}



