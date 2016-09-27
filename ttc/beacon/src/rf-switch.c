/*
 * rf-switch.c
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
 * \file rf-switch.c
 * 
 * \brief RF switch functions implementation
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \addtogroup rf_switch
 * \{
 */

#include "../inc/rf-switch.h"
#include "../driverlib/driverlib.h"

#if DEBUG_MODE == true
#include "../inc/debug.h"
#endif // DEBUG_MODE

void rf_switch_Init()
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf_switch_Init()");
#endif // DEBUG_MODE

    GPIO_setAsOutputPin(RF_SWT_CONTROL_PORT, RF_SWT_CONTROL_PIN);
    
	GPIO_setOutputLowOnPin(RF_SWT_CONTROL_PORT, RF_SWT_CONTROL_PIN);

#if DEBUG_MODE == true
    debug_PrintMsg("End of rf_switch_Init()\n");
#endif // DEBUG_MODE
}

void rf_switch_Enable()
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf_switch_Enable()");
#endif // DEBUG_MODE

    GPIO_setOutputHighOnPin(RF_SWT_CONTROL_PORT, RF_SWT_CONTROL_PIN);

#if DEBUG_MODE == true
    debug_PrintMsg("End of rf_switch_Enable()\n");
#endif // DEBUG_MODE
}

void rf_switch_Disable()
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf_switch_Disable()");
#endif // DEBUG_MODE

    GPIO_setOutputLowOnPin(RF_SWT_CONTROL_PORT, RF_SWT_CONTROL_PIN);
    
#if DEBUG_MODE == true
    debug_PrintMsg("End of rf_switch_Disable()\n");
#endif // DEBUG_MODE
}

//! \} End of rf_switch implementation group
