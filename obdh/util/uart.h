
#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdio.h>


void uart_debug_setup(unsigned long baud_rate);
void uart_debug_tx(char *tx_data);
char uart_debug_rx(void);
void uart_tx_hello(void);
void uart_tx_newline(void);
void uart_set_baudrate(unsigned long baud_rate);

#endif
