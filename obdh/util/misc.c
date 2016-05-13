/*
 * misc.c
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#include "misc.h"
#include "../hal/obdh_engmodel1.h"


void sysled_enable(void){
	SYSLED_PORT_DIR |= SYSLED_PIN; // set as output
	SYSLED_PORT_OUT &= ~SYSLED_PIN;
}


void sysled_toggle(void){
	SYSLED_PORT_OUT ^= SYSLED_PIN; //toggle port state
}

unsigned char CRC8(unsigned char *Data, unsigned int n) {
	unsigned char CRC, inbyte, Mix;    // CRC, inbyte e Mix tem 8 bits
	int i, j;
	for (i = 1; i < n - 2 ; i++) {              // contagem dos bytes(de 1 a n-2 para o floripa sat)
		inbyte = Data[i];
		for (j = 0; j < 8; j++) { 			// contagem dos bits de cada byte
			Mix = (CRC ^ inbyte) & 0x01;// Mix eh a divisao (xor) dos bytes da mensagem pelo polinomio crc
			CRC >>= 1;// CRC comeca em 0 e eh shiftado para a direita a cada iteracao
			if (Mix != 0)// se Mix for diferente de zero, o CRC vira o XOR dele mesmo com a mascara de bits 0x8C
				CRC ^= 0x8C;
			inbyte >>= 1;
		}
	}
	return CRC;
}



/*
 *
 * DEBUGGING FUNCTIONS
 *
*/

void frame_to_string(unsigned char frame[],unsigned char frame_string[], int size){
	int i;
	int j = 0;
	for(i=2; i < size; i+=5){
		frame_string[i]   = hex_to_char(frame[j] >> 4);
		frame_string[i+1] = hex_to_char(frame[j]);
		j++;
	}
}

unsigned char hex_to_char(unsigned char byte){
	char character;
	switch(byte & 0x0f){
		case 0x00: character = '0'; break;
		case 0x01: character = '1'; break;
		case 0x02: character = '2'; break;
		case 0x03: character = '3'; break;
		case 0x04: character = '4'; break;
		case 0x05: character = '5'; break;
		case 0x06: character = '6'; break;
		case 0x07: character = '7'; break;
		case 0x08: character = '8'; break;
		case 0x09: character = '9'; break;
		case 0x0A: character = 'A'; break;
		case 0x0B: character = 'B'; break;
		case 0x0C: character = 'C'; break;
		case 0x0D: character = 'D'; break;
		case 0x0E: character = 'E'; break;
		case 0x0F: character = 'F'; break;
	}
	return character;
}


unsigned char* int_to_char(int value){
	//up to MSP +- MAX_INT: +- 32767
	unsigned char buffer[intStringSize];
	sprintf(buffer, "%d", value);
	return buffer;
}

unsigned char* aligned_right(unsigned char* data){
	int i,j;
	int n = 1;
	unsigned char string[intStringSize];

	//copping data to string
	for(i=0; i < intStringSize;i++)
		string[i]= data[i];

	//discovering the index
	for(i=0; i < intStringSize;i++){
		if (string[i]==NULL){
			j=i;
			break;
		}
	}
	//shifting to right
	for(i=j;i>=0;i--)
		string[intStringSize - n++]=string[i-1];


	//filling up with blank spaces
	for(i=intStringSize - j - 1;i>=0;i--)
		string[i]=' ';

	return string;
}
