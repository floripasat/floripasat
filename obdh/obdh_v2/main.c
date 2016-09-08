#include <msp430.h> 
#include "fsat_tasks.h"
/*
 * main.c
 */
int main(void) {
    prvSetupHardware();
    static xTaskHandle led1Blink;
    static xTaskHandle led2Blink;


    xTaskCreate( prvLed1Task, "Led1Blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &led1Blink );
    xTaskCreate( prvLed2Task, "Led2Blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &led2Blink );

    vTaskStartScheduler();

    for( ;; );

	return 0;
}
