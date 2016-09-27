/*
 * cc11xx.h
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
 * \file cc11xx.h
 * 
 * \brief CC1125/CC1175 control functions
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \defgroup cc1175 CC1175
 * \ingroup beacon
 * \{
 */

#ifndef CC11XX_H_
#define CC11XX_H_

#include <stdint.h>

/**
 * \defgroup pins CC1175 pins
 * \ingroup cc1175
 * 
 * \brief MCU pins on CC1175
 * 
 * \{
 */
/**
 * \brief GPIO pins
 * 
 * P1.3 = Reset beacon (RESETn_TRANS)
 * 
 */
#define CC11XX_RESET_PORT       GPIO_PORT_P1
#define CC11XX_RESET_PIN        GPIO_PIN3

/**
 * \brief SPI pins
 * 
 *      - P2.0 = CSn  (SPI0_BEACON_CSn),
 *      - P2.1 = MOSI (SPI0_BEACON_MOSI),
 *      - P2.2 = MISO (SPI0_BEACON_MISO),
 *      - P2.3 = SCLK (SPI0_BEACON_SCLK)
 *      .
 */
#define CC11XX_SPI_PORT         GPIO_PORT_P2
#define CC11XX_CSN_PORT         GPIO_PORT_P2
#define CC11XX_CSN_PIN          GPIO_PIN0
#define CC11XX_MOSI_PORT        GPIO_PORT_P2
#define CC11XX_MOSI_PIN         GPIO_PIN1
#define CC11XX_MISO_PORT        GPIO_PORT_P2
#define CC11XX_MISO_PIN         GPIO_PIN2
#define CC11XX_SCLK_PORT        GPIO_PORT_P2
#define CC11XX_SCLK_PIN         GPIO_PIN3
//! \} End of pins

/**
 * \defgroup adr_space CC1175 SPI Address Space
 * \ingroup cc1175
 * 
 * \brief Addresses of CC1175 SPI Address Space
 * 
 * Reference: CC112X/CC1175 User's Guide Table 4
 * 
 * \{
 */
#define CC11XX_IOCFG3           0x0000      /**< GPIO3 IO Pin Configuration */
#define CC11XX_IOCFG2           0x0001      /**< GPIO2 IO Pin Configuration */ 
#define CC11XX_IOCFG1           0x0002      /**< GPIO1 IO Pin Configuration */
#define CC11XX_IOCFG0           0x0003      /**< GPIO0 IO Pin Configuration */
#define CC11XX_SYNC3            0x0004
#define CC11XX_SYNC2            0x0005
#define CC11XX_SYNC1            0x0006
#define CC11XX_SYNC0            0x0007
#define CC11XX_SYNC_CFG1        0x0008      /**< Sync Word Detection Configuration Reg. 1 */
#define CC11XX_SYNC_CFG0        0x0009
#define CC11XX_DEVIATION_M      0x000A
#define CC11XX_MODCFG_DEV_E     0x000B      /**< Modulation Format and Frequency Deviation Configuration */
#define CC11XX_DCFILT_CFG       0x000C      /**< Digital DC Removal Configuration */
#define CC11XX_PREAMBLE_CFG1    0x000D
#define CC11XX_PREAMBLE_CFG0    0x000E
#define CC11XX_FREQ_IF_CFG      0x000F
#define CC11XX_IQIC             0x0010      /**< Digital Image Channel Compensation Configuration */
#define CC11XX_CHAN_BW          0x0011      /**< Channel Filter Configuration */
#define CC11XX_MDMCFG1          0x0012      /**< General Modem Parameter Configuration Reg. 1 */
#define CC11XX_MDMCFG0          0x0013      /**< General Modem Parameter Configuration Reg. 0 */
#define CC11XX_SYMBOL_RATE2     0x0014
#define CC11XX_SYMBOL_RATE1     0x0015
#define CC11XX_SYMBOL_RATE0     0x0016
#define CC11XX_AGC_REF          0x0017      /**< AGC Reference Level Configuration */
#define CC11XX_AGC_CS_THR       0x0018      /**< Carrier Sense Threshold Configuration */
#define CC11XX_AGC_GAIN_ADJUST  0x0019
#define CC11XX_AGC_CFG3         0x001A      /**< Automatic Gain Control Configuration Reg. 3 */
#define CC11XX_AGC_CFG2         0x001B      /**< Automatic Gain Control Configuration Reg. 2 */
#define CC11XX_AGC_CFG1         0x001C      /**< Automatic Gain Control Configuration Reg. 1 */
#define CC11XX_AGC_CFG0         0x001D      /**< Automatic Gain Control Configuration Reg. 0 */
#define CC11XX_FIFO_CFG         0x001E      /**< FIFO Configuration */
#define CC11XX_DEV_ADDR         0x001F
#define CC11XX_SETTLING_CFG     0x0020      /**< Frequency Synthesizer Calibration and Setting Configuration */
#define CC11XX_FS_CFG           0x0021      /**< Frequency Synthesizer Configuration */
#define CC11XX_WOR_CFG1         0x0022
#define CC11XX_WOR_CFG0         0x0023
#define CC11XX_WOR_EVENT0_MSB   0x0024
#define CC11XX_WOR_EVENT0_LSB   0x0025
#define CC11XX_PKT_CFG2         0x0026      /**< Packet Configuration Reg. 2 */
#define CC11XX_PKT_CFG1         0x0027      /**< Packet Configuration Reg. 1 */
#define CC11XX_PKT_CFG0         0x0028      /**< Packet Configuration Reg. 0 */
#define CC11XX_RFEND_CFG1       0x0029
#define CC11XX_RFEND_CFG0       0x002A
#define CC11XX_PA_CFG2          0x002B      //!< Power Amplifier Configuration Reg. 2 */
#define CC11XX_PA_CFG1          0x002C      //!< Power Amplifier Configuration Reg. 1 */
#define CC11XX_PA_CFG0          0x002D      //!< Power Amplifier Configuration Reg. 0 */
#define CC11XX_PKT_LEN          0x002E      //!< Packet Length Configuration */
//! \} End of adr_space

/**
 * \defgroup ext_reg CC1175 Extended Register Space Mapping
 * \ingroup cc1175
 * 
 * \brief Addresses of CC1175 Extended Register Space Mapping
 * 
 * Reference: CC112X/CC1175 User's Guide Table 5
 * 
 * \{
 */
#define CC11XX_IF_MIX_CFG       0x2F00      /**< IF Mix Configuration */
#define CC11XX_FREQOFF_CFG      0x2F01      /**< Frequency Offset Correction Configuration */
#define CC11XX_TOC_CFG          0x2F02
#define CC11XX_MARC_SPARE       0x2F03
#define CC11XX_ECG_CFG          0x2F04
#define CC11XX_CFM_DATA_CFG     0x2F05
#define CC11XX_EXT_CTRL         0x2F06
#define CC11XX_RCCAL_FINE       0x2F07
#define CC11XX_RCCAL_COARSE     0x2F08
#define CC11XX_RCCAL_OFFSET     0x2F09
#define CC11XX_FREQOFF1         0x2F0A
#define CC11XX_FREQOFF0         0x2F0B
#define CC11XX_FREQ2            0x2F0C      /**< Frequency Configuration [23:16] */
#define CC11XX_FREQ1            0x2F0D      /**< Frequency Configuration [15:8] */
#define CC11XX_FREQ0            0x2F0E
#define CC11XX_IF_ADC2          0x2F0F
#define CC11XX_IF_ADC1          0x2F10
#define CC11XX_IF_ADC0          0x2F11
#define CC11XX_FS_DIG1          0x2F12      /**< Frequency Synthesizer Digital Reg. 1 */
#define CC11XX_FS_DIG0          0x2F13      /**< Frequency Synthesizer Digital Reg. 0 */
#define CC11XX_FS_CAL3          0x2F14
#define CC11XX_FS_CAL2          0x2F15
#define CC11XX_FS_CAL1          0x2F16
#define CC11XX_FS_CAL0          0x2F17      /**< Frequency Synthesizer Calibration Reg. 0 */
#define CC11XX_FS_CHP           0x2F18
#define CC11XX_FS_DIVTWO        0x2F19      /**< Frequency Synthesizer Divide by 2 */
#define CC11XX_FS_DSM1          0x2F1A
#define CC11XX_FS_DSM0          0x2F1B      /**< FS Digital Synthesizer Module Configuration Reg. 0 */
#define CC11XX_FS_DVC1          0x2F1C
#define CC11XX_FS_DVC0          0x2F1D      /**< Frequency Synthesizer Divider Chain Configuration .. */
#define CC11XX_FS_LBI           0x2F1E
#define CC11XX_FS_PFD           0x2F1F      /**< Frequency Synthesizer Phase Frequency Detector Con.. */
#define CC11XX_FS_PRE           0x2F20      /**< Frequency Synthesizer Prescaler Configuration */
#define CC11XX_FS_REG_DIV_CML   0x2F21      /**< Frequency Synthesizer Divider Regulator Configurat.. */
#define CC11XX_FS_SPARE         0x2F22      /**< Frequency Synthesizer Spare */
#define CC11XX_FS_VCO4          0x2F23
#define CC11XX_FS_VCO3          0x2F24
#define CC11XX_FS_VCO2          0x2F25
#define CC11XX_FS_VCO1          0x2F26
#define CC11XX_FS_VCO0          0x2F27
#define CC11XX_GBIAS6           0x2F28
#define CC11XX_GBIAS5           0x2F29
#define CC11XX_GBIAS4           0x2F2A
#define CC11XX_GBIAS3           0x2F2B
#define CC11XX_GBIAS2           0x2F2C
#define CC11XX_GBIAS1           0x2F2D
#define CC11XX_GBIAS0           0x2F2E
#define CC11XX_IFAMP            0x2F2F
#define CC11XX_LNA              0x2F30
#define CC11XX_RXMIX            0x2F31
#define CC11XX_XOSC5            0x2F32      /**< Crystal Oscillator Configuration Reg. 5 */
#define CC11XX_XOSC4            0x2F33
#define CC11XX_XOSC3            0x2F34      /**< Crystal Oscillator Configuration Reg. 3 */
#define CC11XX_XOSC2            0x2F35
#define CC11XX_XOSC1            0x2F36      /**< Crystal Oscillator Configuration Reg. 1 */
#define CC11XX_XOSC0            0x2F37
#define CC11XX_ANALOG_SPARE     0x2F38
#define CC11XX_PA_CFG3          0x2F39
// 0x2F3A - 0x2F3E = Not used
// 0x2F3F - 0x2F40 = Reserved
// 0x2F41 - 0x2F63 = Not used
#define CC11XX_WOR_TIME1        0x2F64
#define CC11XX_WOR_TIME0        0x2F65
#define CC11XX_WOR_CAPTURE1     0x2F66
#define CC11XX_WOR_CAPTURE0     0x2F67
#define CC11XX_BIST             0x2F68
#define CC11XX_DCFILTOFFSET_I1  0x2F69
#define CC11XX_DCFILTOFFSET_I0  0x2F6A
#define CC11XX_DCFILTOFFSET_Q1  0x2F6B
#define CC11XX_DCFILTOFFSET_Q0  0x2F6C
#define CC11XX_IQIE_I1          0x2F6D
#define CC11XX_IQIE_I0          0x2F6E
#define CC11XX_IQIE_Q1          0x2F6F
#define CC11XX_IQIE_Q0          0x2F70
#define CC11XX_RSSI1            0x2F71
#define CC11XX_RSSI0            0x2F72
#define CC11XX_MARCSTATE        0x2F73
#define CC11XX_LQI_VAL          0x2F74
#define CC11XX_PQT_SYNC_ERR     0x2F75
#define CC11XX_DEM_STATUS       0x2F76
#define CC11XX_FREQOFF_EST1     0x2F77
#define CC11XX_FREQOFF_EST0     0x2F78
#define CC11XX_AGC_GAIN3        0x2F79
#define CC11XX_AGC_GAIN2        0x2F7A
#define CC11XX_AGC_GAIN1        0x2F7B
#define CC11XX_AGC_GAIN0        0x2F7C
#define CC11XX_CFM_RX_DATA_OUT  0x2F7D
#define CC11XX_CFM_TX_DATA_IN   0x2F7E
#define CC11XX_ASK_SOFT_RX_DATA 0x2F7F
#define CC11XX_RNDGEN           0x2F80
#define CC11XX_MAGN2            0x2F81
#define CC11XX_MAGN1            0x2F82
#define CC11XX_MAGN0            0x2F83
#define CC11XX_ANG1             0x2F84
#define CC11XX_ANG0             0x2F85
#define CC11XX_CHFILT_I2        0x2F86
#define CC11XX_CHFILT_I1        0x2F87
#define CC11XX_CHFILT_I0        0x2F88
#define CC11XX_CHFILT_Q2        0x2F89
#define CC11XX_CHFILT_Q1        0x2F8A
#define CC11XX_CHFILT_Q0        0x2F8B
#define CC11XX_GPIO_STATUS      0x2F8C
#define CC11XX_FSCAL_CTRL       0x2F8D
#define CC11XX_PHASE_ADJUST     0x2F8E
#define CC11XX_PARTNUMBER       0x2F8F
#define CC11XX_PARTVERSION      0x2F90
#define CC11XX_SERIAL_STATUS    0x2F91
#define CC11XX_MODEM_STATUS1    0x2F92
#define CC11XX_MODEM_STATUS0    0x2F93
#define CC11XX_MARC_STATUS1     0x2F94
#define CC11XX_MARC_STATUS0     0x2F95
#define CC11XX_PA_IFAMP_TEST    0x2F96
#define CC11XX_FSRF_TEST        0x2F97
#define CC11XX_PRE_TEST         0x2F98
#define CC11XX_PRE_OVR          0x2F99
#define CC11XX_ADC_TEST         0x2F9A
#define CC11XX_DVC_TEST         0x2F9B
#define CC11XX_ATEST            0x2F9C
#define CC11XX_ATEST_LVDS       0x2F9D
#define CC11XX_ATEST_MODE       0x2F9E
#define CC11XX_XOSC_TEST1       0x2F9F
#define CC11XX_XOSC_TEST0       0x2FA0
// 0x2FA1 - 0x2FD1 = Not used
#define CC11XX_RXFIRST          0x2FD2
#define CC11XX_TXFIRST          0x2FD3
#define CC11XX_RXLAST           0x2FD4
#define CC11XX_TXLAST           0x2FD5
#define CC11XX_NUM_TXBYTES      0x2FD6
#define CC11XX_NUM_RXBYTES      0x2FD7
#define CC11XX_FIFO_NUM_TXBYTES 0x2FD8
#define CC11XX_FIFO_NUM_RXBYTES 0x2FD9
//! \} End of ext_reg

/**
 * \defgroup cmd_strobe CC1175 Command Strobes
 * \ingroup cc1175
 * 
 * \brief CC1175 command strobes values
 * 
 * Reference: CC112x/CC1175 User's Guide Table 6
 * 
 * \{
 */
#define CC11XX_SRES             0x30        /**< Reset chip */
#define CC11XX_SFSTXON          0x31        /**< Enable and calibrate frequency synthesizer (if SETTLING_CFG.FS_AUTOCAL = 1). If in RX and PKT_CFG2.CCA_MODE ≠ 0: Go to a wait state where only the synthesizer is running (for quick RX/TX turnaround). */
#define CC11XX_SXOFF            0x32        /**< Enter XOFF state when CSn is de-asserted */
#define CC11XX_SCAL             0x33        /**< Calibrate frequency synthesizer and turn it off. SCAL can be strobed from IDLE mode without setting manual calibration mode (SETTLING_CFG.FS_AUTOCAL = 0) */
#define CC11XX_SRX              0x34        /**< Enable RX. Perform calibration first if coming from IDLE and SETTLING_CFG.FS_AUTOCAL = 1 */
#define CC11XX_STX              0x35        /**< In IDLE state: Enable TX. Perform calibration first if SETTLING_CFG.FS_AUTOCAL = 1. If in RX state and PKT_CFG2.CCA_MODE ≠ 0: Only go to TX if channel is clear */
#define CC11XX_SIDLE            0x36        /**< Exit RX/TX, turn off frequency synthesizer and exit eWOR mode if applicable */
#define CC11XX_SAFC             0x37        /**< Automatic Frequency Compensation */
#define CC11XX_SWOR             0x38        /**< Start automatic RX polling sequence (eWOR) if WOR_CFGO.RC_PD = 0 */
#define CC11XX_SPWD             0x39        /**< Enter SLEEP mode when CSn is de-asserted */
#define CC11XX_SFRX             0x3A        /**< Flush the RX FIFO. Only issue SFRX in IDLE or RX_FIFO_ERR states */
#define CC11XX_SFTX             0x3B        /**< Flush the TX FIFO. Only issue SFTX in IDLE or TX_FIFO_ERR states */
#define CC11XX_SWORRST          0x3C        /**< Reset the eWOR timer to the Event1 value */
#define CC11XX_SNOP             0x3D        /**< No operation. May be used to get access to the chip status byte */
//! \} End of cmd_strobe

#define CC11XX_DIRECT_MEMORY_ACCESS 0x3F

/**
 * \defgroup fifo_acs CC1175 FIFO access
 * \ingroup cc1175
 * 
 * \brief FIFO access addresses
 * 
 * Referemce: CC112x/CC1175 User's Guide Table 4
 * 
 * \{
 */
#define CC11XX_SINGLE_TXFIFO    0x003F      /**< Single access to Transmit FIFO (0x3F + 0x00 = 0x003F) */
#define CC11XX_BURST_TXFIFO     0x007F      /**< Burst access to Transmit FIFO  (0x3F + 0x40 = 0x007F) */
#define CC11XX_SINGLE_RXFIFO    0x00BF      /**< Single access to Receive FIFO  (0x3F + 0x80 = 0x00BF) */
#define CC11XX_BURST_RXFIFO     0x00FF      /**< Burst access to Receive FIFO   (0x3F + 0xC0 = 0x00FF) */
//! \} End of fifo_acs

/**
 * \defgroup acs_modes CC1175 Access Modes
 * \ingroup cc1175
 * 
 * \brief CC1175 access modes values
 * 
 * Reference: CC112x/CC1175 User's Guide Table 3
 * 
 * \{
 */
#define CC11XX_BURST_ACCESS     0x40        /**< [R/W 1 A5 A4 A3 A2 A1 A0] = 0100 0000 = 0x40 */
#define CC11XX_SINGLE_ACCESS    0x00        /**< [R/W 0 A5 A4 A3 A2 A1 A0] = 0000 0000 = 0x00 */
#define CC11XX_READ_ACCESS      0x80        /**< [1 B/S A5 A4 A3 A2 A1 A0] = 1000 0000 = 0x80 */
#define CC11XX_WRITE_ACCESS     0x00        /**< [0 B/S A5 A4 A3 A2 A1 A0] = 0000 0000 = 0x00 */
//! \} End of acs_modes

/**
 * \defgroup status_byte CC1175 Status Byte
 * \ingroup cc1175
 * 
 * \brief CC1175 Status Byte possible values
 * 
 * Basic structure:
 *      - STATUS_CHIP_RDYn = bit  7
 *      - STATE            = bits 6:4
 *      - Reserved         = bits 3:0
 *      .
 * 
 * Reference: CC112x/CC1175 User's Guide Table 2
 * 
 * \{
 */
#define CC11XX_STATUS_CHIP_RDYn_L   0x00    /**< Should always be low when using the SPI interface */
#define CC11XX_STATUS_CHIP_RDYn_H   0x80    /**< Stays high until power and crystal have stabilized */
#define CC11XX_STATE_IDLE           0x00    /**< Idle state */
#define CC11XX_STATE_RX             0x10    /**< Receive mode */
#define CC11XX_STATE_TX             0x20    /**< Transmit mode */
#define CC11XX_STATE_FSTXON         0x30    /**< Fast TX ready */
#define CC11XX_STATE_CALIBRATE      0x40    /**< Frequency synthesizer callibration is running */
#define CC11XX_STATE_SETTLING       0x50    /**< PLL is settling */
#define CC11XX_STATE_RX_FIFO_ERROR  0x60    /**< RX FIFO has over/underflowed. Read out any useful data, then flush the FIFO with an SFRX strobe */
#define CC11XX_STATE_TX_FIFO_ERROR  0x70    /**< TX FIFO has over/underflowed. Flush the FIFO with an SFTX strobe */
//! \} End of status_byte

/**
 * \defgroup cal_macros Calibration macros
 * \ingroup cc1175
 * 
 * \brief Calibration const.
 * 
 * Reference: CC112X, CC1175 Silicon Errata
 * 
 * \{
 */
#define CC11XX_VCDAC_START_OFFSET   2
#define CC11XX_FS_VCO2_INDEX        0
#define CC11XX_FS_VCO4_INDEX        1
#define CC11XX_FS_CHP_INDEX         2
//! \} End of cal_macros

/**
 * \fn cc11xx_Init
 * 
 * \brief cc11xx initialization
 * 
 * \return None
 */
void cc11xx_Init();

/**
 * \fn cc11xx_registerConfig
 * 
 * \brief cc11xx initialization
 * 
 * This function 
 * 
 * Operation sequence:
 *      -# Reset chip
 *      -# Registers configuration
 *      .
 * 
 * \return None
 */
void cc11xx_RegConfig();

/**
 * \fn cc11xx_WriteRef
 * 
 * \brief 
 * 
 * \param addr
 * \param pData
 * \param len
 * 
 * \return Chip status
 */
uint8_t cc11xx_WriteReg(uint16_t addr, uint8_t *pData, uint8_t len);

/**
 * \fn cc11xx_ReadRef
 * 
 * \brief 
 * 
 * \param addr
 * \param pData
 * \param len
 * 
 * \return Chip status
 */
uint8_t cc11xx_ReadReg(uint16_t addr, uint8_t *pData, uint8_t len);

/**
 * \fn cc11xx_CmdStrobe
 * 
 * \brief 
 * 
 * \param cmd
 * 
 * \return 
 */
uint8_t cc11xx_CmdStrobe(uint8_t cmd);

/**
 * \fn cc11xx_8BitRegAccess
 * 
 * \brief This function performs a read or write from/to a 8bit register
 *        address space. The function handles burst and single read/write
 *        as specfied in addrByte. Function assumes that chip is ready.
 * 
 * \param access_type Specifies if this is a read or write and if it's a
 *                    single or burst access. Bitmask made up of
 *                    RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                    RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * \param addr_byte address byte of register
 * \param pData data array
 * \param len length of array to be read (TX)/written (RX)
 * 
 * \return Chip status
 */
uint8_t cc11xx_8BitRegAccess(uint8_t access_type, uint8_t addr_byte, uint8_t *pData, uint16_t len);

/**
 * \fn cc11xx_16BitRegAccess
 * 
 * \brief
 * \param access_type
 * \param ext_addr
 * \param red_addr
 * \param pData
 * \param len
 * 
 * \return Chip status
 */
uint8_t cc11xx_16BitRegAccess(uint8_t access_type, uint8_t ext_addr, uint8_t reg_addr, uint8_t *pData, uint8_t len);

/**
 * \fn cc11xx_ReadWriteBurstSingle
 * 
 * \brief 
 * 
 * \param addr
 * \param pData
 * \param len
 *
 * \return None
 */
void cc11xx_ReadWriteBurstSingle(uint8_t addr, uint8_t *pData, uint16_t len);

/**
 * \fn cc11xx_ManualReset
 * 
 * \brief Reset by using RESETn pin (active-low)
 * 
 * \return None
 */
void cc11xx_ManualReset();

/**
 * \fn cc11xx_SRESReset
 * 
 * \brief Reset by using the SRES command strobe
 * 
 * \return None
 */
void cc11xx_SRESReset();

/**
 * \fn cc11xx_ManualCalibration()
 * 
 * \brief Chip calibration
 * 
 * See "CC112X, CC1175 Silicon Errata".
 * 
 * \return None
 */
void cc11xx_ManualCalibration();

/**
 * \fn cc11xx_WriteTXFIFO()
 * 
 * \brief 
 * 
 * \return Chip status
 */
uint8_t cc11xx_WriteTXFIFO(uint8_t *pData, uint8_t len);

#endif // CC11XX_H_

//! \} End of CC1175 group
