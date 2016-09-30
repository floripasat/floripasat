/*
 * main.c
 * 
 * Copyright (C) 2016, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-TTC.
 * 
 * FloripaSat-TTC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-TTC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-TTC.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file main.c
 * 
 * \brief Main file
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \defgroup beacon Beacon
 * \{
 */

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/driverlib.h"

// Turn on/off debug mode
#define DEBUG_MODE true

// Turn on/off PA
#define PA_TEST false

#if DEBUG_MODE == true
#include "inc/debug.h"
#endif // DEBUG_MODE

#include "inc/watchdog.h"
#include "inc/cc11xx.h"
//#include "inc/rf-switch.h"
//#include "inc/rf6886.h"
//#include "inc/uart-eps.h"
#include "inc/delay.h"

#define BEACON_STATUS_LED_PORT  GPIO_PORT_P5
#define BEACON_STATUS_LED_PIN   GPIO_PIN4

#define F_CPU  4000000
#define SPICLK 400000

#define TX_MESSAGE "FloripaSat"

void GPIO_Init();
uint8_t SPI_Init();

/**
 * \fn main
 * 
 * \brief The main function.
 * 
 * After the initializations of the periphericals,
 * the program stays running in infinite loop.
 * 
 * \return None
 */
void main()
{
#if DEBUG_MODE == true
    WDT_A_hold(WDT_A_BASE);     // Disable watchdog for debug
    
    // UART for debug
    while(debug_Init() != STATUS_SUCCESS)
    {
        // Blinking system LED if something is wrong
        GPIO_toggleOutputOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
        delay_ms(500);
    }
#else
    //watchdog_Init();      // Todo: Fix watchdog
#endif // DEBUG_MODE
    
    GPIO_Init();
    
    while(SPI_Init() != STATUS_SUCCESS)
    {
        // Blinking system LED if something is wrong
        GPIO_toggleOutputOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
        delay_ms(1000);
    }
/*    
    // UART for EPS data
    while(UART_EPS_Init() != STATUS_SUCCESS)
    {
        // Blinking system LED if something is wrong
        GPIO_toggleOutputOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
        delay_ms(2000);
    }
*/    
    cc11xx_Init();
    
    // Data to send
    uint8_t tx_buffer[] = TX_MESSAGE;

    // Calibrate radio (See "CC112X, CC1175 Silicon Errata")
    cc11xx_ManualCalibration();
/*    
#if PA_TEST == true
    // Beacon PA initialization
    rf6886_Init();

    rf6886_SetVreg(3);   // DAC output = 3V

    rf6886_Enable();

    rf_switch_Init();
#endif // PA_TEST
*/
    // Infinite loop
    while(1)
    {
#if DEBUG_MODE == false
        WDT_A_resetTimer(WDT_A_BASE);
#endif // DEBUG_MODE

        // Flush the TX FIFO
        cc11xx_CmdStrobe(CC11XX_SFTX);

        // Write packet to TX FIFO
        cc11xx_WriteTXFIFO(tx_buffer, sizeof(tx_buffer));

        // Enable TX (Command strobe)
        cc11xx_CmdStrobe(CC11XX_STX);
/*
        // Wait for interrupt that packet has been sent.
        while(tx_ready != 1)
        {
            
        }

        tx_ready = 0;
*/
        // Blinking system LED (Faster than error blink)
        GPIO_toggleOutputOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);

        // Simple delay between packets
        delay_ms(50);
    }
}

/**
 * \fn GPIO_Init
 * 
 * \brief Initialization of the GPIO (Led, antenna deployment, etc.).
 * 
 * \return None
 */
void GPIO_Init()
{
#if DEBUG_MODE == true
    debug_PrintMsg("GPIO_Init()");
#endif // DEBUG_MODE

    // Beacon LED (LED_SYSTEM)
	GPIO_setAsOutputPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
	GPIO_setOutputHighOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
    
    /*
    // P1.1 = Enable beacon (ENE_3V3_PA_BEACON)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN1);
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN1);
    
    // P1.2 = OBDH status (OBDH_STATUS)
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN2);
    
    // P1.4 = Antenna deployment (BEACON_ANTENNA_DEPLOYMENT)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN4);
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN4);
    */
    // GPIO2 interrupt
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN5);
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);  // Interrupt on falling edge
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN5);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN5);
}

/**
 * \fn SPI_Init
 * 
 * \brief Initialization of the MCU SPI
 * 
 * Used interface: USCI_B0
 * 
 * \return Initialization status. It can be:
 *      - \b STATUS_SUCCESS
 *      - \b STATUS_FAIL
 *      .
 */
uint8_t SPI_Init()
{
#if DEBUG_MODE == true
    debug_PrintMsg("SPI_Init()");
#endif // DEBUG_MODE

    // MISO, MOSI and SCLK init.
    GPIO_setAsPeripheralModuleFunctionInputPin(CC11XX_SPI_PORT,
                                               CC11XX_MISO_PIN + CC11XX_MOSI_PIN + CC11XX_SCLK_PIN);
    
    // CSn init.
    GPIO_setAsOutputPin(CC11XX_CSN_PORT, CC11XX_CSN_PIN);
	GPIO_setOutputHighOnPin(CC11XX_CSN_PORT, CC11XX_CSN_PIN);   // CSn must be kept low during SPI transfers
    
    // Config. SPI as Master
    USCI_B_SPI_initMasterParam spi_params = {0};
    spi_params.selectClockSource     = USCI_B_SPI_CLOCKSOURCE_SMCLK;
    spi_params.clockSourceFrequency  = UCS_getSMCLK();
    spi_params.desiredSpiClock       = SPICLK;
    spi_params.msbFirst              = USCI_B_SPI_MSB_FIRST;
    spi_params.clockPhase            = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    spi_params.clockPolarity         = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;

    // SPI initialization
    if (USCI_B_SPI_initMaster(USCI_B0_BASE, &spi_params) == STATUS_FAIL)
    {
#if DEBUG_MODE == true
        debug_PrintMsg("\tFAIL!");
#endif // DEBUG_MODE

        return STATUS_FAIL;
    }
    else
    {
        // Enable SPI module
        USCI_B_SPI_enable(USCI_B0_BASE);
        
#if DEBUG_MODE == true
        debug_PrintMsg("\tSUCCESS!");
#endif // DEBUG_MODE

        return STATUS_SUCCESS;
    }
}

/**
 * \fn GPIO2_Interrupt
 * 
 * \brief General purpose IO interrupt function for GPIO port 1.
 * 
 * \return None
 */
/*#pragma vector=PORT1_VECTOR
__interrupt void GPIO2_Interrupt()
{
#if DEBUG_MODE == TRUE
    debug_PrintMsg("GPIO2 Interruption!");
#endif // DEBUG_MODE

    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN5);
    tx_ready = 1;
}
*/

//! \} End of beacon group
