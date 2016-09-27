/*
 * debug.h
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
 * \file debug.h
 * 
 * \brief Functions for printing messages and bytes over UART
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \defgroup debug Debug
 * \ingroup beacon
 * \{
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdint.h>

#ifndef DEBUG_MODE
#define DEBUG_MODE true
#endif // DEBUG_MODE

//P8.2 = USCI_A1_TX_BEACON; P8.3 = USCI_A1_RX_BEACON
#define DEBUG_UART_PORT     GPIO_PORT_P8
#define DEBUG_UART_TX_PIN   GPIO_PIN2
#define DEBUG_UART_RX_PIN   GPIO_PIN3

/**
 * \fn debug_Init
 * 
 * \brief 
 * 
 * \return UART initialization status. It can be:
 *      - \b STATUS_SUCCES
 *      - \b STATUS_FAIL
 */
uint8_t debug_Init();

/**
 * \fn debug_PrintMsg
 * 
 * \brief 
 * 
 * \param msg
 * 
 * \return None
 */
void debug_PrintMsg(const char *msg);

/**
 * \fn debug_PrintByte
 * 
 * \brief 
 * 
 * \param msg
 * \param byte
 * 
 * \return None
 */
void debug_PrintByte(const char *msg, uint8_t byte);

/**
 * \fn debug_UART_Init
 * 
 * \brief Initialization of the debug UART (USCI_A1)
 * 
 * \return Initialization status. It can be:
 *      - \b STATUS_SUCCESS
 *      - \b STATUS_FAIL
 */
uint8_t debug_UART_Init();

//! \} End of Debug group

#endif // DEBUG_H_
