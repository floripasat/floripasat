/*
 * cc11xx.c
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
 * \file cc11xx.c
 * 
 * \brief cc1125/cc1175 functions implementation
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 *
 * \addtogroup cc1175
 * \{
 */

#include "../inc/cc11xx.h"
#include "../inc/cc11xx_floripasat_reg_config.h"
#include "../driverlib/driverlib.h"

#if DEBUG_MODE == true
#include "../inc/debug.h"
#endif // DEBUG_MODE

void cc11xx_Init()
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_Init()");
#endif // DEBUG_MODE

    // Reset pin init.
	GPIO_setAsOutputPin(CC11XX_RESET_PORT, CC11XX_RESET_PIN);
    
    /*
    // P1.6 = CC1175 GPIO0
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6);
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6);
    
    // P1.5 = CC1175 GPIO2
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);
    
    // P1.7 = CC1175 GPIO3
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
    */
    
    cc11xx_ManualReset();
    
    cc11xx_RegConfig();
    
#if DEBUG_MODE == true
    debug_PrintMsg("End of cc11xx_Init()\n");
#endif // DEBUG_MODE
}

void cc11xx_RegConfig()
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_RegConfig()");
#endif // DEBUG_MODE

    uint16_t i;
    uint8_t write_byte;

    // Write registers settings to radio (Values in "cc11xx_floripasat_reg_config.h")
    for(i=0; i<(sizeof(reg_values)/sizeof(RegistersSettings)); i++)
    {
        write_byte = reg_values[i].data;
        cc11xx_WriteReg(reg_values[i].addr, &write_byte, sizeof(reg_values[i].data));
    }

#if DEBUG_MODE == true
    debug_PrintMsg("End of cc11xx_RegConfig()\n");
#endif // DEBUG_MODE
}

uint8_t cc11xx_WriteReg(uint16_t addr, uint8_t *pData, uint8_t len)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_WriteReg()");
    debug_PrintByte("\taddr = ", addr);
    debug_PrintByte("\tpData = ", *pData);
    debug_PrintByte("\tlen = ", len);
#endif // DEBUG_MODE

    uint8_t temp_ext  = (uint8_t)(addr >> 8);
    uint8_t temp_addr = (uint8_t)(addr & 0x00FF);
    uint8_t chip_status = 0;

    // Checking if this is a FIFO access (if true, returns chip not ready)
    if ((CC11XX_SINGLE_TXFIFO <= temp_addr) && (temp_ext == 0))
    {
#if DEBUG_MODE == true
    debug_PrintMsg("> CC11XX_STATUS_CHIP_RDYn_H!");
#endif // DEBUG_MODE

        return CC11XX_STATUS_CHIP_RDYn_H;
    }

    // Decide what register space is accessed
    if (!temp_ext)
    {
        chip_status = cc11xx_8BitRegAccess((CC11XX_BURST_ACCESS | CC11XX_WRITE_ACCESS), temp_addr, pData, len);
    }
    else if (temp_ext == 0x2F)  // Extended addresses space
    {
        chip_status = cc11xx_16BitRegAccess((CC11XX_BURST_ACCESS | CC11XX_WRITE_ACCESS), temp_ext, temp_addr, pData, len);
    }

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", chip_status);
    debug_PrintMsg("End of cc11xx_WriteReg()\n");
#endif // DEBUG_MODE

    return chip_status;
}

uint8_t cc11xx_ReadReg(uint16_t addr, uint8_t *pData, uint8_t len)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_ReadReg()");
    debug_PrintByte("\taddr = ", addr);
    debug_PrintByte("\tpData = ", *pData);
    debug_PrintByte("\tlen = ", len);
#endif // DEBUG_MODE

    uint8_t temp_ext  = (uint8_t)(addr >> 8);
    uint8_t temp_addr = (uint8_t)(addr & 0x00FF);
    uint8_t chip_status = 0;

    // Checking if this is a FIFO access (if true, returns chip not ready)
    if ((CC11XX_SINGLE_TXFIFO <= temp_addr) && (temp_ext == 0))
    {
#if DEBUG_MODE == true
    debug_PrintMsg("> CC11XX_STATUS_CHIP_RDYn_H!");
#endif // DEBUG_MODE
        
        return CC11XX_STATUS_CHIP_RDYn_H;
    }

    // Decide what register space is accessed
    if (!temp_ext)
    {
        chip_status = cc11xx_8BitRegAccess((CC11XX_BURST_ACCESS | CC11XX_READ_ACCESS), temp_addr, pData, len);
    }
    else if (temp_ext == 0x2F)  // Extended addresses space
    {
        chip_status = cc11xx_16BitRegAccess((CC11XX_BURST_ACCESS | CC11XX_READ_ACCESS), temp_ext, temp_addr, pData, len);
    }

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", chip_status);
    debug_PrintMsg("End of cc11xx_ReadReg()\n");
#endif // DEBUG_MODE

    return chip_status;
}

uint8_t cc11xx_CmdStrobe(uint8_t cmd)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_CmdStrobe()");
    debug_PrintByte("\tcmd = ", cmd);
#endif // DEBUG_MODE

    uint8_t chip_status;

    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);   // P2.0 = CSn = 0

    while(GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN2) == GPIO_INPUT_PIN_HIGH)
    {
        
    }

    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_B_SPI_transmitData(USCI_B0_BASE, cmd);

#if DEBUG_MODE == true
    debug_PrintByte("Transmited command: ", cmd);
#endif // DEBUG_MODE

    // Wait until new data was written into RX buffer
    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
    {
        
    }

    chip_status = USCI_B_SPI_receiveData(USCI_B0_BASE);

    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);   // P2.0 = CSn = 1

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", chip_status);
    debug_PrintMsg("End of cc11xx_CmdStrobe()\n");
#endif // DEBUG_MODE

    return chip_status;
}

uint8_t cc11xx_8BitRegAccess(uint8_t access_type, uint8_t addr_byte, uint8_t *pData, uint16_t len)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_8BitRegAccess()");
    debug_PrintByte("\taccess_type = ", access_type);
    debug_PrintByte("\taddr_byte = ", addr_byte);
    debug_PrintByte("\tpData = ", *pData);
    debug_PrintByte("\tlen = ", len);
#endif // DEBUG_MODE

	uint8_t read_value = 0;
    uint8_t header_byte = access_type | addr_byte;

	// Pull CSn low
	GPIO_setOutputLowOnPin(CC11XX_CSN_PORT, CC11XX_CSN_PIN);
    
    // Wait for MISO (or SO) to go low before communication starts
    while(GPIO_getInputPinValue(CC11XX_MISO_PORT, CC11XX_MISO_PIN) == GPIO_INPUT_PIN_HIGH)
    {
        
    }

    // Send register address byte
    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_B_SPI_transmitData(USCI_B0_BASE, header_byte);

#if DEBUG_MODE == true
    debug_PrintByte("Transmited header byte: ", header_byte);
#endif // DEBUG_MOD

    // Wait until new data was written into RX buffer
    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
    {
        
    }

    // Storing chip status
	read_value = USCI_B_SPI_receiveData(USCI_B0_BASE);

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", read_value);
#endif // DEBUG_MODE
    
	cc11xx_ReadWriteBurstSingle(header_byte, pData, len);
	
    // CSn = high after transfers
    GPIO_setOutputHighOnPin(CC11XX_CSN_PORT, CC11XX_CSN_PIN);

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", read_value);
    debug_PrintMsg("End of cc11xx_8BitRegAccess()\n");
#endif // DEBUG_MODE

    // Return the status byte value
	return read_value;
}

void cc11xx_ReadWriteBurstSingle(uint8_t header, uint8_t *pData, uint16_t len)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_ReadWriteBurstSingle()");
    debug_PrintByte("\theader = ", header);
    debug_PrintByte("\tpData = ", *pData);
    debug_PrintByte("\tlen = ", len);
#endif // DEBUG_MODE

    uint16_t i;
    
    // Communicate len number of bytes: if RX - the procedure sends 0x00 to push bytes from slave
    if (header & CC11XX_READ_ACCESS)
    {
        if (header & CC11XX_BURST_ACCESS)
        {
            for(i=0; i<len; i++)
            {
                // ????????????????????????????????????????????????????????????????????????????????????
                // Possible to combining read and write as one access type ????????????????????????????
                // ????????????????????????????????????????????????????????????????????????????????????

                // Wait until new data was written into RX buffer
                while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
                {
                    
                }
                USCI_B_SPI_transmitData(USCI_B0_BASE, 0);   // ????????????????????????????????????????

#if DEBUG_MODE == true
                debug_PrintByte("Transmited data (Read cmd.): ", 0x00);
#endif // DEBUG_MODE
                
                // Wait until new data was written into RX buffer
                while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
                {
                    
                }

                *pData = USCI_B_SPI_receiveData(USCI_B0_BASE);  // Store pData from last pData RX

#if DEBUG_MODE == true
                debug_PrintByte("Received data (Reg. value): ", *pData);
#endif // DEBUG_MODE

                pData++;
            }
        }
        else    // CC11XX_SINGLE_ACCESS
        {
            USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
            USCI_B_SPI_transmitData(USCI_B0_BASE, 0);

#if DEBUG_MODE == true
            debug_PrintByte("Transmited data (Read cmd.): ", 0x00);
#endif // DEBUG_MODE

            // Wait until new data was written into RX buffer
            while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
            {
                
            }
            
            *pData = USCI_B_SPI_receiveData(USCI_B0_BASE);
            
#if DEBUG_MODE == true
            debug_PrintByte("Received data (Reg. value): ", *pData);
#endif // DEBUG_MODE
        }
    }
    else    // CC11XX_WRITE_ACCESS
    {
        if (header & CC11XX_BURST_ACCESS)
        {
            // Communicate len number of bytes: if TX - the procedure doesn't overwrite pData
            for(i=0; i<len; i++)
            {
                USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
                USCI_B_SPI_transmitData(USCI_B0_BASE, *pData);                

#if DEBUG_MODE == true
                debug_PrintByte("Transmited data (Reg. value): ", *pData);
#endif // DEBUG_MODE
                
                // Wait until new data was written into RX buffer
                while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
                {
                    
                }
                pData++;
            }
        }
        else    // CC11XX_SINGLE_ACCESS
        {
            USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
            USCI_B_SPI_transmitData(USCI_B0_BASE, *pData);

#if DEBUG_MODE == true
            debug_PrintByte("Transmited data (Reg. value): ", *pData);
#endif // DEBUG_MODE

            // Wait until new data was written into RX buffer
            while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
            {
                
            }
        }
    }

#if DEBUG_MODE == true
    debug_PrintMsg("End of cc11xx_ReadWriteBurstSingle()\n");
#endif // DEBUG_MODE
}

uint8_t cc11xx_16BitRegAccess(uint8_t access_type, uint8_t ext_addr, uint8_t reg_addr, uint8_t *pData, uint8_t len)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_16BitRegAccess()");
    debug_PrintByte("\taccess_type = ", access_type);
    debug_PrintByte("\text_addr = ", ext_addr);
    debug_PrintByte("\treg_addr = ", reg_addr);
    debug_PrintByte("\tpData = ", *pData);
    debug_PrintByte("\tlen = ", len);
#endif // DEBUG_MODE

    uint8_t read_value = 0;
    uint8_t header_byte = access_type | ext_addr;

    // Pull CSn low to start transfer
    GPIO_setOutputLowOnPin(CC11XX_CSN_PORT, CC11XX_CSN_PIN);
    
    // Wait for MISO (or SO) to go low before communication starts
    while(GPIO_getInputPinValue(CC11XX_MISO_PORT, CC11XX_MISO_PIN) == GPIO_INPUT_PIN_HIGH)
    {
        
    }
    
    // Send extended address byte with access type bits set
    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_B_SPI_transmitData(USCI_B0_BASE, header_byte);

#if DEBUG_MODE == true
    debug_PrintByte("Transmited data (Header byte): ", header_byte);
#endif // DEBUG_MODE

    // Wait until new data was written into RX buffer
    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
    {
        
    }
    
    // Storing chip status
    read_value = USCI_B_SPI_receiveData(USCI_B0_BASE);

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", read_value);
#endif // DEBUG_MODE
    
    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_B_SPI_transmitData(USCI_B0_BASE, reg_addr);

#if DEBUG_MODE == true
    debug_PrintByte("Reg. address: ", reg_addr);
#endif // DEBUG_MODE

    // Wait until new data was written into RX buffer
    while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT))
    {
        
    }
    
    // Communicate len number of bytes
    cc11xx_ReadWriteBurstSingle(header_byte, pData, len);
    
    // Pull CSn high after transfer
    GPIO_setOutputHighOnPin(CC11XX_CSN_PORT, CC11XX_CSN_PIN);

#if DEBUG_MODE == true
    debug_PrintByte("Chip status: ", read_value);
    debug_PrintMsg("End of cc11xx_16BitRegAccess()\n");
#endif // DEBUG_MODE

    // Return the status byte value
    return read_value;
}

void cc11xx_ManualReset()
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_ManualReset()");
#endif // DEBUG_MODE

    GPIO_setOutputLowOnPin(CC11XX_RESET_PORT, CC11XX_RESET_PIN);
    __delay_cycles(100);
    GPIO_setOutputHighOnPin(CC11XX_RESET_PORT, CC11XX_RESET_PIN);

#if DEBUG_MODE == true
    debug_PrintMsg("End of cc11xx_ManualReset()\n");
#endif // DEBUG_MODE
}

void cc11xx_SRESReset()
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_SRESReset()");
#endif // DEBUG_MODE

    cc11xx_CmdStrobe(CC11XX_SRES);

#if DEBUG_MODE == true
    debug_PrintMsg("End of cc11xx_SRESReset()\n");
#endif // DEBUG_MODE
}

void cc11xx_ManualCalibration()
{
    uint8_t original_fs_cal2;
    uint8_t calResults_for_vcdac_start_high[3];
    uint8_t calResults_for_vcdac_start_mid[3];
    uint8_t marcstate;
    uint8_t write_byte;

    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    write_byte = 0x00;
    cc11xx_WriteReg(CC11XX_FS_VCO2, &write_byte, 1);

    // 2) Start with high VCDAC (original VCDAC_START + 2):
    cc11xx_ReadReg(CC11XX_FS_CAL2, &original_fs_cal2, 1);
    write_byte = original_fs_cal2 + CC11XX_VCDAC_START_OFFSET;
    cc11xx_WriteReg(CC11XX_FS_CAL2, &write_byte, 1);

    // 3) Calibrate and wait for calibration to be done
    //   (radio back in IDLE state)
    cc11xx_CmdStrobe(CC11XX_SCAL);

    do					// <--------- fica nesse loop
    {
        cc11xx_ReadReg(CC11XX_MARCSTATE, &marcstate, 1);
    }
    while(marcstate != 0x41);

    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with
    //    high VCDAC_START value
    cc11xx_ReadReg(CC11XX_FS_VCO2, &calResults_for_vcdac_start_high[CC11XX_FS_VCO2_INDEX], 1);
    cc11xx_ReadReg(CC11XX_FS_VCO4, &calResults_for_vcdac_start_high[CC11XX_FS_VCO4_INDEX], 1);
    cc11xx_ReadReg(CC11XX_FS_CHP, &calResults_for_vcdac_start_high[CC11XX_FS_CHP_INDEX], 1);

    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    write_byte = 0x00;
    cc11xx_WriteReg(CC11XX_FS_VCO2, &write_byte, 1);

    // 6) Continue with mid VCDAC (original VCDAC_START):
    write_byte = original_fs_cal2;
    cc11xx_WriteReg(CC11XX_FS_CAL2, &write_byte, 1);

    // 7) Calibrate and wait for calibration to be done
    //   (radio back in IDLE state)
    cc11xx_CmdStrobe(CC11XX_SCAL);

    do
    {
        cc11xx_ReadReg(CC11XX_MARCSTATE, &marcstate, 1);
    }
    while(marcstate != 0x41);

    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained
    //    with mid VCDAC_START value
    cc11xx_ReadReg(CC11XX_FS_VCO2, &calResults_for_vcdac_start_mid[CC11XX_FS_VCO2_INDEX], 1);
    cc11xx_ReadReg(CC11XX_FS_VCO4, &calResults_for_vcdac_start_mid[CC11XX_FS_VCO4_INDEX], 1);
    cc11xx_ReadReg(CC11XX_FS_CHP, &calResults_for_vcdac_start_mid[CC11XX_FS_CHP_INDEX], 1);

    // 9) Write back highest FS_VCO2 and corresponding FS_VCO
    //    and FS_CHP result
    if (calResults_for_vcdac_start_high[CC11XX_FS_VCO2_INDEX] > calResults_for_vcdac_start_mid[CC11XX_FS_VCO2_INDEX])
    {
        write_byte = calResults_for_vcdac_start_high[CC11XX_FS_VCO2_INDEX];
        cc11xx_WriteReg(CC11XX_FS_VCO2, &write_byte, 1);
        write_byte = calResults_for_vcdac_start_high[CC11XX_FS_VCO4_INDEX];
        cc11xx_WriteReg(CC11XX_FS_VCO4, &write_byte, 1);
        write_byte = calResults_for_vcdac_start_high[CC11XX_FS_CHP_INDEX];
        cc11xx_WriteReg(CC11XX_FS_CHP, &write_byte, 1);
    }
    else
    {
        write_byte = calResults_for_vcdac_start_mid[CC11XX_FS_VCO2_INDEX];
        cc11xx_WriteReg(CC11XX_FS_VCO2, &write_byte, 1);
        write_byte = calResults_for_vcdac_start_mid[CC11XX_FS_VCO4_INDEX];
        cc11xx_WriteReg(CC11XX_FS_VCO4, &write_byte, 1);
        write_byte = calResults_for_vcdac_start_mid[CC11XX_FS_CHP_INDEX];
        cc11xx_WriteReg(CC11XX_FS_CHP, &write_byte, 1);
    }
}

uint8_t cc11xx_WriteTXFIFO(uint8_t *pData, uint8_t len)
{
#if DEBUG_MODE == true
    debug_PrintMsg("cc11xx_WriteTXFIFO()");
    debug_PrintByte("\tpData = ", *pData);
    debug_PrintByte("\tlen = ", len);
#endif // DEBUG_MODE

    uint8_t chip_status = cc11xx_8BitRegAccess(CC11XX_WRITE_ACCESS, CC11XX_BURST_TXFIFO, pData, len);

#if DEBUG_MODE == true
    debug_PrintMsg("End of cc11xx_WriteTXFIFO()\n");
#endif // DEBUG_MODE

    return chip_status;
}

//! \} End of CC1175 implementation group
