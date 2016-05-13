
#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdio.h>


void uart_setup(unsigned long baud_rate);
void uart_tx(char *tx_data);

void uart_debug_tx(unsigned char *tx_data);
void uart_debug_tx_newline(void);
void uart_set_baudrate(unsigned long baud_rate);

#endif
