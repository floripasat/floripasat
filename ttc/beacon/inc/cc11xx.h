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
 * \brief Functions of the CC1125/CC1175.
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

#ifndef DEBUG_MODE
#define DEBUG_MODE true
#endif // DEBUG_MODE

/**
 * \defgroup pins CC1175 pins
 * \ingroup cc1175
 * 
 * \brief MCU pins on CC1175.
 * 
 * \{
 */
#define CC11XX_RESET_PORT       GPIO_PORT_P1    /**< Reset port = P1 */
#define CC11XX_RESET_PIN        GPIO_PIN3       /**< Reset pin = P1.3 */

#define CC11XX_SPI_PORT         GPIO_PORT_P2    /**< SPI port = P2 (all pins in the same port) */
#define CC11XX_CSN_PORT         GPIO_PORT_P2    /**< CSn port = P2*/
#define CC11XX_CSN_PIN          GPIO_PIN0       /**< CSn pin = P2.0 */
#define CC11XX_MOSI_PORT        GPIO_PORT_P2    /**< MOSI port = P2 */
#define CC11XX_MOSI_PIN         GPIO_PIN1       /**< MOSI pin = P2.1 */
#define CC11XX_MISO_PORT        GPIO_PORT_P2    /**< MISO port = P2 */
#define CC11XX_MISO_PIN         GPIO_PIN2       /**< MISO pin = P2.2 */
#define CC11XX_SCLK_PORT        GPIO_PORT_P2    /**< SCLK port = P2 */
#define CC11XX_SCLK_PIN         GPIO_PIN3       /**< SCLK pin = P2.3*/
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
#define CC11XX_SYNC3            0x0004      /**< Sync Word Configuration [31:24] */
#define CC11XX_SYNC2            0x0005      /**< Sync Word Configuration [23:16] */
#define CC11XX_SYNC1            0x0006      /**< Sync Word Configuration [15:8] */
#define CC11XX_SYNC0            0x0007      /**< Sync Word Configuration [7:0] */
#define CC11XX_SYNC_CFG1        0x0008      /**< Sync Word Detection Configuration Reg 1 */
#define CC11XX_SYNC_CFG0        0x0009      /**< Sync Word Detection Configuration Reg 0 */
#define CC11XX_DEVIATION_M      0x000A      /**< Frequency Deviation Configuration */
#define CC11XX_MODCFG_DEV_E     0x000B      /**< Modulation Format and Frequency Deviation Configuration */
#define CC11XX_DCFILT_CFG       0x000C      /**< Digital DC Removal Configuration */
#define CC11XX_PREAMBLE_CFG1    0x000D      /**< Preamble Lenght Configuration Reg 1 */
#define CC11XX_PREAMBLE_CFG0    0x000E      /**< Preamble Lenght Configuration Reg 0 */
#define CC11XX_FREQ_IF_CFG      0x000F      /**< RX Mixer Frequency Configuration */
#define CC11XX_IQIC             0x0010      /**< Digital Image Channel Compensation Configuration */
#define CC11XX_CHAN_BW          0x0011      /**< Channel Filter Configuration */
#define CC11XX_MDMCFG1          0x0012      /**< General Modem Parameter Configuration Reg 1 */
#define CC11XX_MDMCFG0          0x0013      /**< General Modem Parameter Configuration Reg 0 */
#define CC11XX_SYMBOL_RATE2     0x0014      /**< Symbol Rate Configuration Exponent and Mantissa [19:16] */
#define CC11XX_SYMBOL_RATE1     0x0015      /**< Symbol Rate Configuration Exponent and Mantissa [15:8] */
#define CC11XX_SYMBOL_RATE0     0x0016      /**< Symbol Rate Configuration Exponent and Mantissa [7:0] */
#define CC11XX_AGC_REF          0x0017      /**< AGC Reference Level Configuration */
#define CC11XX_AGC_CS_THR       0x0018      /**< Carrier Sense Threshold Configuration */
#define CC11XX_AGC_GAIN_ADJUST  0x0019      /**< RSSI Offset Configuration */
#define CC11XX_AGC_CFG3         0x001A      /**< Automatic Gain Control Configuration Reg 3 */
#define CC11XX_AGC_CFG2         0x001B      /**< Automatic Gain Control Configuration Reg 2 */
#define CC11XX_AGC_CFG1         0x001C      /**< Automatic Gain Control Configuration Reg 1 */
#define CC11XX_AGC_CFG0         0x001D      /**< Automatic Gain Control Configuration Reg 0 */
#define CC11XX_FIFO_CFG         0x001E      /**< FIFO Configuration */
#define CC11XX_DEV_ADDR         0x001F      /**< Device Address Configuration */
#define CC11XX_SETTLING_CFG     0x0020      /**< Frequency Synthesizer Calibration and Setting Configuration */
#define CC11XX_FS_CFG           0x0021      /**< Frequency Synthesizer Configuration */
#define CC11XX_WOR_CFG1         0x0022      /**< eWOR Configuration Reg 1 */
#define CC11XX_WOR_CFG0         0x0023      /**< eWOR Configuration Reg 0 */
#define CC11XX_WOR_EVENT0_MSB   0x0024      /**< Event 0 Configuration MSB */
#define CC11XX_WOR_EVENT0_LSB   0x0025      /**< Event 0 Configuration LSB */
#define CC11XX_PKT_CFG2         0x0026      /**< Packet Configuration Reg 2 */
#define CC11XX_PKT_CFG1         0x0027      /**< Packet Configuration Reg 1 */
#define CC11XX_PKT_CFG0         0x0028      /**< Packet Configuration Reg 0 */
#define CC11XX_RFEND_CFG1       0x0029      /**< RFEND Configuration Reg 1 */
#define CC11XX_RFEND_CFG0       0x002A      /**< RFEND Configuration Reg 0 */
#define CC11XX_PA_CFG2          0x002B      /**< Power Amplifier Configuration Reg 2 */
#define CC11XX_PA_CFG1          0x002C      /**< Power Amplifier Configuration Reg 1 */
#define CC11XX_PA_CFG0          0x002D      /**< Power Amplifier Configuration Reg 0 */
#define CC11XX_PKT_LEN          0x002E      /**< Packet Length Configuration */
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
#define CC11XX_TOC_CFG          0x2F02      /**< IF Mix Configuration */
#define CC11XX_MARC_SPARE       0x2F03      /**< MARC Spare */
#define CC11XX_ECG_CFG          0x2F04      /**< External Clock Frequency Configuration */
#define CC11XX_CFM_DATA_CFG     0x2F05      /**< Custom Frequency Modulation Configuration */
#define CC11XX_EXT_CTRL         0x2F06      /**< External Control Configuration */
#define CC11XX_RCCAL_FINE       0x2F07      /**< RC Oscillator Calibration Fine */
#define CC11XX_RCCAL_COARSE     0x2F08      /**< RC Oscillator Calibration Coarse */
#define CC11XX_RCCAL_OFFSET     0x2F09      /**< RC Oscillator Calibration Clock Offset */
#define CC11XX_FREQOFF1         0x2F0A      /**< Frequency Offset MSB */
#define CC11XX_FREQOFF0         0x2F0B      /**< Frequency Offset LSB */
#define CC11XX_FREQ2            0x2F0C      /**< Frequency Configuration [23:16] */
#define CC11XX_FREQ1            0x2F0D      /**< Frequency Configuration [15:8] */
#define CC11XX_FREQ0            0x2F0E      /**< Frequency Configuration [7:0] */
#define CC11XX_IF_ADC2          0x2F0F      /**< Analog to Digital Converter Configuration Reg 2 */
#define CC11XX_IF_ADC1          0x2F10      /**< Analog to Digital Converter Configuration Reg 1 */
#define CC11XX_IF_ADC0          0x2F11      /**< Analog to Digital Converter Configuration Reg 0 */
#define CC11XX_FS_DIG1          0x2F12      /**< Frequency Synthesizer Digital Reg 1 */
#define CC11XX_FS_DIG0          0x2F13      /**< Frequency Synthesizer Digital Reg 0 */
#define CC11XX_FS_CAL3          0x2F14      /**< Frequency Synthesizer Calibration Reg 3 */
#define CC11XX_FS_CAL2          0x2F15      /**< Frequency Synthesizer Calibration Reg 2 */
#define CC11XX_FS_CAL1          0x2F16      /**< Frequency Synthesizer Calibration Reg 1 */
#define CC11XX_FS_CAL0          0x2F17      /**< Frequency Synthesizer Calibration Reg 0 */
#define CC11XX_FS_CHP           0x2F18      /**< Frequency Synthesizer Charge Pump Configuration */
#define CC11XX_FS_DIVTWO        0x2F19      /**< Frequency Synthesizer Divide by 2 */
#define CC11XX_FS_DSM1          0x2F1A      /**< FS Digital Synthesizer Module Configuration Reg 1 */
#define CC11XX_FS_DSM0          0x2F1B      /**< FS Digital Synthesizer Module Configuration Reg 0 */
#define CC11XX_FS_DVC1          0x2F1C      /**< Frequency Synthesizer Divider Chain Configuration Reg 1 */
#define CC11XX_FS_DVC0          0x2F1D      /**< Frequency Synthesizer Divider Chain Configuration Reg 0 */
#define CC11XX_FS_LBI           0x2F1E      /**< Frequency Synthesizer Local Bias Configuration */
#define CC11XX_FS_PFD           0x2F1F      /**< Frequency Synthesizer Phase Frequency Detector Configuration */
#define CC11XX_FS_PRE           0x2F20      /**< Frequency Synthesizer Prescaler Configuration */
#define CC11XX_FS_REG_DIV_CML   0x2F21      /**< Frequency Synthesizer Divider Regulator Configuration */
#define CC11XX_FS_SPARE         0x2F22      /**< Frequency Synthesizer Spare */
#define CC11XX_FS_VCO4          0x2F23      /**< FS Voltage Controlled Oscillator Configuration Reg 4 */
#define CC11XX_FS_VCO3          0x2F24      /**< FS Voltage Controlled Oscillator Configuration Reg 3 */
#define CC11XX_FS_VCO2          0x2F25      /**< FS Voltage Controlled Oscillator Configuration Reg 2 */
#define CC11XX_FS_VCO1          0x2F26      /**< FS Voltage Controlled Oscillator Configuration Reg 1 */
#define CC11XX_FS_VCO0          0x2F27      /**< FS Voltage Controlled Oscillator Configuration Reg 0 */
#define CC11XX_GBIAS6           0x2F28      /**< Global Bias Configuration Reg 6 */
#define CC11XX_GBIAS5           0x2F29      /**< Global Bias Configuration Reg 5 */
#define CC11XX_GBIAS4           0x2F2A      /**< Global Bias Configuration Reg 4 */
#define CC11XX_GBIAS3           0x2F2B      /**< Global Bias Configuration Reg 3 */
#define CC11XX_GBIAS2           0x2F2C      /**< Global Bias Configuration Reg 2 */
#define CC11XX_GBIAS1           0x2F2D      /**< Global Bias Configuration Reg 1 */
#define CC11XX_GBIAS0           0x2F2E      /**< Global Bias Configuration Reg 0 */
#define CC11XX_IFAMP            0x2F2F      /**< Intermediate Frequency Amplifier Configuration */
#define CC11XX_LNA              0x2F30      /**< Low Noise Amplifier Configuration */
#define CC11XX_RXMIX            0x2F31      /**< RX Mixer Configuration */
#define CC11XX_XOSC5            0x2F32      /**< Crystal Oscillator Configuration Reg 5 */
#define CC11XX_XOSC4            0x2F33      /**< Crystal Oscillator Configuration Reg 4 */
#define CC11XX_XOSC3            0x2F34      /**< Crystal Oscillator Configuration Reg 3 */
#define CC11XX_XOSC2            0x2F35      /**< Crystal Oscillator Configuration Reg 2 */
#define CC11XX_XOSC1            0x2F36      /**< Crystal Oscillator Configuration Reg 1 */
#define CC11XX_XOSC0            0x2F37      /**< Crystal Oscillator Configuration Reg 0 */
#define CC11XX_ANALOG_SPARE     0x2F38      /**< Analog Spare */
#define CC11XX_PA_CFG3          0x2F39      /**< Power Amplifier Configuration Reg 3 */
// 0x2F3A - 0x2F3E = Not used
// 0x2F3F - 0x2F40 = Reserved
// 0x2F41 - 0x2F63 = Not used
#define CC11XX_WOR_TIME1        0x2F64      /**< eWOR Timer Counter Value MSB */
#define CC11XX_WOR_TIME0        0x2F65      /**< eWOR Timer Counter Value LSB */
#define CC11XX_WOR_CAPTURE1     0x2F66      /**< eWOR Timer Capture Value MSB */
#define CC11XX_WOR_CAPTURE0     0x2F67      /**< eWOR Timer Capture Value LSB */
#define CC11XX_BIST             0x2F68      /**< MARC Built-In Self-Test */
#define CC11XX_DCFILTOFFSET_I1  0x2F69      /**< DC Filter Offset I MSB */
#define CC11XX_DCFILTOFFSET_I0  0x2F6A      /**< DC Filter Offset I LSB */
#define CC11XX_DCFILTOFFSET_Q1  0x2F6B      /**< DC Filter Offset Q MSB */
#define CC11XX_DCFILTOFFSET_Q0  0x2F6C      /**< DC Filter Offset Q LSB */
#define CC11XX_IQIE_I1          0x2F6D      /**< IQ Imbalance Value I MSB */
#define CC11XX_IQIE_I0          0x2F6E      /**< IQ Imbalance Value I LSB */
#define CC11XX_IQIE_Q1          0x2F6F      /**< IQ Imbalance Value Q MSB */
#define CC11XX_IQIE_Q0          0x2F70      /**< IQ Imbalance Value Q LSB */
#define CC11XX_RSSI1            0x2F71      /**< Received Signal Strength Indicator Reg 1 */
#define CC11XX_RSSI0            0x2F72      /**< Received Signal Strength Indicator Reg 0 */
#define CC11XX_MARCSTATE        0x2F73      /**< MARC State */
#define CC11XX_LQI_VAL          0x2F74      /**< Link Quality Indicator Value */
#define CC11XX_PQT_SYNC_ERR     0x2F75      /**< Preamble and Sync Word Error */
#define CC11XX_DEM_STATUS       0x2F76      /**< Demodulator Status */
#define CC11XX_FREQOFF_EST1     0x2F77      /**< Frequency Offset Estiamate MSB */
#define CC11XX_FREQOFF_EST0     0x2F78      /**< Frequency Offset Estiamate LSB */
#define CC11XX_AGC_GAIN3        0x2F79      /**< Automatic Gain Control Reg 3 */
#define CC11XX_AGC_GAIN2        0x2F7A      /**< Automatic Gain Control Reg 2 */
#define CC11XX_AGC_GAIN1        0x2F7B      /**< Automatic Gain Control Reg 1 */
#define CC11XX_AGC_GAIN0        0x2F7C      /**< Automatic Gain Control Reg 0 */
#define CC11XX_CFM_RX_DATA_OUT  0x2F7D      /**< Custom Frequency Modulation RX Data */
#define CC11XX_CFM_TX_DATA_IN   0x2F7E      /**< Custom Frequency Modulation TX Data */
#define CC11XX_ASK_SOFT_RX_DATA 0x2F7F      /**< ASK Soft Decision Output */
#define CC11XX_RNDGEN           0x2F80      /**< Random Number Generator Value */
#define CC11XX_MAGN2            0x2F81      /**< Signal Magnitude after CORDIC [16] */
#define CC11XX_MAGN1            0x2F82      /**< Signal Magnitude after CORDIC [15:8] */
#define CC11XX_MAGN0            0x2F83      /**< Signal Magnitude after CORDIC [7:0] */
#define CC11XX_ANG1             0x2F84      /**< Signal Angular after CORDIC [9:8] */
#define CC11XX_ANG0             0x2F85      /**< Signal Angular after CORDIC [7:0] */
#define CC11XX_CHFILT_I2        0x2F86      /**< Channel Filter Data Real Part [18:16] */
#define CC11XX_CHFILT_I1        0x2F87      /**< Channel Filter Data Real Part [15:8] */
#define CC11XX_CHFILT_I0        0x2F88      /**< Channel Filter Data Real Part [7:0] */
#define CC11XX_CHFILT_Q2        0x2F89      /**< Channel Filter Data Imaginary Part [18:16] */
#define CC11XX_CHFILT_Q1        0x2F8A      /**< Channel Filter Data Imaginary Part [15:8] */
#define CC11XX_CHFILT_Q0        0x2F8B      /**< Channel Filter Data Imaginary Part [8:0] */
#define CC11XX_GPIO_STATUS      0x2F8C      /**< General Purpose input/Output Status */
#define CC11XX_FSCAL_CTRL       0x2F8D      /**< Frequency Synthesizer Calibration Control */
#define CC11XX_PHASE_ADJUST     0x2F8E      /**< Frequency Synthesizer Phase Adjust */
#define CC11XX_PARTNUMBER       0x2F8F      /**< Part Number */
#define CC11XX_PARTVERSION      0x2F90      /**< Part Revision */
#define CC11XX_SERIAL_STATUS    0x2F91      /**< Serial Status */
#define CC11XX_MODEM_STATUS1    0x2F92      /**< Modem Status Reg. 1 */
#define CC11XX_MODEM_STATUS0    0x2F93      /**< Modem Status Reg. 0 */
#define CC11XX_MARC_STATUS1     0x2F94      /**< MARC Status Reg. 1 */
#define CC11XX_MARC_STATUS0     0x2F95      /**< MARC Status Reg. 0 */
#define CC11XX_PA_IFAMP_TEST    0x2F96      /**< Power Amplifier Intermediate Frequency Amplifier Test */
#define CC11XX_FSRF_TEST        0x2F97      /**< Frequency Synthesizer Test */
#define CC11XX_PRE_TEST         0x2F98      /**< Frequency Synthesizer Prescaler Test */
#define CC11XX_PRE_OVR          0x2F99      /**< Frequency Synthesizer Prescaler Override */
#define CC11XX_ADC_TEST         0x2F9A      /**< Analog to Digital Converter Test */
#define CC11XX_DVC_TEST         0x2F9B      /**< Digital Divider Chain Test */
#define CC11XX_ATEST            0x2F9C      /**< Analog Test */
#define CC11XX_ATEST_LVDS       0x2F9D      /**< Analog Test LVDS */
#define CC11XX_ATEST_MODE       0x2F9E      /**< Analog Test Mode */
#define CC11XX_XOSC_TEST1       0x2F9F      /**< Crystal Oscillator Test Reg 1 */
#define CC11XX_XOSC_TEST0       0x2FA0      /**< Crystal Oscillator Test Reg 0 */
// 0x2FA1 - 0x2FD1 = Not used
#define CC11XX_RXFIRST          0x2FD2      /**< RX FIFO Pointer First Entry */
#define CC11XX_TXFIRST          0x2FD3      /**< TX FIFO Pointer First Entry */
#define CC11XX_RXLAST           0x2FD4      /**< RX FIFO Pointer Last Entry */
#define CC11XX_TXLAST           0x2FD5      /**< TX FIFO Pointer Last Entry */
#define CC11XX_NUM_TXBYTES      0x2FD6      /**< TX FIFO Status */
#define CC11XX_NUM_RXBYTES      0x2FD7      /**< RX FIFO Status */
#define CC11XX_FIFO_NUM_TXBYTES 0x2FD8      /**< TX FIFO Status */
#define CC11XX_FIFO_NUM_RXBYTES 0x2FD9      /**< RX FIFO Status */
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
 * \defgroup gpio_signals GPIO signals
 * \ingroup cc1175
 * 
 * \brief GPIO signals.
 * 
 * Reference: CC112x/CC1175 User's Guide Table 10
 * 
 * \{
 */
#define CC11XX_GPIOX_ATRAN_STD_DIG_PAD  0x00    /**< Analog transfer enable: Standard digital pad. */
#define CC11XX_GPIOX_ATRAN_PAD_ANL_MODE 0x80    /**< Analog transfer enable: Pad in analog mode (digital GPIO input and output disabled). */
#define CC11XX_GPIOX_INV_DISABLE        0x00    /**< Invert output enable: Invert output disabled. */
#define CC11XX_GPIOX_INV_ENABLE         0x80    /**< Invert output enable: Invert output enable. */

//-- GPIOX_CFG -----------------------------
#define CC11XX_RXFIFO_THR               0x00    /**< Associated to the RX FIFO. Asserted when the RX FIFO is filled above FIFO_CFG.FIFO_THR. De-asserted when the RX FIFO is drained below (or is equal) to the same threshold. This signal is also available in the MODEM_STATUS1 register. */
#define CC11XX_RXFIFO_THR_PKT           0x01    /**< Associated to the RX FIFO. Asserted when the RX FIFO is filled above FIFO_CFG.FIFO_THR or the end of packet is reached. De-asserted when the RX FIFO is empty. */
#define CC11XX_TXFIFO_THR               0x02    /**< Associated to the TX FIFO. Asserted when the TX FIFO is filled above (or is equal to) (127 −FIFO_CFG.FIFO_THR). De-asserted when the TXFIFO is drained below the same threshold. This signal is also available in the MODEM_STATUS0 register. */
#define CC11XX_TXFIFO_THR_PKT           0x03    /**< Associated to the TX FIFO. Asserted when the TX FIFO is full. Deasserted when the TX FIFO is drained below (127 − FIFO_CFG.FIFO_THR). */
#define CC11XX_RXFIFO_OVERFLOW          0x04    /**< Asserted when the RX FIFO has overflowed. De-asserted when the RXFIFO is flushed (see Section 3.2.4). This signal is also available in the MODEM_STATUS1 register. */
#define CC11XX_TXFIFO_UNDERFLOW         0x05    /**< Asserted when the TX FIFO has underflowed. De-asserted when the TXFIFO is flushed (see Section 3.2.4). This signal is also available in the MODEM_STATUS0 register. */
#define CC11XX_PKT_SYNC_RXTX            0x06    /**< RX: Asserted when sync word has been received and de-asserted at the end of the packet. Will de-assert when the optional address and/or length check fails or the RX FIFO overflows/underflows. TX: Asserted when sync word has been sent, and de-asserted at the end of the packet. Will de-assert if the TX FIFO underflows/overflows. */
#define CC11XX_CRC_OK                   0x07    /**< Asserted simultaneously as PKT_CRC_OK. De-asserted when the first byte is read from the RX FIFO. */
#define CC11XX_SERIAL_CLK               0x08    /**< Serial clock (RX and TX mode). Synchronous to the data in synchronous serial mode. Data is set up on the falling edge in RX and is captured on the rising edge of the serial clock in TX. */
#define CC11XX_SERIAL_RX                0x09    /**< Serial data (RX mode). Used for both synchronous and transparent mode. Synchronous serial mode: Data is set up on the falling edge. Transparent mode: No timing recovery (outputs just the hard limited baseband signal). */
// 0x0A = Reserved (used for test)
#define CC11XX_PQT_REACHED              0x0B    /**< Preamble Quality Reached. Asserted when the quality of the preamble is above the programmed PQT value (see Section 6.8). This signal is also available in the MODEM_STATUS1 register. */
#define CC11XX_PQT_VALID                0x0C    /**< Preamble quality valid. Asserted when the PQT logic has received a sufficient number of symbols (see Section 6.8). This signal is also available in the MODEM_STATUS1 register. */
#define CC11XX_RSSI_VALID               0x0D    /**< RSSI calculation is valid. */
#define CC11XX_RSSI_UPDATE              0x0E    /**< Pins 3 and 2 = A pulse occurring each time the RSSI value is updated (see Figure 16). */
#define CC11XX_AGC_HOLD                 0x0E    /**< Pin 1 = AGC waits for gain settling (see Figure 16). */
#define CC11XX_AGC_UPDATE               0x0E    /**< Pin 0 = A pulse occurring each time the front end gain has been adjusted (see Figure 16). */
#define CC11XX_CCA_STATUS               0x0F    /**< Pins 3 and 1 = Current CCA status. */
#define CC11XX_TXONCCA_DONE             0x0F    /**< Pin 2 = A pulse occurring when a decision has been made as to whether the channel is busy or not. This signal must be used as an interrupt to the MCU. When this signal is asserted/de-asserted, TXONCCA_FAILED can be checked. */
#define CC11XX_TXONCCA_FAILED           0x0F    /**< Pin 0 = TX on CCA failed. This signal is also available in the MARC_STATUS0 register. */
#define CC11XX_CARRIER_SENSE_VALID      0x10    /**< CARRIER_SENSE is valid (see Figure 16). */
#define CC11XX_CARRIER_SENSE            0x11    /**< Carrier sense. High if RSSI level is above threshold (see section 6.9.1) (see Figure 16). */
#define CC11XX_DSSS_CLK                 0x12    /**< Pins 3 and 1 = DSSS clock (see Section 5.2.6 for more details). */
#define CC11XX_DSSS_DATA0               0x12    /**< Pin 2 = DSSS data0 (see Section 5.2.6 for more details). */
#define CC11XX_DSSS_DATA1               0x12    /**< Pin 0 = DSSS data1 (see Section 5.2.6 for more details). */
#define CC11XX_PKT_CRC_OK               0x13    /**< Asserted in RX when PKT_CFG1.CRC_CFG = 1 or 10 b and a good packet is received. This signal is always on if the radio is in TX or if the radio is in RX and PKT_CFG1.CRC_CFG = 0. The signal is de-asserted when RX mode is entered and PKT_CFG1.CRC_CFG ≠ 0. This signal is also available in the LQI_VAL register. */
#define CC11XX_MCU_WAKEUP               0x14    /**< MCU wake up signal. Read MARC_STATUS1.MARC_STATUS_OUT to find the cause of the wake up event (see Section 3.4.1.2 for more details). This signal is also available in the MARC_STATUS0 register. The signal is a pulse. */
#define CC11XX_SYNC_LOW0_HIGH1          0x15    /**< DualSync detect. Only valid when SYNC_CFG0.SYNC_MODE = 111b. When SYNC_EVENT is asserted this bit can be checked to see which sync word is found. This signal is also available in the DEM_STATUS register. */
// 0x16 = Reserved (used for test)
#define CC11XX_LNA_PA_REG_PD            0x17    /**< Common regulator control for PA and LNA. Indicates RF operation. */
#define CC11XX_LNA_PD                   0x18    /**< Control external LNA. */
#define CC11XX_PA_PD                    0x19    /**< Control external PA. */
#define CC11XX_RX0TX1_CFG               0x1A    /**< Indicates whether RF operation is in RX or TX (this signal is 0 in IDLE state). */
// 0x1B = Reserved (used for test)
#define CC11XX_IMAGE_FOUND              0x1C    /**< Image detected by image rejection calibration algorithm. */
#define CC11XX_CLKEN_CFM                0x1D    /**< Data clock for demodulator soft data (see Section 5.2.4 for more details). */
#define CC11XX_CFM_TX_DATA_CLK          0x1E    /**< Data clock for modulator soft data (see Section 5.2.4 for more details). */
// 0x1F - 0x20 = Reserved (used for test)
#define CC11XX_RSSI_STEP_FOUND          0x21    /**< RSSI step found during packet reception (after the assertion of SYNC_EVENT. The RSSI step is either 3 or 6 dB (configured through AGC_CFG3.RSSI_STEP_THR). This signal is also available in the DEM_STATUS register. */
#define CC11XX_RSSI_STEP_EVENT          0x22    /**< RSSI step detected. This signal is asserted if there is an RSSI step of 3 or 6 dB during sync search or during packet reception. The RSSI step is configured through AGC_CFG3.RSSI_STEP_THR). The signal is a pulse. */
#define CC11XX_LOCK                     0x23    /**< Pins 1 and 0 = Out of lock status signal. Indicates out of lock when the signal goes low. This signal is also available in the FSCAL_CTR register. */
#define CC11XX_ANTENNA_SELECT           0x24    /**< Antenna diversity control. Can be used to control external antenna switch. If differential signal is needed, two GPIOs can be used with one of them having IOCFGx.GPIOx_INV set to 1. */
#define CC11XX_MARC_2PIN_STATUS_1       0x25    /**< Partial MARC state status. These signals are also available in the MARCSTATE register. */
#define CC11XX_MARC_2PIN_STATUS_0       0x26    /**< See MARC_2PIN_STATUS_1. */
#define CC11XX_TXFIFO_OVERFLOW          0x27    /**< Pin 2 = Asserted when the TX FIFO has overflowed. De-asserted when the TXFIFO is flushed (see Section 3.2.4). This signal is also available in the MODEM_STATUS0 register. */
#define CC11XX_RXFIFO_UNDERFLOW         0x27    /**< Pin 0 = Asserted when the RX FIFO has underflowed. De-asserted when the RXFIFO is flushed (see Section 3.2.4). This signal is also available in the MODEM_STATUS1 register. */
#define CC11XX_MAGN_VALID               0x28    /**< Pin 3 = New CORDIC magnitude sample. */
#define CC11XX_CHFILT_VALID             0x28    /**< Pin 2 = New channel filter sample. */
#define CC11XX_RCC_CALL_VALID           0x28    /**< Pin 1 = RCOSC calibration has been performed at least once. */
#define CC11XX_CHFILT_STARTUP_VALID     0x28    /**< Pin 0 = Channel filter has settled. */
#define CC11XX_COLLISION_FOUND          0x29    /**< Pins 3 and 1 = Asserted if a sync word is found during packet reception (i.e. after SYNC_EVENT has been asserted) if MDMCFG1.COLLISION_DETECT_EN = 1. This signal is also available in the DEM_STATUS register. */
#define CC11XX_SYNC_EVENT               0x29    /**< Pin 2 = Sync word found (pulse). */
#define CC11XX_COLLISION_EVENT          0x29    /**< Pin 0 = Sync found during receive (pulse). */
#define CC11XX_PA_RAMP_UP               0x2A    /**< Asserted when ramping is started (for compliance testing). */
#define CC11XX_CRC_FAILED               0x2B    /**< Pin 3 = Packet CRC error. */
#define CC11XX_LENGTH_FAILED            0x2B    /**< Pin 2 = Packet length error. */
#define CC11XX_ADDR_FAILED              0x2B    /**< Pin 1 = Packet address error. */
#define CC11XX_UART_FRAMING_ERROR       0x2B    /**< Pin 0 = Packet UART framing error. */
#define CC11XX_AGC_STABLE_GAIN          0x2C    /**< AGC has settled to a gain. The AGC gain is reported stable whenever the current gain setting is equal to the previous gain setting. This condition is evaluated each time a new internal RSSI estimate is computed (see Figure 16). */
#define CC11XX_AGC_UPDATE               0x2D    /**< A pulse occurring each time the front end gain has been adjusted (see Figure 16). */
#define CC11XX_ADC_CLOCK                0x2E    /**< Pins 3 and 1 = ADC clock. */
#define CC11XX_ADC_Q_DATA_SAMPLE        0x2E    /**< Pin 2 = ADC sample (Q data). */
#define CC11XX_ADC_I_DATA_SAMPLE        0x2E    /**< Pin 0 = ADC sample (I data). */
// 0x2F = Reserved (used for test)
#define CC11XX_HIGHZ                    0x30    /**< High impedance (tri-state). */
#define CC11XX_EXT_CLOCK                0x31    /**< External clock (divided crystal clock). The division factor is controlled through the ECG_CFG.EXT_CLOCK_FREQ register field. */
#define CC11XX_CHIP_RDYn                0x32    /**< Chip ready (XOSC is stable). */
#define CC11XX_HW0                      0x33    /**< HW to 0 (HW to 1 achieved with IOCFGx.GPIOx_INV = 1). */
// 0x34 - 0x35 = Reserved (used for test)
#define CC11XX_CLOCK_32K                0x36    /**< 32/40 kHz clock output from internal RC oscillator. */
#define CC11XX_WOR_EVENT0               0x37    /**< WOR EVENT0. */
#define CC11XX_WOR_EVENT1               0x38    /**< WOR EVENT1. */
#define CC11XX_WOR_EVENT2               0x39    /**< WOR EVENT2. */
// 0x3A = Reserved (used for test)
#define CC11XX_XOSC_STABLE              0x3B    /**< XOSC is stable (has finished settling). */
#define CC11XX_EXT_OSC_EN               0x3C    /**< External oscillator enable (used to control e.g. a TCXO). Note that this signal is only asserted is a TCXO is present. */
// 0x3D - 0x3F = Reserved (used for test)
//! \} End of gpio_signals

/**
 * \fn cc11xx_Init
 * 
 * \brief cc11xx initialization
 * 
 * This function makes:
 *      -# Initialization of the Reset pin
 *      -# Chip reset (Manual) using cc11xx_ManualReset()
 *      -# Register configuration using cc11xx_RegConfig()
 *      .
 * 
 * \return None
 */
void cc11xx_Init();

/**
 * \fn cc11xx_RegConfig
 * 
 * \brief Configuration of the registers of the cc11xx
 * 
 * This function takes an array with the address of a register and its value,
 * and writes the data using cc11xx_WriteReg().
 * 
 * \return None
 */
void cc11xx_RegConfig();

/**
 * \fn cc11xx_WriteRef
 * 
 * \brief 
 * 
 * \param addr is the address of the register to be written.
 * \param pData is a pointer to the data to be written in the register.
 * \param len is the size of the data (*pData) to be written.
 * 
 * \return Chip status
 */
uint8_t cc11xx_WriteReg(uint16_t addr, uint8_t *pData, uint8_t len);

/**
 * \fn cc11xx_ReadRef
 * 
 * \brief 
 * 
 * \param addr is the address of the register to be written.
 * \param pData is a pointer to the data to be written in the register.
 * \param len is the size of the data (*pData) to be written.
 * 
 * \return Chip status
 */
uint8_t cc11xx_ReadReg(uint16_t addr, uint8_t *pData, uint8_t len);

/**
 * \fn cc11xx_CmdStrobe
 * 
 * \brief Sends a command strobe to the cc11xx.
 * 
 * \param cmd is the command strobe (See "CC112X/CC1175 User's Guide", table 6).
 * 
 * To get a list with all the possible commands, see: "CC112X/CC1175 User's Guide", table 6.
 * The table above is transcripted in \ref cmd_strobe CC11XX Command Strobes.
 * 
 * \return Chip status
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
 * \brief Read/Write data using Burst/Single mode.
 * 
 * \param addr is the address of the register to be accessed.
 * \param pData is a pointer to the data to be written in the register (Write mode).
 *        Or a pointer to a variable to receive the register value.
 * \param len is the size of the data (pData).
 *
 * \return None
 */
void cc11xx_ReadWriteBurstSingle(uint8_t addr, uint8_t *pData, uint16_t len);

/**
 * \fn cc11xx_ManualReset
 * 
 * \brief Reset by using RESETn pin (active-low).
 * 
 * \return None
 */
void cc11xx_ManualReset();

/**
 * \fn cc11xx_SRESReset
 * 
 * \brief Reset the chip by using the SRES command strobe.
 * 
 * \return None
 */
void cc11xx_SRESReset();

/**
 * \fn cc11xx_ManualCalibration()
 * 
 * \brief Chip calibration.
 * 
 * See "CC112X, CC1175 Silicon Errata".
 * 
 * \return None
 */
void cc11xx_ManualCalibration();

/**
 * \fn cc11xx_WriteTXFIFO()
 * 
 * \brief Writes data into the TX FIFO.
 * 
 * \param pData is a pointer to the data to be written.
 * \param len is the size of the data (*pData) to be written.
 * 
 * \return Chip status
 */
uint8_t cc11xx_WriteTXFIFO(uint8_t *pData, uint8_t len);

#endif // CC11XX_H_

//! \} End of CC1175 group
