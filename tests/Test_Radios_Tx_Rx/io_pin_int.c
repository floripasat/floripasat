//*****************************************************************************
//! @file       io_pin_int.c
//! @brief      I/O pin interrupt handler for MSP430. It allows GPIO pins
//!             on the same GPIO port to have different interrupt handlers.
//!
//!             If \b IO_PIN_KEEP_POWER_MODE_ON_EXIT is defined, the generic
//!             GPIO port interrupt service routine does not turn off low power
//!             mode on exit.
//!
//!             \b Use:
//!
//!             1) Register a custom interrupt handler using ioPinIntRegister.
//!
//!             2) Unregister a custom interrupt handler using ioPinIntRegister
//!
//!             When using this module, a generic interrupt handler is assigned
//!             to the GPIO port. The generic interrupt handler calls the custom
//!             interrupt handler. If an interrupt is triggered on a pin without
//!             a custom interrupt handler, the generic interrupt handler
//!             simply clears the pin's interrupt flag.
//!
//!             Example:
//!             \code
//!             // Register interrupt handler to GPIO port C, pin 0
//!             ioPinIntRegister(IO_PIN_PORT_1, IO_PIN_0, &myIsr);
//!
//!             // Set interrupt type to rising edge
//!             ioPinIntTypeSet(IO_PIN_PORT_1, IO_PIN_0, IO_PIN_RISING_EDGE);
//!
//!             // Enable pin interrupt
//!             ioPinIntEnable(IO_PIN_PORT_1, IO_PIN_0);
//!
//!             // Enable master interrupt
//!             __enable_interrupt();
//!             \endcode
//!
//! Revised     $Date: 2013-04-11 20:13:51 +0200 (to, 11 apr 2013) $
//! Revision    $Revision: 9716 $
//
//  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//****************************************************************************/


/**************************************************************************//**
* @addtogroup io_pin_int_api I/O pin interrupt API
* @{
******************************************************************************/


/******************************************************************************
* INCLUDES
*/
#include "bsp.h"
#include "io_pin_int.h"


/******************************************************************************
* LOCAL VARIABLES AND PROTOTYPES
*/
// Lookup variables (a set bit in these variables means the corresponding gpio
// pin has a custom isr)
static uint_fast8_t ioPort1PinHasIsr;
static uint_fast8_t ioPort2PinHasIsr;

// Function pointer arrays
static void (*ioPort1IsrTable[8])(void);
static void (*ioPort2IsrTable[8])(void);

// Function prototypes
__interrupt void ioPort1Isr(void);
__interrupt void ioPort2Isr(void);


/******************************************************************************
* LOCAL VARIABLES AND PROTOTYPES
*/


/**************************************************************************//**
* @brief    Register an interrupt handler to the specified GPIO pin(s).
* 			This function will register a general ISR to the GPIO port
* 			and then assign the ISR specified by \e pfnIntHandler to the
* 			given pins.
*
* @param    ui32Base        The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins         The bit-packed representation of the pin(s)
* @param    pfnIntHandler   A pointer to the interrupt handling function
*
* @return   None
******************************************************************************/
void
ioPinIntRegister(uint32_t ui32Base, uint8_t ui8Pins,
                 void (*pfnIntHandler)(void))
{
    uint_fast8_t ui8Cnt;
    uint16_t ui16IntState;

    //
    // Critical section
    //
    ui16IntState = __get_interrupt_state();
    __disable_interrupt();

    if(pfnIntHandler)
    {
        //
        // Update HasIsr variables and clear interrupt flags
        //
        switch(ui32Base)
        {
        case IO_PIN_PORT_1:
            ioPort1PinHasIsr |=  ui8Pins;
            P1IFG &= (~ui8Pins);
            break;
        case IO_PIN_PORT_2:
            ioPort2PinHasIsr |=  ui8Pins;
            P2IFG &= (~ui8Pins);
            break;
        }
    }

    //
    // Go through pins
    //
    for(ui8Cnt = 0; ui8Cnt < 8; ui8Cnt++)
    {
        if(ui8Pins & (1 << ui8Cnt))
        {
            //
            // Place function to offset in the correct lookup table
            //
            switch(ui32Base)
            {
            case IO_PIN_PORT_1:
                ioPort1IsrTable[ui8Cnt] = pfnIntHandler;
                break;
            case IO_PIN_PORT_2:
                ioPort2IsrTable[ui8Cnt] = pfnIntHandler;
                break;
            default:
                break;
            }
        }
    }

    //
    // End critical section
    //
    __set_interrupt_state(ui16IntState);
}


/**************************************************************************//**
* @brief    Unregister an interrupt handler to the specified GPIO pin(s).
*
* @param    ui32Base          The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins          The bit-packed representation of the pin(s)
*
* @return   None
******************************************************************************/
void
ioPinIntUnregister(uint32_t ui32Base, uint8_t ui8Pins)
{
    //
    // Critical section
    //
    uint16_t ui16IntState = __get_interrupt_state();
    __disable_interrupt();

    //
    // Register null function to pins
    // Doing this is not necessary, but is less confusing during debug. If not
    // cleared, the pins' interrupt vector tables may be non-null even when
    // no custom ISR is actually registered. It is the ioPortXPinHasIsr vars
    // that are used to decide whether a custom interrupt is registered or not.
    //
    ioPinIntRegister(ui32Base, ui8Pins, 0);

    //
    // Clear "pin has isr" variables
    //
    switch(ui32Base)
    {
    case IO_PIN_PORT_1:
        ioPort1PinHasIsr &= ~ui8Pins;
        break;
    case IO_PIN_PORT_2:
        ioPort2PinHasIsr &= ~ui8Pins;
        break;
    }

    //
    // End critical section
    //
    __set_interrupt_state(ui16IntState);
}


/**************************************************************************//**
* @brief    Enable interrupt on the specified GPIO pin(s).
*
* @param    ui32Base          The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins          The bit-packed representation of the pin(s)
*
* @return   None
******************************************************************************/
void
ioPinIntEnable(uint32_t ui32Base, uint8_t ui8Pins)
{
    switch(ui32Base)
    {
    case IO_PIN_PORT_1:
        P1IE |= ui8Pins;
        return;
    case IO_PIN_PORT_2:
        P2IE |= ui8Pins;
        return;
    default:
        return;
    }
}


/**************************************************************************//**
* @brief    Disable interrupt on the specified GPIO pin(s).
*
* @param    ui32Base          The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins          The bit-packed representation of the pin(s)
*
* @return   None
******************************************************************************/
void
ioPinIntDisable(uint32_t ui32Base, uint8_t ui8Pins)
{
    switch(ui32Base)
    {
    case IO_PIN_PORT_1:
        P1IE &= (~ui8Pins);
        return;
    case IO_PIN_PORT_2:
        P2IE &= (~ui8Pins);
        return;
    default:
        return;
    }
}


/**************************************************************************//**
* @brief    Set interrupt edge on the specified GPIO pins.
*
* @param    ui32Base          The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins          The bit-packed representation of the pin(s)
* @param    ui8IntType       Interrupt trigger edge. Can be one of the following:
*                           \li \b IO_PIN_RISING_EDGE
*                           \li \b IO_PIN_FALLING_EDGE
*
* @return   None
******************************************************************************/
void
ioPinIntTypeSet(uint32_t ui32Base, uint8_t ui8Pins, uint8_t ui8IntType)
{
    switch(ui8IntType)
    {
    case IO_PIN_FALLING_EDGE:
        switch(ui32Base)
        {
        case IO_PIN_PORT_1:
            P1IES |= ui8Pins;
            return;
        case IO_PIN_PORT_2:
            P2IES |= ui8Pins;
            return;
        default:
            return;
        }

    case IO_PIN_RISING_EDGE:
        switch(ui32Base)
        {
        case IO_PIN_PORT_1:
            P1IES &= ~ui8Pins;
            return;
        case IO_PIN_PORT_2:
            P2IES &= ~ui8Pins;
            return;
        default:
            return;
        }
    default:
        return;
    }
}


/**************************************************************************//**
* @brief    Get interrupt status on the specified GPIO pins.
*
* @param    ui32Base          The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins          The bit-packed representation of the pin(s)
*
* @return   None
******************************************************************************/
uint8_t
ioPinIntStatus(uint32_t ui32Base, uint8_t ui8Pins)
{
    switch(ui32Base)
    {
    case IO_PIN_PORT_1:
        return (P1IFG & ui8Pins);
    case IO_PIN_PORT_2:
        return (P2IFG & ui8Pins);
    default:
        return (0);
    }
}


/**************************************************************************//**
* @brief    Clear interrupt flag on the specified GPIO pins.
*
* @param    ui32Base        The GPIO port. Can be one of the following:
*                           \li \b IO_PIN_PORT_1
*                           \li \b IO_PIN_PORT_2
* @param    ui8Pins          The bit-packed representation of the pin(s)
*
* @return   None
******************************************************************************/
void ioPinIntClear(uint32_t ui32Base, uint8_t ui8Pins)
{
    switch(ui32Base)
    {
    case IO_PIN_PORT_1:
        P1IFG &= ~(ui8Pins);
        return;
    case IO_PIN_PORT_2:
        P2IFG &= ~(ui8Pins);
        return;
    }
}


/******************************************************************************
* LOCAL FUNCTIONS
*/

/**************************************************************************//**
* @brief    General purpose IO interrupt function for GPIO port 1.
*           If an interrupt function handler is defined for the pins with
*           its interrupt flag set, this function is called. The interrupt
*           flag for this pin is then cleared. If no custom ISR is registered,
*           function simply clears the interrupt pin flag(s) and returns.
*
* @return   None
******************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void ioPort1Isr(void)
{
    register uint_fast8_t ui8IntBm, ui8IsrBm;

    //
    // Get bitmask of pins with interrupt triggered (and interrupt enabled)
    //
    ui8IntBm = P1IFG;
    ui8IntBm &= P1IE;

    //
    // Create bitmask of pins with interrupt _and_ custom isr
    //
    ui8IsrBm = (ui8IntBm & ioPort1PinHasIsr);

    if((ui8IsrBm & BIT0))
    {
        (*ioPort1IsrTable[0])();
    }
    if((ui8IsrBm & BIT1))
    {
        (*ioPort1IsrTable[1])();
    }
    if((ui8IsrBm & BIT2))
    {
        (*ioPort1IsrTable[2])();
    }
    if((ui8IsrBm & BIT3))
    {
        (*ioPort1IsrTable[3])();
    }
    if((ui8IsrBm & BIT4))
    {
        (*ioPort1IsrTable[4])();
    }
    if((ui8IsrBm & BIT5))
    {
        (*ioPort1IsrTable[5])();
    }
    if((ui8IsrBm & BIT6))
    {
        (*ioPort1IsrTable[6])();
    }
    if((ui8IsrBm & BIT7))
    {
        (*ioPort1IsrTable[7])();
    }

    //
    // Clear pin interrupt flags (custom isr or not)
    //
    P1IFG &= (~ui8IntBm);

#ifndef IO_PIN_KEEP_POWER_MODE_ON_EXIT
    //
    // Turn off low power mode
    //
    __low_power_mode_off_on_exit();
#endif
}


/**************************************************************************//**
* @brief    General purpose IO interrupt function for GPIO port 2.
*
* @see      ioPort1Isr
*
* @return   None
******************************************************************************/
#pragma vector=PORT2_VECTOR
__interrupt void ioPort2Isr(void)
{
    register uint_fast8_t ui8IntBm, ui8IsrBm;

    //
    // Get bitmask of pins with interrupt triggered (and interrupt enabled)
    //
    ui8IntBm = P2IFG;
    ui8IntBm &= P2IE;

    //
    // Create bitmask of pins with interrupt _and_ custom isr
    //
    ui8IsrBm = (ui8IntBm & ioPort2PinHasIsr);

    if((ui8IsrBm & BIT0))
    {
        (*ioPort2IsrTable[0])();
    }
    if((ui8IsrBm & BIT1))
    {
        (*ioPort2IsrTable[1])();
    }
    if((ui8IsrBm & BIT2))
    {
        (*ioPort2IsrTable[2])();
    }
    if((ui8IsrBm & BIT3))
    {
        (*ioPort2IsrTable[3])();
    }
    if((ui8IsrBm & BIT4))
    {
        (*ioPort2IsrTable[4])();
    }
    if((ui8IsrBm & BIT5))
    {
        (*ioPort2IsrTable[5])();
    }
    if((ui8IsrBm & BIT6))
    {
        (*ioPort2IsrTable[6])();
    }
    if((ui8IsrBm & BIT7))
    {
        (*ioPort2IsrTable[7])();
    }

    //
    // Clear pin interrupt flags (custom isr or not)
    //
    P2IFG &= (~ui8IntBm);

#ifndef IO_PIN_KEEP_POWER_MODE_ON_EXIT
    //
    // Turn off low power mode
    //
    __low_power_mode_off_on_exit();
#endif
}


/**************************************************************************//**
* Close the Doxygen group.
* @}
******************************************************************************/

