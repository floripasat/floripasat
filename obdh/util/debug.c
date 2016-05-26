/*
 * debug.c
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */


#include "debug.h"

void debug_print(char* msg){
	if (DEBUG_LOG_ENABLE){
		uart_tx(msg);
	}
}



void debug(char* msg){
	if (DEBUG_LOG_ENABLE){
		uart_tx("[ ");
		//TODO:
		//should use the returned float from sysclock;
		//but it may be causing syslock drift (due debug print itself of sysclock float math)
		sprintf(tmpStr, "%u", sysclock_read_s() );
		uart_tx(tmpStr);
		uart_tx(".");
		sprintf(tmpStr, "%u", sysclock_read_ms() );
		uart_tx(tmpStr);
		uart_tx(" ] ");
		uart_tx(msg);
		uart_tx("\n\r");
	}
}



void debug_uint(char* msg, uint16_t value){
	if (DEBUG_LOG_ENABLE){
		uart_tx("[ ");
		//TODO:
		//should use the returned float from sysclock;
		//but it may be causing syslock drift (due debug print itself of sysclock float math)
		sprintf(tmpStr, "%u", sysclock_read_s() );
		uart_tx(tmpStr);
		uart_tx(".");
		sprintf(tmpStr, "%u", sysclock_read_ms() );
		uart_tx(tmpStr);
		uart_tx(" ] ");
		uart_tx(msg);
		uart_tx(" ");
		sprintf(tmpStr, "%u", value);
		uart_tx( tmpStr );
		uart_tx("\n\r");
	}
}


void debug_int(char* msg, int16_t value){
	if (DEBUG_LOG_ENABLE){
		uart_tx("[ ");
		//TODO:
		//should use the returned float from sysclock;
		//but it may be causing syslock drift (due debug print itself of sysclock float math)
		sprintf(tmpStr, "%u", sysclock_read_s() );
		uart_tx(tmpStr);
		uart_tx(".");
		sprintf(tmpStr, "%u", sysclock_read_ms() );
		uart_tx(tmpStr);
		uart_tx(" ] ");
		uart_tx(msg);
		uart_tx(" ");
		sprintf(tmpStr, "%d", value);
		uart_tx( tmpStr );
		uart_tx("\n\r");
	}
}





