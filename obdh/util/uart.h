
#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdio.h>


void uart_setup(void);
void uart_tx(unsigned char *tx_data);

void uart_tx_hello(void);

#endif
