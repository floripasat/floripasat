/*
 * watchdog.c
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
 * \file watchdog.c
 * 
 * \brief Watchdog functions implementation
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \addtogroup watchdog
 * \{
 */

#include "../inc/watchdog.h"
#include "../driverlib/driverlib.h"

void watchdog_Init()
{
    // Watchdog initialization (2 sec)
    WDT_A_initWatchdogTimer(WDT_A_BASE,
                            WDT_A_CLOCKSOURCE_SMCLK,
                            WDT_A_CLOCKDIVIDER_512);
    
    // Start counter
    WDT_A_start(WDT_A_BASE);
    
    // Enable Watchdog Interrupt
    SFR_enableInterrupt(SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT);
}

/**
 * \fn WDT_ISR
 * 
 * \brief 
 * 
 * \return None 
 */
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
    //#######################################
    // Watchdog procedure ?????????????????
    //#######################################
	WDT_A_resetTimer(WDT_A_BASE);
}

//! \} End of watchdog implementation group
