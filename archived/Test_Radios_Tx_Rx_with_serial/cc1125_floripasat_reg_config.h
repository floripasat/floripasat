//FloripaSat TX power = 15 
//FloripaSat PA ramping = true 
//FloripaSat Packet length = 255 
//FloripaSat Device address = 0 
//FloripaSat Performance mode = High Performance 
//FloripaSat Whitening = false 
//FloripaSat Modulation format = 2-FSK 
//FloripaSat Address config = No address check 
//FloripaSat Bit rate = 1.2 
//FloripaSat Deviation = 3.997803 
//FloripaSat Packet bit length = 0 
//FloripaSat RX filter BW = 10.000000 
//FloripaSat Packet length mode = Variable 
//FloripaSat Carrier frequency = 437.500000 
//FloripaSat Manchester enable = false 
//FloripaSat Symbol rate = 1.2 
//****************************************************************************/
#ifndef CC1125_FLORIPASAT_REG_CONFIG_H
#define CC1125_FLORIPASAT_REG_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * INCLUDES
 */
#include "hal_spi_rf_floripasat.h"
#include "cc112x_spi.h"


static const registerSetting_t preferredSettings[]= 
{
		  {CC112X_IOCFG3,            0xB0},
		  {CC112X_IOCFG2,            0x06},
		  {CC112X_IOCFG1,            0xB0},
		  {CC112X_IOCFG0,            0x40},
		  {CC112X_SYNC_CFG1,         0x08},
		  {CC112X_DCFILT_CFG,        0x1C},
		  {CC112X_IQIC,              0xC6},
		  {CC112X_CHAN_BW,           0x11},
		  {CC112X_MDMCFG0,           0x05},
		  {CC112X_AGC_REF,           0x20},
		  {CC112X_AGC_CS_THR,        0x19},
		  {CC112X_AGC_CFG1,          0xA9},
		  {CC112X_AGC_CFG0,          0xCF},
		  {CC112X_FIFO_CFG,          0x00},
		  {CC112X_SETTLING_CFG,      0x03},
		  {CC112X_FS_CFG,            0x14},
		  {CC112X_PKT_CFG0,          0x20},
		  {CC112X_PA_CFG0,           0x7E},
		  {CC112X_PKT_LEN,           0xFF},
		  {CC112X_IF_MIX_CFG,        0x00},
		  {CC112X_FREQOFF_CFG,       0x22},
		  {CC112X_FREQ2,             0x6D},
		  {CC112X_FREQ1,             0x60},
		  {CC112X_FS_DIG1,           0x00},
		  {CC112X_FS_DIG0,           0x5F},
		  {CC112X_FS_CAL0,           0x0E},
		  {CC112X_FS_DIVTWO,         0x03},
		  {CC112X_FS_DSM0,           0x33},
		  {CC112X_FS_DVC0,           0x17},
		  {CC112X_FS_PFD,            0x50},
		  {CC112X_FS_PRE,            0x6E},
		  {CC112X_FS_REG_DIV_CML,    0x14},
		  {CC112X_FS_SPARE,          0xAC},
		  {CC112X_XOSC5,             0x0E},
		  {CC112X_XOSC3,             0xC7},
		  {CC112X_XOSC1,             0x07},
		  {CC112X_PARTNUMBER,        0x58},
		  {CC112X_PARTVERSION,       0x21},
		  {CC112X_MODEM_STATUS1,     0x10},
		  {CC112X_XOSC_TEST1,        0x0C},
//  {CC112X_IOCFG3,            0xB0},
//  {CC112X_IOCFG2,            0x06},
//  {CC112X_IOCFG0,            0x40},
//  {CC112X_SYNC_CFG1,         0x0B},
//  {CC112X_MDMCFG0,           0x05},
//  {CC112X_AGC_CS_THR,        0xEB},
//  {CC112X_AGC_CFG1,          0xA0},
//  {CC112X_FIFO_CFG,          0x78},
//  {CC112X_SETTLING_CFG,      0x03},
//  {CC112X_FS_CFG,            0x14},
//  {CC112X_WOR_CFG0,          0x20},
//  {CC112X_WOR_EVENT0_MSB,    0x02},
//  {CC112X_WOR_EVENT0_LSB,    0xE9},
//  {CC112X_PKT_CFG0,          0x20},
//  {CC112X_RFEND_CFG0,        0x09},
//  {CC112X_PKT_LEN,           0xFF},
//  {CC112X_FREQOFF_CFG,       0x22},
//  {CC112X_RCCAL_FINE,        0x09},
//  {CC112X_RCCAL_COARSE,      0x48},
//  {CC112X_RCCAL_OFFSET,      0x04},
//  {CC112X_FREQ2,             0x6D},
//  {CC112X_FREQ1,             0x60},
//  {CC112X_FS_DIG1,           0x00},
//  {CC112X_FS_DIG0,           0x5F},
//  {CC112X_FS_CAL0,           0x0E},
//  {CC112X_FS_CHP,            0x2A},
//  {CC112X_FS_DIVTWO,         0x03},
//  {CC112X_FS_DSM0,           0x33},
//  {CC112X_FS_DVC0,           0x17},
//  {CC112X_FS_PFD,            0x50},
//  {CC112X_FS_PRE,            0x6E},
//  {CC112X_FS_REG_DIV_CML,    0x14},
//  {CC112X_FS_SPARE,          0xAC},
//  {CC112X_FS_VCO4,           0x1F},
//  {CC112X_FS_VCO2,           0x4C},
//  {CC112X_FS_VCO1,           0x9C},
//  {CC112X_XOSC5,             0x0E},
//  {CC112X_XOSC1,             0x07},
//  {CC112X_WOR_TIME0,         0x58},
//  {CC112X_PARTNUMBER,        0x58},
//  {CC112X_PARTVERSION,       0x21},
//  {CC112X_SERIAL_STATUS,     0x10},
//  {CC112X_MODEM_STATUS1,     0x10},
//  {CC112X_XOSC_TEST1,        0x10},
};

#ifdef  __cplusplus
}
#endif

#endif
