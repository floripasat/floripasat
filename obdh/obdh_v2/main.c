#include <msp430.h> 
#include "fsat_tasks.h"
/*
 * main.c
 */
int main(void) {

    prvSetupHardware();
    static xTaskHandle led1Blink;
    static xTaskHandle uartSend;


    xTaskCreate( prvLedTask, "Led1Blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &led1Blink );
    xTaskCreate( prvUartTask, "UartSend", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &uartSend );

    vTaskStartScheduler();

    for( ;; );

	return 0;
}
