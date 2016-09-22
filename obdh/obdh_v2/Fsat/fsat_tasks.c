#include "fsat_tasks.h"

void prvLedTask( void *pvParameters )
{
    while(1)
    {
        /* Block for 1000 milliseconds (1Hz) so this task does not utilise all the CPU
        time and debouncing of the button is not necessary. */
        vTaskDelay( 1000 / portTICK_PERIOD_MS );

        if( ( LED_PORT_OUT & LED_1 ) == 0 )
        {
            LED_PORT_OUT |= LED_1;
        }
        else
        {
            LED_PORT_OUT &= ~LED_1;
        }
    }
}

void prvUartTask( void *pvParameters )
{
    char data = 0;
    while(1)
    {
        /* Block for 500 milliseconds (2Hz) so this task does not utilise all the CPU
        time and debouncing of the button is not necessary. */
        vTaskDelay( 500 / portTICK_PERIOD_MS );

        while (!(UCA2IFG & UCTXIFG));             // USCI_A0 TX buffer ready?
        UCA2TXBUF = data + 'a';
        data = (data + 1) % ('z' - 'a' + 1); //just to print abc...xyzabc...
    }
}

void prvSetupUart( void )
{
    P9SEL |= BIT2 + BIT3;                            // Assign P2.0 to UCA0TXD and...

    UCA2CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA2CTL1 |= UCSSEL_2;                     // SMCLK
    UCA2BR0 = 6;                              // 1MHz 9600 (see User's Guide)
    UCA2BR1 = 0;                              // 1MHz 9600
    UCA2MCTL = UCBRS_0 | UCBRF_13 | UCOS16;   // Modln UCBRSx=0, UCBRFx=0,
                                                // over sampling
    UCA2CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}


void prvSetupHardware( void )
{
    taskDISABLE_INTERRUPTS();

    /* Disable the watchdog. */
    WDTCTL = WDTPW + WDTHOLD;

    prvSetupUart();

    LED_PORT_OUT = 0x00;
    LED_PORT_DIR |= LED_1;
}


void vApplicationTickHook( void )
{
    static unsigned long ulCounter = 0;

    /* Is it time to toggle the LED again? */
    ulCounter++;

    if( ( ulCounter & 0xff ) == 0 )
    {
        /* Once in 256 tick counts, do that */
    }
}
/*-----------------------------------------------------------*/

/* The MSP430X port uses this callback function to configure its tick interrupt.
This allows the application to choose the tick interrupt source.
configTICK_VECTOR must also be set in FreeRTOSConfig.h to the correct
interrupt vector for the chosen tick interrupt source.  This implementation of
vApplicationSetupTimerInterrupt() generates the tick from timer A0, so in this
case configTICK_VECTOR is set to TIMER0_A0_VECTOR. */
void vApplicationSetupTimerInterrupt( void )
{
const unsigned short usACLK_Frequency_Hz = 32768;

    /* Ensure the timer is stopped. */
    TA0CTL = 0;

    /* Run the timer from the ACLK. */
    TA0CTL = TASSEL_1;

    /* Clear everything to start with. */
    TA0CTL |= TACLR;

    /* Set the compare match value according to the tick rate we want. */
    TA0CCR0 = usACLK_Frequency_Hz / configTICK_RATE_HZ;

    /* Enable the interrupts. */
    TA0CCTL0 = CCIE;

    /* Start up clean. */
    TA0CTL |= TACLR;

    /* Up mode. */
    TA0CTL |= MC_1;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    /* Called on each iteration of the idle task.  In this case the idle task
    just enters a low(ish) power mode. */
    __bis_SR_register( LPM1_bits + GIE );
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues or
    semaphores. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pxTask;
    ( void ) pcTaskName;

    /* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/
