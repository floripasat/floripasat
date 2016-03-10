//*****************************************************************************
//! @file       bsp.h
//! @brief      Board support package header file for MSP430F5438A on
//!             SmartRF TrxEB.
//!
//! Revised     $Date: 2013-09-18 13:18:48 +0200 (on, 18 sep 2013) $
//! Revision    $Revision: 10587 $
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
#ifndef __BSP_H__
#define __BSP_H__


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
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>


/******************************************************************************
* DEFINES
*/
#define BSP_SYS_CLK_1MHZ        1000000UL
#define BSP_SYS_CLK_4MHZ        4000000UL
#define BSP_SYS_CLK_8MHZ        8000000UL
#define BSP_SYS_CLK_12MHZ       12000000UL
#define BSP_SYS_CLK_16MHZ       16000000UL
#define BSP_SYS_CLK_20MHZ       20000000UL
#define BSP_SYS_CLK_25MHZ       25000000UL

//
// Clock speed defines
//


//
//! Default system clock speed
//
#define BSP_SYS_CLK_SPD         BSP_SYS_CLK_8MHZ

//
// IO SPI defines
//
#define BSP_IO_SPI0             1
#define BSP_IO_SPI1             2

//
// IO SPI0 defines												(Exemplo para definir SPI-x no FloripaSat)
//#define BSP_IO_SPI0_BUS_BASE    __MSP430_BASEADDRESS_PORT9_R__
//#define BSP_IO_SPI0_PORT        9
//#define BSP_IO_SPI0_MOSI        BIT1        //! P9.1
//#define BSP_IO_SPI0_MISO        BIT2        //! P9.2
//#define BSP_IO_SPI0_SCLK        BIT3        //! P9.3


//
// LED defines													(Exemplo para definir LEDs no FloripaSat)
//#define BSP_LED_1               BIT0            //!< P4.0
//#define BSP_LED_2               BIT1            //!< P4.1
#define OBDH_LED_SYSTEM           BIT4            //!< P5.4

//
// key defines													(Exemplo para definir buttons no FloripaSat)
//#define BSP_KEY_1               BIT1            //!< P2.1
//#define BSP_KEY_2               BIT2            //!< P2.2




/******************************************************************************
* FUNCTION PROTOTYPES
*/
extern void bspInit(uint32_t ui32SysClockSpeed);
extern void bspSysClockSpeedSet(uint32_t ui32SystemClockSpeed);
extern void bspAssert(void);


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* #ifndef __BSP_H__ */
