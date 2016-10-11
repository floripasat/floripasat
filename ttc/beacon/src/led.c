/*
 * led.c
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
 * \file led.c
 * 
 * \brief Initialization and control of the status led.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 11/10/2016
 * 
 * \addtogroup led
 * \{
 */

#include "../inc/led.h"
#include "../inc/delay.h"

void led_Init()
{
    GPIO_setAsOutputPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
}

void led_Enable()
{
    GPIO_setOutputHighOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
}

void led_Disable()
{
    GPIO_setOutputLowOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
}

void led_Blink(uint16_t period)
{
    GPIO_toggleOutputOnPin(BEACON_STATUS_LED_PORT, BEACON_STATUS_LED_PIN);
    delay_ms(period/2);
}

//! \} End of led group
