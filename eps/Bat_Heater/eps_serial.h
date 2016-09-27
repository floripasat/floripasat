#ifndef EPS_SERIAL_TEST_H_
#define EPS_SERIAL_TEST_H_



/********** UART functions **********/

void uart_tx(char *tx_data);
void config_MSP430_UART(void);
void float_send(float c);

#endif /* EPS_SERIAL_TEST_H_ */
