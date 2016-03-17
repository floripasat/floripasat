//*****************************************************************************
//! @file       io_pin_int.h
//! @brief      I/O pin interrupt handler header file.
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
#ifndef __IO_PIN_INT_H__
#define __IO_PIN_INT_H__


/******************************************************************************
* If building with a C++ compiler, make all of the definitions in this header
* have a C binding.
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif


/******************************************************************************
* INCLUDES
*/
#include <stdint.h>

/******************************************************************************
* TYPEDEFS
*/

/******************************************************************************
* DEFINES
*/
#define IO_PIN_PORT_1           1
#define IO_PIN_PORT_2           2

#define IO_PIN_FALLING_EDGE     0
#define IO_PIN_RISING_EDGE      1


/******************************************************************************
* GLOBAL FUNCTIONS
*/
extern void ioPinIntRegister(uint32_t ui32Base, uint8_t ui8Pins,
                             void (*pfnIntHandler)(void) );
extern void ioPinIntUnregister(uint32_t ui32Base, uint8_t ui8Pins);
extern void ioPinIntEnable(uint32_t ui32Base, uint8_t ui8Pins);
extern void ioPinIntDisable(uint32_t ui32Base, uint8_t ui8Pins);
extern void ioPinIntTypeSet(uint32_t ui32Base, uint8_t ui8Pins,
                            uint8_t ui8IntType);
extern uint8_t ioPinIntStatus(uint32_t ui32Base, uint8_t ui8Pins);
extern void ioPinIntClear(uint32_t ui32Base, uint8_t ui8Pins);


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* #ifndef __IO_PIN_INT_H__ */
