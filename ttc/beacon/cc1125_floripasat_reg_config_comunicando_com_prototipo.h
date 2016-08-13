// Carrier frequency = 433.000000
// Modulation format = 2-FSK
// Bit rate = 1.2
// Deviation = 3.997803
// Address config = No address check
// Packet length mode = Variable
// Packet length = 255
// PA ramping = true
// RX filter BW = 66.666667
// Manchester enable = false
// Performance mode = High Performance
// Symbol rate = 1.2
// Whitening = false
// Device address = 0
// Packet bit length = 0
// TX power = 15

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

static const registerSetting_t preferredSettings[]= 
{
  {CC112X_IOCFG3,            0xB0},
  {CC112X_IOCFG2,            0x06},
  {CC112X_IOCFG1,            0xB0},
  {CC112X_IOCFG0,            0x40},
  //------- Reg Modulations -------------------------
  //{CC112X_SYNC_CFG1,         0x08},	// Mod 2-GFSK
  //{CC112X_MODCFG_DEV_E,      0x0B}, 	// Mod 2-GFSK
  {CC112X_SYNC_CFG1,         0x0B},		// Mod 2-FSK
  {CC112X_MODCFG_DEV_E,      0x03}, 	// Mod 2-FSK
  //-------------------------------------------------
  {CC112X_DCFILT_CFG,        0x1C},
  {CC112X_IQIC,              0xC6},
  {CC112X_MDMCFG0,           0x05},
  {CC112X_AGC_REF,           0x20},
  {CC112X_AGC_CS_THR,        0x19},
  {CC112X_AGC_CFG1,          0xA9},
  {CC112X_AGC_CFG0,          0xCF},
  {CC112X_FIFO_CFG,          0x00},
  {CC112X_SETTLING_CFG,      0x03},
  {CC112X_FS_CFG,            0x14},
  {CC112X_PKT_CFG0,          0x20},
  //------ Reg Power -------------------------------
  {CC112X_PA_CFG2,           0x74},	//Pw: 74 = 15dBm //0x5D = 0dBm //ox43 = -11dBm
  //------------------------------------------------
  {CC112X_PA_CFG0,           0x7E},
  {CC112X_PKT_LEN,           0xFF},
  {CC112X_IF_MIX_CFG,        0x00},
  {CC112X_FREQOFF_CFG,       0x22},
  //------------------------------------
  // Freq = 437.5 MHz
  //{CC112X_FREQ2,             0x6D},
  //{CC112X_FREQ1,             0x60},
  //------------------------------------
  // Freq = 435 MHz
  //{CC112X_FREQ2,             0x6C},
  //{CC112X_FREQ1,             0xC0},
  //------------------------------------
  //Freq = 433MHz (Medido = 432.995)
  {CC112X_FREQ2,             0x6C},
  {CC112X_FREQ1,             0x40},
  //------------------------------------
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
  {CC112X_PARTNUMBER,        0x5A},
  {CC112X_PARTVERSION,       0x21},
  {CC112X_MODEM_STATUS1,     0x10},
  {CC112X_XOSC_TEST1,        0x08},
};


#ifdef  __cplusplus
}
#endif

#endif
