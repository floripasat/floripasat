
#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdio.h>

volatile unsigned char *PTxUart;

void uart_setup(void);
void uart_tx(char *tx_data);
void float_send(float c);
void int_send(int data);

void uart_tx_hello(void);

#endif
