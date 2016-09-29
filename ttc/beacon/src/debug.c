/*
 * debug.c
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
 * \file debug.c
 * 
 * \brief Debug functions implementation
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \addtogroup debug
 * \{
 */

#include "../inc/debug.h"
#include "../driverlib/driverlib.h"

uint8_t debug_Init()
{
    if (debug_UART_Init() == STATUS_FAIL)
    {
        return STATUS_FAIL;
    }
    else
    {
        char debug_msg[] = "FloripaSat-TTC Copyright (C) 2016, Universidade Federal de Santa Catarina;\n"
                           "This program comes with ABSOLUTELY NO WARRANTY.\n"
                           "This is free software, and you are welcome to redistribute it\n"
                           "under certain conditions.\n\n"
                           "Source code: https://github.com/mariobaldini/floripasat/tree/master/ttc\n"
                           "Documentation: http://fsat-server.duckdns.org:8000/ttc\n\n"
                           "FloripaSat debug mode:\n"
                           "*************************************\n";
        uint8_t i = 0;
        for(i=0;i<sizeof(debug_msg)-1;i++)
        {
            while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
            {
                
            }
            
            USCI_A_UART_transmitData(USCI_A1_BASE, debug_msg[i]);
        }
        
        return STATUS_SUCCESS;
    }
}

void debug_PrintMsg(const char *msg)
{
    uint8_t i = 0;
    while(msg[i] != '\0')
    {
        while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
        {
            
        }
        
        USCI_A_UART_transmitData(USCI_A1_BASE, msg[i]);
        i++;
    }
    
    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
    {
        
    }
    
    USCI_A_UART_transmitData(USCI_A1_BASE, '\n');
}

void debug_PrintByte(const char *msg, uint8_t byte)
{
    uint8_t i = 0;
    while(msg[i] != '\0')
    {
        while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
        {
            
        }
        USCI_A_UART_transmitData(USCI_A1_BASE, msg[i]);
        i++;
    }
    
    char hex_msg[] = "0x";
    for(i=0;i<sizeof(hex_msg)-1;i++)
    {
        while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
        {
            
        }
        USCI_A_UART_transmitData(USCI_A1_BASE, hex_msg[i]);
    }
    
    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
    {
        
    }
    uint8_t hex_to_ascii = (uint8_t)(byte >> 4);
    if (hex_to_ascii < 0x0A)
        USCI_A_UART_transmitData(USCI_A1_BASE, hex_to_ascii + 0x30);  // 0x30 = ascii 0
    else
        USCI_A_UART_transmitData(USCI_A1_BASE, hex_to_ascii + 0x37);  // 0x37 = ascii 7
    
    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
    {
        
    }
    hex_to_ascii = (uint8_t)(byte & 0x0F);
    if (hex_to_ascii < 0x0A)
        USCI_A_UART_transmitData(USCI_A1_BASE, hex_to_ascii + 0x30);  // 0x30 = ascii 0
    else
        USCI_A_UART_transmitData(USCI_A1_BASE, hex_to_ascii + 0x37);  // 0x37 = ascii 7
    
    while(!USCI_A_UART_getInterruptStatus(USCI_A1_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
    {
        
    }
    USCI_A_UART_transmitData(USCI_A1_BASE, '\n');
}

uint8_t debug_UART_Init()
{
    // UART pins init.
    GPIO_setAsPeripheralModuleFunctionInputPin(DEBUG_UART_PORT, DEBUG_UART_TX_PIN + DEBUG_UART_RX_PIN);
    
    // Config UART (115200 bps, no parity, 1 stop bit, LSB first)
    USCI_A_UART_initParam uart_params = {0};
    uart_params.selectClockSource   = USCI_A_UART_CLOCKSOURCE_SMCLK;
    uart_params.clockPrescalar      = 8;		// Clock = 1 MHz, Baudrate = 115200 bps	([1] http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html)
    uart_params.firstModReg         = 0;		// Clock = 1 MHz, Baudrate = 115200 bps (See [1])
    uart_params.secondModReg        = 6;		// Clock = 1 MHz, Baudrate = 115200 bps (See [1])
    uart_params.parity              = USCI_A_UART_NO_PARITY;
    uart_params.msborLsbFirst       = USCI_A_UART_LSB_FIRST;
    uart_params.numberofStopBits    = USCI_A_UART_ONE_STOP_BIT;
    uart_params.uartMode            = USCI_A_UART_MODE;
    uart_params.overSampling        = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;    // Clock = 1 MHz, Baudrate = 115200 bps (See [1])

    // UART initialization
    if (USCI_A_UART_init(USCI_A1_BASE, &uart_params) == STATUS_FAIL)
    {
        return STATUS_FAIL;
    }
    else
    {
        // Enable UART module
        USCI_A_UART_enable(USCI_A1_BASE);

        return STATUS_SUCCESS;
    }
}

//! \} End of debug implementation group
