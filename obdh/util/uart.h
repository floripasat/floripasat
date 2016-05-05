
#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdio.h>


void uart_setup(unsigned long baud_rate);
void uart_tx(unsigned char *tx_data);
unsigned char uart_rx(void);
void uart_tx_hello(void);
void set_baud_rate(unsigned long baud_rate);

#endif
