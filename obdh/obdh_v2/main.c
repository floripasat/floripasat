#include <msp430.h> 
#include "fsat_tasks.h"
/*
 * main.c
 */
int main(void) {

    prvSetupHardware();
    static xTaskHandle epsTask, imuTask, ttcTask;
    static xTaskHandle uartSend;


    xTaskCreate( prvEPSTask, "EPS", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &epsTask );
    xTaskCreate( prvIMUTask, "IMU", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &imuTask );
    xTaskCreate( prvTTCTask, "TTC", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &ttcTask );
    xTaskCreate( prvSendUartTask, "UartSend", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &uartSend );

    vTaskStartScheduler();

    for( ;; );

	return 0;
}
