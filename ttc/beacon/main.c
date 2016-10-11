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

#define F_CPU 4000000               /**< Clock frequency of the MCU. */

// Turn on/off debug mode
#define DEBUG_MODE true             /**< Debug mode flag. */

#if DEBUG_MODE == true
#include "inc/debug.h"
#endif // DEBUG_MODE

#include "inc/watchdog.h"
#include "inc/led.h"
#include "inc/cc11xx.h"
#include "inc/rf-switch.h"
#include "inc/rf6886.h"
//#include "inc/uart-eps.h"
#include "inc/delay.h"

#define TX_MESSAGE "FloripaSat"     /**< Message to transmit. */

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
    
    led_Init();
    led_Enable();
    
    // UART for debug
    while(debug_Init() != STATUS_SUCCESS)
    {
        // Blinking system LED if something is wrong
        led_Blink(1000);
    }
#else
    //watchdog_Init();      // Todo: Fix watchdog
    
    led_Init();
    led_Enable();
#endif // DEBUG_MODE
    
/*    
    // UART for EPS data
    while(UART_EPS_Init() != STATUS_SUCCESS)
    {
        // Blinking system LED if something is wrong
        led_Blink(4000);
    }
*/    
    cc11xx_Init();

    // Calibrate radio (See "CC112X, CC1175 Silicon Errata")
    cc11xx_ManualCalibration();
 
    // Beacon PA initialization
    while(rf6886_Init() != STATUS_SUCCESS)
    {
        // Blinking system LED if something is wrong
        led_Blink(3000);
    }

    rf6886_Enable();

    rf6886_SetVreg(3.1);   // DAC output = 3,1V

    rf_switch_Init();
    
    rf_switch_Enable();

    // Data to send
    uint8_t tx_buffer[] = TX_MESSAGE;

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

        // Heartbeat
        led_Blink(100);
    }
}

//! \} End of beacon group
