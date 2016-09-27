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

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
// 		Registradores do CC1175
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------


// Modulation format = 2-FSK
// Bit rate = 1.2
// Packet length = 255
// RX filter BW = 10.000000
// Packet length mode = Variable
// Address config = No address check
// Symbol rate = 1.2
// Performance mode = High Performance
// Carrier frequency = 437.781006
// TX power = 15
// Device address = 0
// Whitening = false
// Deviation = 3.997803
// Packet bit length = 0
// Manchester enable = false
// PA ramping = true


static const registerSetting_t preferredSettings[]= 
{
  {CC112X_IOCFG3,            0xB0},
  {CC112X_IOCFG2,            0x06},
  {CC112X_IOCFG1,            0xB0},
  {CC112X_IOCFG0,            0x40},
  {CC112X_SYNC_CFG1,         0x0B},
  {CC112X_DCFILT_CFG,        0x1C},
  {CC112X_IQIC,              0x46},
  {CC112X_CHAN_BW,           0x42},
  {CC112X_MDMCFG0,           0x05},
  {CC112X_AGC_REF,           0x20},
  {CC112X_AGC_CS_THR,        0x19},
  {CC112X_AGC_CFG1,          0xA9},
  {CC112X_AGC_CFG0,          0xCF},
  {CC112X_FIFO_CFG,          0x00},
  {CC112X_FS_CFG,            0x14},
  {CC112X_PKT_CFG0,          0x20},
  {CC112X_PA_CFG0,           0x7E},
  {CC112X_PKT_LEN,           0xFF},
  {CC112X_IF_MIX_CFG,        0x00},
  {CC112X_FREQOFF_CFG,       0x22},
  {CC112X_FREQ2,             0x6C},
  {CC112X_FREQ1,             0x40},
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
};




#ifdef  __cplusplus
}
#endif

#endif

