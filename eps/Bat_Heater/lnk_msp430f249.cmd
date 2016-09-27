/* ============================================================================ */
/* Copyright (c) 2015, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/******************************************************************************/
/* lnk_msp430f249.cmd - LINKER COMMAND FILE FOR LINKING MSP430F249 PROGRAMS     */
/*                                                                            */
/*   Usage:  lnk430 <obj files...>    -o <out file> -m <map file> lnk.cmd     */
/*           cl430  <src files...> -z -o <out file> -m <map file> lnk.cmd     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* These linker options are for command line linking only.  For IDE linking,  */
/* you should set your linker options in Project Properties                   */
/* -c                                               LINK USING C CONVENTIONS  */
/* -stack  0x0100                                   SOFTWARE STACK SIZE       */
/* -heap   0x0100                                   HEAP AREA SIZE            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Version: 1.173                                                             */
/*----------------------------------------------------------------------------*/

/****************************************************************************/
/* Specify the system memory map                                            */
/****************************************************************************/

MEMORY
{
    SFR                     : origin = 0x0000, length = 0x0010
    PERIPHERALS_8BIT        : origin = 0x0010, length = 0x00F0
    PERIPHERALS_16BIT       : origin = 0x0100, length = 0x0100
    RAM                     : origin = 0x0200, length = 0x0800
    INFOA                   : origin = 0x10C0, length = 0x0040
    INFOB                   : origin = 0x1080, length = 0x0040
    INFOC                   : origin = 0x1040, length = 0x0040
    INFOD                   : origin = 0x1000, length = 0x0040
    FLASH                   : origin = 0x1100, length = 0xEEC0
    BSLSIGNATURE            : origin = 0xFFDE, length = 0x0002, fill = 0xFFFF
    INT00                   : origin = 0xFFC0, length = 0x0002
    INT01                   : origin = 0xFFC2, length = 0x0002
    INT02                   : origin = 0xFFC4, length = 0x0002
    INT03                   : origin = 0xFFC6, length = 0x0002
    INT04                   : origin = 0xFFC8, length = 0x0002
    INT05                   : origin = 0xFFCA, length = 0x0002
    INT06                   : origin = 0xFFCC, length = 0x0002
    INT07                   : origin = 0xFFCE, length = 0x0002
    INT08                   : origin = 0xFFD0, length = 0x0002
    INT09                   : origin = 0xFFD2, length = 0x0002
    INT10                   : origin = 0xFFD4, length = 0x0002
    INT11                   : origin = 0xFFD6, length = 0x0002
    INT12                   : origin = 0xFFD8, length = 0x0002
    INT13                   : origin = 0xFFDA, length = 0x0002
    INT14                   : origin = 0xFFDC, length = 0x0002
    INT16                   : origin = 0xFFE0, length = 0x0002
    INT17                   : origin = 0xFFE2, length = 0x0002
    INT18                   : origin = 0xFFE4, length = 0x0002
    INT19                   : origin = 0xFFE6, length = 0x0002
    INT20                   : origin = 0xFFE8, length = 0x0002
    INT21                   : origin = 0xFFEA, length = 0x0002
    INT22                   : origin = 0xFFEC, length = 0x0002
    INT23                   : origin = 0xFFEE, length = 0x0002
    INT24                   : origin = 0xFFF0, length = 0x0002
    INT25                   : origin = 0xFFF2, length = 0x0002
    INT26                   : origin = 0xFFF4, length = 0x0002
    INT27                   : origin = 0xFFF6, length = 0x0002
    INT28                   : origin = 0xFFF8, length = 0x0002
    INT29                   : origin = 0xFFFA, length = 0x0002
    INT30                   : origin = 0xFFFC, length = 0x0002
    RESET                   : origin = 0xFFFE, length = 0x0002
}

/****************************************************************************/
/* Specify the sections allocation into memory                              */
/****************************************************************************/

SECTIONS
{
    .bss        : {} > RAM                  /* Global & static vars              */
    .data       : {} > RAM                  /* Global & static vars              */
    .TI.noinit  : {} > RAM                  /* For #pragma noinit                */
    .sysmem     : {} > RAM                  /* Dynamic memory allocation area    */
    .stack      : {} > RAM (HIGH)           /* Software system stack             */

    .text       : {} > FLASH                /* Code                              */
    .cinit      : {} > FLASH                /* Initialization tables             */
    .const      : {} > FLASH                /* Constant data                     */
    .bslsignature  : {} > BSLSIGNATURE      /* BSL Signature                     */
    .cio        : {} > RAM                  /* C I/O Buffer                      */

    .pinit      : {} > FLASH                /* C++ Constructor tables            */
    .init_array : {} > FLASH                /* C++ Constructor tables            */
    .mspabi.exidx : {} > FLASH              /* C++ Constructor tables            */
    .mspabi.extab : {} > FLASH              /* C++ Constructor tables            */

    .infoA     : {} > INFOA              /* MSP430 INFO FLASH Memory segments */
    .infoB     : {} > INFOB
    .infoC     : {} > INFOC
    .infoD     : {} > INFOD

    /* MSP430 Interrupt vectors          */
    RESERVED0    : { * ( .int00 ) } > INT00 type = VECT_INIT
    RESERVED1    : { * ( .int01 ) } > INT01 type = VECT_INIT
    RESERVED2    : { * ( .int02 ) } > INT02 type = VECT_INIT
    RESERVED3    : { * ( .int03 ) } > INT03 type = VECT_INIT
    RESERVED4    : { * ( .int04 ) } > INT04 type = VECT_INIT
    RESERVED5    : { * ( .int05 ) } > INT05 type = VECT_INIT
    RESERVED6    : { * ( .int06 ) } > INT06 type = VECT_INIT
    RESERVED7    : { * ( .int07 ) } > INT07 type = VECT_INIT
    RESERVED8    : { * ( .int08 ) } > INT08 type = VECT_INIT
    RESERVED9    : { * ( .int09 ) } > INT09 type = VECT_INIT
    RESERVED10   : { * ( .int10 ) } > INT10 type = VECT_INIT
    RESERVED11   : { * ( .int11 ) } > INT11 type = VECT_INIT
    RESERVED12   : { * ( .int12 ) } > INT12 type = VECT_INIT
    RESERVED13   : { * ( .int13 ) } > INT13 type = VECT_INIT
    RESERVED14   : { * ( .int14 ) } > INT14 type = VECT_INIT
    USCIAB1TX    : { * ( .int16 ) } > INT16 type = VECT_INIT
    USCIAB1RX    : { * ( .int17 ) } > INT17 type = VECT_INIT
    PORT1        : { * ( .int18 ) } > INT18 type = VECT_INIT
    PORT2        : { * ( .int19 ) } > INT19 type = VECT_INIT
    RESERVED20   : { * ( .int20 ) } > INT20 type = VECT_INIT
    ADC12        : { * ( .int21 ) } > INT21 type = VECT_INIT
    USCIAB0TX    : { * ( .int22 ) } > INT22 type = VECT_INIT
    USCIAB0RX    : { * ( .int23 ) } > INT23 type = VECT_INIT
    TIMERA1      : { * ( .int24 ) } > INT24 type = VECT_INIT
    TIMERA0      : { * ( .int25 ) } > INT25 type = VECT_INIT
    WDT          : { * ( .int26 ) } > INT26 type = VECT_INIT
    COMPARATORA   : { * ( .int27 ) } > INT27 type = VECT_INIT
    TIMERB1      : { * ( .int28 ) } > INT28 type = VECT_INIT
    TIMERB0      : { * ( .int29 ) } > INT29 type = VECT_INIT
    NMI          : { * ( .int30 ) } > INT30 type = VECT_INIT
    .reset       : {}               > RESET  /* MSP430 Reset vector         */
}

/****************************************************************************/
/* Include peripherals memory map                                           */
/****************************************************************************/

-l msp430f249.cmd

