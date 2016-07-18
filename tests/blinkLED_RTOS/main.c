/* GENERAL includes. */
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

/* MSP430 includes. */
#include <msp430.h>
#include "driverlib/MSP430F5xx_6xx/driverlib.h"

/* System includes*/
#include "uart.h"

#define _4_MHz  1000000UL
#define _32_kHz   32768UL
#define _1_MHz  1000000UL

/*  General Functions */
void vSetupClock(void);

/*  Setup function. */
static void prvSetupHardware(void);

/* Tasks */
void vBlink_P5_4(void * pvParameters);
void vBlink_P1_7(void * pvParameters);
void vPrintTask(void * pvParameters);

/* Tasks ID's*/
xTaskHandle blink_p5_4;
xTaskHandle blink_p1_7;
xTaskHandle printTask;

int main(void) {

    prvSetupHardware();

    xTaskCreate( vBlink_P5_4, "Blink P5.4",configMINIMAL_STACK_SIZE, NULL, 1, &blink_p5_4 );
    xTaskCreate( vBlink_P1_7, "Blink P1.7",configMINIMAL_STACK_SIZE, NULL, 2, &blink_p1_7 );
    xTaskCreate( vPrintTask, "printTask",configMINIMAL_STACK_SIZE, NULL, 3, &printTask );

    vTaskStartScheduler();

    while (1);
}

/*
 *      General Functions
 */


void vSetupClock(void) {

      P1DIR |= BIT0;                            // ACLK set out to pin
      P1SEL |= BIT0;

      while(BAKCTL & LOCKBAK)                   // Unlock XT1 pins for operation
         BAKCTL &= ~(LOCKBAK);
      UCSCTL6 &= ~(XT1OFF);                     // XT1 On
      UCSCTL6 |= XCAP_3;                        // Internal load cap
      // Loop until XT1 fault flag is cleared
      do
      {
        UCSCTL7 &= ~(XT2OFFG | XT1LFOFFG | DCOFFG);
                                                // Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                      // Clear fault flags
      }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

      UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength

      UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)

  }
/*
 *      SETUP function
 */

static void prvSetupHardware( void ){
    WDT_A_hold(WDT_A_BASE);

    vSetupClock();

    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);

    vApplicationSetupTimerInterrupt();

    uart_setup(9600);

    __enable_interrupt();
}

/*
 *      Tasks
 */

void vBlink_P5_4(void * pvParameters){
    const TickType_t xDelay = 20 / portTICK_PERIOD_MS;
    for(;;)
    {
        uart_tx("blink p5.4 1 ************************************** \r\n");
        uart_tx("blink p5.4 2 ************************************** \r\n");
        uart_tx("blink p5.4 3 ************************************** \r\n");
        uart_tx("blink p5.4 4 ************************************** \r\n");
        uart_tx("blink p5.4 5 ************************************** \r\n");
        uart_tx("blink p5.4 6 ************************************** \r\n");
        vTaskDelay( xDelay );
    }
    vTaskDelete(blink_p5_4);
}

void vBlink_P1_7(void * pvParameters){
    const TickType_t xDelay = 40 / portTICK_PERIOD_MS;
    for(;;)
    {
        uart_tx("blink p1.7 1 ************************************** \r\n");
        uart_tx("blink p1.7 2 ************************************** \r\n");
        uart_tx("blink p1.7 3 ************************************** \r\n");
        uart_tx("blink p1.7 4 ************************************** \r\n");
        uart_tx("blink p1.7 5 ************************************** \r\n");
        uart_tx("blink p1.7 6 ************************************** \r\n");
        vTaskDelay( xDelay );
    }
    vTaskDelete(blink_p1_7);
}

void vPrintTask(void * pvParameters){
    const TickType_t xDelay = 80 / portTICK_PERIOD_MS;
    for(;;)
    {
       uart_tx("print task 1 ************************************** \r\n");
       uart_tx("print task 2 ************************************** \r\n");
       uart_tx("print task 3 ************************************** \r\n");
       uart_tx("print task 4 ************************************** \r\n");
       uart_tx("print task 5 ************************************** \r\n");
       uart_tx("print task 6 ************************************** \r\n");
       vTaskDelay( xDelay );
    }
    vTaskDelete(blink_p1_7);
}

/*
 *  Timer function
 */

void vApplicationSetupTimerInterrupt( void ){

    /* Ensure the timer is stopped. */
    TA0CTL = 0;

    /* Run the timer from the ACLK. */
    TA0CTL = TASSEL_1;

    /* Clear everything to start with. */
    TA0CTL |= TACLR;

    /* Set the compare match value according to
           the tick rate we want. */
    TA0CCR0 = _32_kHz / configTICK_RATE_HZ;

    /* Enable the interrupts. */
    TA0CCTL0 = CCIE;

    /* Start up clean. */
    TA0CTL |= TACLR;

    /* Up mode. */
    TA0CTL |= MC_1;
}




