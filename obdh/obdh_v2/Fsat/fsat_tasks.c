#include "fsat_tasks.h"

void prvIMUTask( void *pvParameters )
{
    char data[31] = "123456789 imu__data 987654321-";
    int lenght = 0;

    //just for example
    static int cont = 0;
    int i;

    while(1)
    {
        lenght = 0;
        for(i = 0;i < IMU_DATA_LENGHT; i++)
        {
            imu_data[i] = data[cont];
            cont = (cont+1)%(sizeof(data)-1);
            lenght++;
        }

        /* before send, assert that the package has the correct lenght */
        configASSERT(lenght == IMU_DATA_LENGHT);

        #if VERIFY_BEFORE_SEND == 1
        data_flags |= IMU_FLAG;
        #endif

        //F = 1Hz
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}

void prvEPSTask( void *pvParameters )
{
    char data[33] = "EPS_MESSAGE:    DONT USE ENERGY!";
    int lenght = 0;
    //just for example
    static int cont = 0;
    int i;

    while(1)
    {
        lenght = 0;
        for(i = 0;i < EPS_DATA_LENGHT; i++)
        {
            eps_data[i] = data[cont];
            cont = (cont+1)%(sizeof(data)-1);
            lenght++;
        }

        /* before send, assert that the package has the correct lenght */
        configASSERT(lenght == EPS_DATA_LENGHT);

        #if VERIFY_BEFORE_SEND == 1
        data_flags |= EPS_FLAG;
        #endif
        //F = 1Hz
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}

void prvTTCTask( void *pvParameters )
{
    char data[31] = "ttc_data:  OK, I'm here yet...";
    int lenght = 0;
    //just for example
    static int cont = 0;
    int i;

    while(1)
    {
        lenght = 0;
        for(i = 0;i < TTC_DATA_LENGHT; i++)
        {
            ttc_data[i] = data[cont];
            cont = (cont+1)%(sizeof(data)-1);
            lenght++;
        }

        /* before send, assert that the package has the correct lenght */
        configASSERT(lenght == TTC_DATA_LENGHT);

        #if VERIFY_BEFORE_SEND == 1
        data_flags |= TTC_FLAG;
        #endif

        //F = 1Hz
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}

void prvSendUartTask( void *pvParameters )
{
    static char uart_package[UART_PACKAGE_LENGHT];
    int i, cont;

    while(1)
    {
        cont = 0;
        /* assemble the package */
        #if VERIFY_BEFORE_SEND == 1
        if(data_flags & EPS_FLAG)
        #endif
        for(i = 0;i < EPS_DATA_LENGHT; i++)
        {
            uart_package[i+cont] = eps_data[i];
        }
        cont += EPS_DATA_LENGHT; //proceed in the next positions on the package
        #if VERIFY_BEFORE_SEND == 1
        if(data_flags & IMU_FLAG)
        #endif
        for(i = 0;i < IMU_DATA_LENGHT; i++)
        {
            uart_package[i+cont] = imu_data[i];
        }
        cont += IMU_DATA_LENGHT; //proceed in the next positions on the package
        #if VERIFY_BEFORE_SEND == 1
        if(data_flags & TTC_FLAG)
        #endif
        for(i = 0;i < TTC_DATA_LENGHT; i++)
        {
            uart_package[i+cont] = ttc_data[i];
        }
        cont += TTC_DATA_LENGHT;

        /* assert that the package has the correct lenght (no module was forgotten */
        configASSERT(cont == UART_PACKAGE_LENGHT);


        #if VERIFY_BEFORE_SEND == 1
        if(data_flags) //if has any new message
        {
        #endif
        /* send package */
        for(i = 0;i < UART_PACKAGE_LENGHT; i++)
        {
            while (!(UCA2IFG & UCTXIFG));             // USCI_A0 TX buffer ready?
            UCA2TXBUF = uart_package[i];
        }

        while (!(UCA2IFG & UCTXIFG));
        UCA2TXBUF = 13; //put a new line
        while (!(UCA2IFG & UCTXIFG));
        UCA2TXBUF = 10; //put a new line

        #if VERIFY_BEFORE_SEND == 1
        }
        #endif

        #if VERIFY_BEFORE_SEND == 1
        data_flags = 0;
        #endif
        //F = 0.5Hz
        vTaskDelay( 500 / portTICK_PERIOD_MS );
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

    #if VERIFY_BEFORE_SEND == 1
    data_flags = 0;
    #endif
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
