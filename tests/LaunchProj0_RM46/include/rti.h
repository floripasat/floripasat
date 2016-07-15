/** @file rti.h
*   @brief RTI Driver Header File
*   @date 17.Nov.2014
*   @version 04.02.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the RTI driver.
*/

/* 
* Copyright (C) 2009-2014 Texas Instruments Incorporated - http://www.ti.com/ 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



#ifndef __RTI_H__
#define __RTI_H__

#include "reg_rti.h"

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* RTI General Definitions */

/** @def rtiCOUNTER_BLOCK0
*   @brief Alias name for RTI counter block 0
*
*   This is an alias name for the RTI counter block 0.
*
*   @note This value should be used for API argument @a counter
*/
#define rtiCOUNTER_BLOCK0 0U

/** @def rtiCOUNTER_BLOCK1
*   @brief Alias name for RTI counter block 1
*
*   This is an alias name for the RTI counter block 1.
*
*   @note This value should be used for API argument @a counter
*/
#define rtiCOUNTER_BLOCK1 1U

/** @def rtiCOMPARE0
*   @brief Alias name for RTI compare 0
*
*   This is an alias name for the RTI compare 0.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE0 0U

/** @def rtiCOMPARE1
*   @brief Alias name for RTI compare 1
*
*   This is an alias name for the RTI compare 1.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE1 1U

/** @def rtiCOMPARE2
*   @brief Alias name for RTI compare 2
*
*   This is an alias name for the RTI compare 2.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE2 2U

/** @def rtiCOMPARE3
*   @brief Alias name for RTI compare 3
*
*   This is an alias name for the RTI compare 3.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE3 3U

/** @def rtiNOTIFICATION_COMPARE0
*   @brief Alias name for RTI compare 0 notification
*
*   This is an alias name for the RTI compare 0 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE0 1U

/** @def rtiNOTIFICATION_COMPARE1
*   @brief Alias name for RTI compare 1 notification
*
*   This is an alias name for the RTI compare 1 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE1 2U

/** @def rtiNOTIFICATION_COMPARE2
*   @brief Alias name for RTI compare 2 notification
*
*   This is an alias name for the RTI compare 2 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE2 4U

/** @def rtiNOTIFICATION_COMPARE3
*   @brief Alias name for RTI compare 3 notification
*
*   This is an alias name for the RTI compare 3 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE3 8U

/** @def rtiNOTIFICATION_TIMEBASE
*   @brief Alias name for RTI timebase notification
*
*   This is an alias name for the RTI timebase notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_TIMEBASE 0x10000U

/** @def rtiNOTIFICATION_COUNTER0
*   @brief Alias name for RTI counter block 0 overflow notification
*
*   This is an alias name for the RTI counter block 0 overflow notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COUNTER0 0x20000U

/** @def rtiNOTIFICATION_COUNTER1
*   @brief Alias name for RTI counter block 1 overflow notification
*
*   This is an alias name for the RTI counter block 1 overflow notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COUNTER1 0x40000U

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @enum dwdViolationTag
*   @brief DWD Violations
*/
typedef enum dwdViolationTag
{
	NoTime_Violation = 0U,
	Time_Window_Violation = 1U,
	EndTime_Window_Violation = 2U,
	StartTime_Window_Violation = 3U,
	Key_Seq_Violation = 4U
}dwdViolation_t;

/* USER CODE BEGIN (2) */
/* USER CODE END */

/** @enum dwdResetStatusTag
*   @brief DWD Reset status
*/
typedef enum dwdResetStatusTag
{
	No_Reset_Generated = 0U,
	Reset_Generated    = 1U
}dwdResetStatus_t;

/* USER CODE BEGIN (3) */
/* USER CODE END */

/** @enum dwwdReactionTag
*   @brief DWWD Reaction on vioaltion
*/
typedef enum dwwdReactionTag
{
	Generate_Reset = 0x00000005U,
	Generate_NMI   = 0x0000000AU
}dwwdReaction_t;

/* USER CODE BEGIN (4) */
/* USER CODE END */

/** @enum dwwdWindowSizeTag
*   @brief DWWD Window size
*/
typedef enum dwwdWindowSizeTag
{
	Size_100_Percent   = 0x00000005U,
	Size_50_Percent    = 0x00000050U,
	Size_25_Percent    = 0x00000500U,
	Size_12_5_Percent  = 0x00005000U,
	Size_6_25_Percent  = 0x00050000U,
	Size_3_125_Percent = 0x00500000U
}dwwdWindowSize_t;

/* USER CODE BEGIN (5) */
/* USER CODE END */

/* Configuration registers */
typedef struct rti_config_reg
{
    uint32 CONFIG_GCTRL;
    uint32 CONFIG_TBCTRL;
    uint32 CONFIG_CAPCTRL;
    uint32 CONFIG_COMPCTRL;
    uint32 CONFIG_UDCP0;
    uint32 CONFIG_UDCP1;
    uint32 CONFIG_UDCP2;
    uint32 CONFIG_UDCP3;
} rti_config_reg_t;


/* Configuration registers initial value */
#define RTI_GCTRL_CONFIGVALUE	 ((uint32)((uint32)0x0U << 16U) | 0x00000000U)
#define RTI_TBCTRL_CONFIGVALUE   0x00000000U
#define RTI_CAPCTRL_CONFIGVALUE  (0U | 0U)
#define RTI_COMPCTRL_CONFIGVALUE (0x00001000U | 0x00000100U | 0x00000000U | 0x00000000U)
#define RTI_UDCP0_CONFIGVALUE    10000U
#define RTI_UDCP1_CONFIGVALUE    50000U
#define RTI_UDCP2_CONFIGVALUE    80000U
#define RTI_UDCP3_CONFIGVALUE    100000U


/** 
 *  @defgroup RTI RTI
 *  @brief Real Time Interrupt Module.
 *  
 *  The real-time interrupt (RTI) module provides timer functionality for operating systems and for
 *  benchmarking code. The RTI module can incorporate several counters that define the timebases needed
 *  for scheduling in the operating system.
 *
 *	Related Files
 *   - reg_rti.h
 *   - rti.h
 *   - rti.c
 *  @addtogroup RTI
 *  @{
 */
 
/* RTI Interface Functions */

void rtiInit(void);
void rtiStartCounter(uint32 counter);
void rtiStopCounter(uint32 counter);
uint32 rtiResetCounter(uint32 counter);
void rtiSetPeriod(uint32 compare, uint32 period);
uint32 rtiGetPeriod(uint32 compare);
uint32 rtiGetCurrentTick(uint32 compare);
void rtiEnableNotification(uint32 notification);
void rtiDisableNotification(uint32 notification);
void dwdInit(uint16 dwdPreload);
void dwwdInit(dwwdReaction_t Reaction, uint16 dwdPreload, dwwdWindowSize_t Window_Size);
uint32 dwwdGetCurrentDownCounter(void);
void dwdCounterEnable(void);
void dwdSetPreload(uint16 dwdPreload);
void dwdReset(void);
void dwdGenerateSysReset(void);
boolean IsdwdKeySequenceCorrect(void);
dwdResetStatus_t dwdGetStatus(void);
dwdViolation_t dwdGetViolationStatus(void);
void dwdClearFlag(void);
void rtiGetConfigValue(rti_config_reg_t *config_reg, config_value_type_t type);
/** @fn void rtiNotification(uint32 notification)
*   @brief Notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   @note This function has to be provide by the user.
*/
void rtiNotification(uint32 notification);

/* USER CODE BEGIN (6) */
/* USER CODE END */

/**@}*/
#ifdef __cplusplus
}
#endif /*extern "C" */

#endif
