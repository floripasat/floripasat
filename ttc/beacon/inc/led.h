/*
 * led.h
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
 * \file led.h
 * 
 * \brief Initialization and control of the status led.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 11/10/2016
 * 
 * \defgroup led STATUS LED
 * \{
 */

#ifndef LED_H_
#define LED_H_

#include "../driverlib/driverlib.h"
#include <stdint.h>

#define BEACON_STATUS_LED_PORT  GPIO_PORT_P5    /**< Beacon status led port = 5 */
#define BEACON_STATUS_LED_PIN   GPIO_PIN4       /**< Beacon status led pin  = 4 */

/**
 * \fn led_Init
 * 
 * \brief Initialization of the status led.
 * 
 * \return None
 */
void led_Init();

/**
 * \fn led_Enable
 * 
 * \brief Turns on the status led.
 * 
 * \return None
 */
void led_Enable();

/**
 * \fn led_Disable
 * 
 * \brief Turns off the status led.
 * 
 * \return None
 */
void led_Disable();

/**
 * \fn led_Blink
 * 
 * \brief Blinks the status led with a desired frequency.
 * 
 * \param period is the blink period.
 * 
 * \return None
 */
void led_Blink(uint16_t period);

#endif // LED_H_

//! \} End of led group
