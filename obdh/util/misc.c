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


char* int2char(int value){
	//up to MSP +- MAX_INT: +- 32767
	char buffer[10];
	sprintf(buffer, "%d", value);
	return buffer;
}


//deprecated. To be removed after team review
void int_to_char(int data, unsigned char string[], int size){
	int i,j,n;
	n=1;
	sprintf(string, "%d", data);
	///////// >> string /////////

	//discovering the index
	for(i=0; i < size;i++){
		if (string[i]==NULL){
			j=i;
			break;
		}
	}
	//shifting to right
	for(i=j;i>=0;i--){
		string[size - n++]=string[i-1];
	}

	//filling up with blank spaces
	for(i=size - j - 1;i>=0;i--){
		string[i]=' ';
	}
	/////////(end) >> string /////////
}
