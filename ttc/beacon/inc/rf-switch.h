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
 * \file rf-switch.h
 * 
 * \brief Functions for printing messages and bytes over UART
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \defgroup rf_switch RF Switch
 * \ingroup beacon
 * \{
 */

/*
 * RF Switch truth table (OBDHTTC_Diagrama-Geral.pdf)
 * 
 * ------------------------------------------
 *    Input     |     Output    |
 * ------------------------------  SWT-SP3T
 *  A   B   C   |   V1  V2  V3  |    Mode
 * ------------------------------------------
 *  0   0   0   |   0   0   0   |   Off
 *  0   0   1   |   0   0   1   |   Beacon
 *  0   1   0   |   0   1   0   |   TX
 *  0   1   1   |   0   0   1   |   Beacon
 *  1   0   0   |   1   0   0   |   RX
 *  1   0   1   |   0   0   1   |   Beacon
 *  1   1   0   |   1   0   0   |   RX
 *  1   1   1   |   0   0   1   |   Beacon
 * ------------------------------------------
 * 
 * Beacon is always on when C (CTRL_RF_SWT_BEACON = P5.5) is high
 * 
 */

#ifndef RF_SWITCH_H_
#define RF_SWITCH_H_

// P5.5 = CTRL_RF_SWT_BEACON
#define RF_SWT_CONTROL_PORT     GPIO_PORT_P5
#define RF_SWT_CONTROL_PIN      GPIO_PIN5

/**
 * \fn rf_switch_Init
 * 
 * \brief Initizalization of RF switch control.
 * 
 * \return None
 */
void rf_switch_Init();

/**
 * \fn rf_switch_Enable
 * 
 * \brief Enable beacon TX.
 * 
 * \return None
 */
void rf_switch_Enable();

/**
 * \fn rf_switch_Disable
 * 
 * \brief Disable beacon TX.
 * 
 * \return None
 */
void rf_switch_Disable();

#endif // RF_SWITCH_H_

//! \} End of RFSwitch group
