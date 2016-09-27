/*
 * rf6886.c
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
 * \file rf6886.c
 * 
 * \brief RF6889TR7 functions implementation
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \addtogroup rf6886
 * \{
 */

#include "../inc/rf6886.h"
#include "../driverlib/driverlib.h"

#if DEBUG_MODE == true
#include "../inc/debug.h"
#endif // DEBUG_MODE

uint8_t rf6886_Init()
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf6886_Init()");
#endif // DEBUG_MODE
    DAC12_A_initParam dac_params = {0};
    
    dac_params.submoduleSelect          = DAC12_A_SUBMODULE_0;
    dac_params.outputSelect             = DAC12_A_OUTPUT_1;
    dac_params.positiveReferenceVoltage = DAC12_A_VREF_AVCC;
    dac_params.outputVoltageMultiplier  = DAC12_A_VREFx1;
    dac_params.amplifierSetting         = DAC12_A_AMP_OFF_PINOUTHIGHZ;
    dac_params.conversionTriggerSelect  = DAC12_A_TRIGGER_ENC;
    
    if (DAC12_A_init(DAC12_A_BASE, &dac_params) == STATUS_FAIL)
    {
#if DEBUG_MODE == true
        debug_PrintMsg("\tFAIL!");
#endif // DEBUG_MODE

        return STATUS_FAIL;
    }
    else
    {
        // Calibrate output buffer for DAC12_A_0
        DAC12_A_calibrateOutput(DAC12_A_BASE, DAC12_A_SUBMODULE_0);
        
#if DEBUG_MODE == true
        debug_PrintMsg("\tSUCCESS!");
#endif // DEBUG_MODE

        return STATUS_SUCCESS;
    }
}

void rf6886_Enable()
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf6886_Enable()");
#endif // DEBUG_MODE

    DAC12_A_enableConversions(DAC12_A_BASE, DAC12_A_SUBMODULE_0);

#if DEBUG_MODE == true
    debug_PrintMsg("End of rf6886_Enable()\n");
#endif // DEBUG_MODE
}

void rf6886_Disable()
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf6886_Disable()");
#endif // DEBUG_MODE

    DAC12_A_disable(DAC12_A_BASE, DAC12_A_SUBMODULE_0);
    
#if DEBUG_MODE == true
    debug_PrintMsg("End of rf6886_Disable()\n");
#endif // DEBUG_MODE
}

void rf6886_SetVreg(uint8_t v_reg)
{
#if DEBUG_MODE == true
    debug_PrintMsg("rf6886_Init()");
    debug_PrintByte("\t v_reg = ", v_reg);
#endif // DEBUG_MODE

    v_reg /= 10;
    // 12 bits = 0xFFF
    // V_REF = 0xFFF
    // v_reg = data
    // data  = gain*0xFFF/V_ref
    DAC12_A_setData(DAC12_A_BASE, DAC12_A_SUBMODULE_0, (uint16_t)(v_reg*0xFFF/V_REF));

#if DEBUG_MODE == true
    debug_PrintMsg("End of rf6886_SetVreg()\n");
#endif // DEBUG_MODE
}

//! \} End of rf6886 implementation group
