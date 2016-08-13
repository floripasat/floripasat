//*****************************************************************************
//! @file       bsp.c
//! @brief      Board support package for MSP430F5438a on SmartRF06EB.
//!
//! Revised     $Date: 2013-09-18 13:18:48 +0200 (on, 18 sep 2013) $
//! Revision    $Revision: 10587 $
//
//  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
//****************************************************************************/


/**************************************************************************//**
* @addtogroup bsp_api
* @{
******************************************************************************/


/******************************************************************************
* INCLUDES
*/
#include "bsp.h"


/******************************************************************************
* DEFINES
*/
#define DCO_MULT_1MHZ           30
#define DCO_MULT_4MHZ           122
#define DCO_MULT_8MHZ           244
#define DCO_MULT_12MHZ          366
#define DCO_MULT_16MHZ          488
#define DCO_MULT_20MHZ          610
#define DCO_MULT_25MHZ          763

#define DCORSEL_1MHZ            DCORSEL_2
#define DCORSEL_4MHZ            DCORSEL_4
#define DCORSEL_8MHZ            DCORSEL_4
#define DCORSEL_12MHZ           DCORSEL_5
#define DCORSEL_16MHZ           DCORSEL_5
#define DCORSEL_20MHZ           DCORSEL_6
#define DCORSEL_25MHZ           DCORSEL_7

#define VCORE_1MHZ              PMMCOREV_0
#define VCORE_4MHZ              PMMCOREV_0
#define VCORE_8MHZ              PMMCOREV_0
#define VCORE_12MHZ             PMMCOREV_1
#define VCORE_16MHZ             PMMCOREV_1
#define VCORE_20MHZ             PMMCOREV_2
#define VCORE_25MHZ             PMMCOREV_3

#define VCORE_1_35V             PMMCOREV_0
#define VCORE_1_55V             PMMCOREV_1
#define VCORE_1_75V             PMMCOREV_2
#define VCORE_1_85V             PMMCOREV_3

// Register defines (In the TI example, this register is used to communicate the LCD and accelerometer with th MSP)
//#define IO_SPI0_BUS_DIR         P9DIR
//#define IO_SPI0_BUS_SEL         P9SEL
//#define IO_SPI0_BUS_OUT         P9OUT
//#define IO_SPI0_BUS_REN         P9REN
//
//#define IO_SPI1_BUS_DIR         IO_SPI0_BUS_DIR
//#define IO_SPI1_BUS_SEL         IO_SPI0_BUS_SEL
//#define IO_SPI1_BUS_OUT         IO_SPI0_BUS_OUT
//#define IO_SPI1_BUS_REN         IO_SPI0_BUS_REN


/******************************************************************************
* FUNCTION PROTOTYPES
*/
static void bspMcuGetSystemClockSettings(uint32_t ui32SystemClockSpeed,
                                         uint8_t *pui8SetDcoRange,
                                         uint8_t *pui8SetVCore,
                                         uint32_t *pui32SetMultiplier);


/******************************************************************************
* LOCAL VARIABLES
*/
static uint32_t ui32BspMclkSpeed;


/******************************************************************************
* FUNCTIONS
*/

/**************************************************************************//**
* @brief    Function initializes the MSP430F5438a clocks and I/O for use on
*           SmartRF06EB.
*
*           The function assumes an external crystal oscillator to be available
*           to the MSP430F5438a. The MSP430F5438a main system clock (MCLK) and
*           Sub Main System Clock (SMCLK) are set to the frequency given by
*           input argument \e ui32SysClockSpeed. ACLK is set to 32768 Hz.
*
* @param    ui32SysClockSpeed   is the system clock speed in MHz; it must be
*                               one of the following:
*           \li \b BSP_SYS_CLK_1MHZ
*           \li \b BSP_SYS_CLK_4MHZ
*           \li \b BSP_SYS_CLK_8MHZ
*           \li \b BSP_SYS_CLK_12MHZ
*           \li \b BSP_SYS_CLK_16MHZ
*           \li \b BSP_SYS_CLK_20MHZ
*           \li \b BSP_SYS_CLK_25MHZ
*
* @return   None
******************************************************************************/
void
bspInit(uint32_t ui32SysClockSpeed)
{
    uint16_t ui16IntState;

    //
    // Stop watchdog timer (prevent timeout reset)
    WDTCTL = WDTPW + WDTHOLD;

    //
    // Disable global interrupts
    ui16IntState = __get_interrupt_state();
    __disable_interrupt();

    //
    //  Set capacitor values for XT1, 32768 Hz */
    //bspMcuStartXT1();										//-------> verificar a necessidade dessa função


    bspSysClockSpeedSet(ui32SysClockSpeed);




    //
    // Initialize LEDs as off (pins as GPIO output high)	(Exemplo para inicializar o LED_SYSTEM (P5.4))
    //P5SEL &= ~OBDH_LED_SYSTEM;
    //P5OUT |=  OBDH_LED_SYSTEM;
    //P5DIR |=  OBDH_LED_SYSTEM;


    //
    // RF SPI0 CS as GPIO output high P2.3 					(CSn FloripaSat)
    P2SEL &= ~BIT3;
    P2OUT |=  BIT3;
    P2DIR |=  BIT3;


    // Visualizar ACLK no port P1.0 (pin 34)
    P1SEL |= BIT0;
    P1DIR |= BIT0;

    // Visualizar SMCLK no port P3.4 (pin 46)
	P3SEL |= BIT4;
	P3DIR |= BIT4;



    //
    // USB UART as GPIO input pullup						(Exemplo para definir a interface UART-0 (USCI-A2))
    //P5SEL &= ~(BIT6 | BIT7);
    //P5OUT |= (BIT6 | BIT7);
    //P5REN |= (BIT6 | BIT7);
    //P5DIR &= ~(BIT6 | BIT7);

    //
    // Return to previous interrupt state
    __set_interrupt_state(ui16IntState);
}



/**************************************************************************//**
* @brief    This is an assert function. It runs an infinite loop that blinks
*           all LEDs quickly. The function assumes LEDs to be initialized by,
*           for example,  bspInit().
*
* @return   None
******************************************************************************/
void
bspAssert(void)
{
    //
    // Set all LEDs to the same state before the infinite loop
    //
    //P5OUT |= OBDH_LED_SYSTEM;
    while(1)
    {
        //
        // Toggle LEDs
        //
        //P5OUT ^= OBDH_LED_SYSTEM;

        //
        // Simple wait
        //
        __delay_cycles(900000);
    }
}


/**************************************************************************//**
* @brief    This function sets the MCLK frequency. It also selects XT1 as ACLK
*           source with no divison in Low Power mode.
*
* @param    ui32SystemClockSpeed    is the intended frequency of operation.
*
* @return   None
******************************************************************************/
void
bspSysClockSpeedSet(uint32_t ui32SystemClockSpeed)
{
    uint8_t ui8SetDcoRange, ui8SetVCore;
    uint32_t ui32SetMultiplier;
    
    //
    // Set clocks (doing sanity check)
    // MCLK     = ui32SysClockSpeed;
    // SMCLK    = ui32SysClockSpeed;
    // ACLK     = 32 768 Hz
    //
    if((ui32SystemClockSpeed > 25000000UL) || (ui32SystemClockSpeed < 1000000UL))
    {
        bspAssert();
    }

    ui32BspMclkSpeed = ui32SystemClockSpeed;



    //
    // Get DCO, VCore and multiplier settings for the given clock speed
    //
    bspMcuGetSystemClockSettings(ui32SystemClockSpeed, &ui8SetDcoRange,
                                 &ui8SetVCore, &ui32SetMultiplier);
								//    *pui8SetDcoRange = DCORSEL_8MHZ;    	= DCORSEL_4 	= (0x0040)       /* DCO RSEL 4 */
								//    *pui8SetVCore = VCORE_8MHZ;			= PMMCOREV_0	= (0x0000)       /* PMM Core Voltage 0 (1.35V) */
								//    *pui32SetMultiplier = DCO_MULT_8MHZ;	= 244

    //
    // Set VCore setting
    //bspMcuSetVCore(ui8SetVCore)

    //
    // Disable FLL control loop, set lowest possible DCOx, MODx and select
    // a suitable range
    //
    __bis_SR_register(SCG0);
    UCSCTL0 = 0x00;
    UCSCTL1 = ui8SetDcoRange;											// Para 8MHz:  DCORSEL_4 	= (0x0040)       /* DCO RSEL 4 */

    // Set DCO multiplier and reenable the FLL control loop
    //
    UCSCTL2 = ui32SetMultiplier + FLLD_1;								// ui32SetMultiplier = 244,  FLLD_1 = 0x1000
    //UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV  |  SELM__DCOCLKDIV ;
    UCSCTL4 = SELA__REFOCLK | SELS__DCOCLKDIV  |  SELM__DCOCLKDIV ;		// ------> Adicionado para tirar o XT1 do clk
    //	     ACLK = SELA__VLOCLK | SMCLK = DCOCLKDIV| MCLK = DCOCLKDIV


    __bic_SR_register(SCG0);



    //
    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_FLL_reference. See UCS chapter in 5xx UG
    // for optimization.
    // 32 x 32 x / f_FLL_reference (32,768 Hz) = .03125 = t_DCO_settle
    // t_DCO_settle / (1 / 25 MHz) = 781250 = counts_DCO_settle
    //
    __delay_cycles(781250);


}




/*****************************************************************************
* @brief    Get function for the DCORSEL, VCORE, and DCO multiplier
*           settings that map to a given clock speed.
*
* @param    ui32SystemClockSpeed    is the target DCO frequency; can be one of
*           the following values:
*           \li \b BSP_SYS_CLK_1MHZ
*           \li \b BSP_SYS_CLK_4MHZ
*           \li \b BSP_SYS_CLK_8MHZ
*           \li \b BSP_SYS_CLK_12MHZ
*           \li \b BSP_SYS_CLK_16MHZ
*           \li \b BSP_SYS_CLK_20MHZ
*           \li \b BSP_SYS_CLK_25MHZ
* @param    pui8SetDcoRange         is a pointer to the DCO range select bits.
* @param    pui8SetVCore            is a pointer to the VCore level bits.
* @param    pui32SetMultiplier      is a pointer to the DCO multiplier bits.
*
* @return      None
******************************************************************************/
static void
bspMcuGetSystemClockSettings(uint32_t ui32SystemClockSpeed,
                             uint8_t *pui8SetDcoRange, uint8_t *pui8SetVCore,
                             uint32_t  *pui32SetMultiplier)
{
    switch(ui32SystemClockSpeed)
    {
    case BSP_SYS_CLK_1MHZ:
        *pui8SetDcoRange = DCORSEL_1MHZ;
        *pui8SetVCore = VCORE_1MHZ;
        *pui32SetMultiplier = DCO_MULT_1MHZ;
        break;
    case BSP_SYS_CLK_4MHZ:
        *pui8SetDcoRange = DCORSEL_4MHZ;
        *pui8SetVCore = VCORE_4MHZ;
        *pui32SetMultiplier = DCO_MULT_4MHZ;
        break;
    case BSP_SYS_CLK_8MHZ:
        *pui8SetDcoRange = DCORSEL_8MHZ;
        *pui8SetVCore = VCORE_8MHZ;
        *pui32SetMultiplier = DCO_MULT_8MHZ;
        break;
    case BSP_SYS_CLK_12MHZ:
        *pui8SetDcoRange = DCORSEL_12MHZ;
        *pui8SetVCore = VCORE_12MHZ;
        *pui32SetMultiplier = DCO_MULT_12MHZ;
        break;
    case BSP_SYS_CLK_16MHZ:
        *pui8SetDcoRange = DCORSEL_16MHZ;
        *pui8SetVCore = VCORE_16MHZ;
        *pui32SetMultiplier = DCO_MULT_16MHZ;
        break;
    case BSP_SYS_CLK_20MHZ:
        *pui8SetDcoRange = DCORSEL_20MHZ;
        *pui8SetVCore = VCORE_20MHZ;
        *pui32SetMultiplier = DCO_MULT_20MHZ;
        break;
    case BSP_SYS_CLK_25MHZ:
        *pui8SetDcoRange = DCORSEL_25MHZ;
        *pui8SetVCore = VCORE_25MHZ;
        *pui32SetMultiplier = DCO_MULT_25MHZ;
        break;
    }
}



/**************************************************************************//**
* Close the Doxygen group.
* @}
******************************************************************************/
