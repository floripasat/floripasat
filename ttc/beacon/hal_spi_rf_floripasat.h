/*
 * hal_spi_rf_floripasat.h
 *
 *  Created on: 12/02/2016
 *      Author: Julian
 */

#ifndef HAL_SPI_RF_FLORIPASAT_H_
#define HAL_SPI_RF_FLORIPASAT_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * INCLUDES
 */
#include <msp430.h>
#include "hal_types.h"
#include "hal_defs.h"

/******************************************************************************
 * CONSTANTS
 */

// MCU MSP430F6659 FloripaSat
#define TRXEM_PORT_SEL       P2SEL
#define TRXEM_PORT_OUT       P2OUT
#define TRXEM_PORT_DIR       P2DIR
#define TRXEM_PORT_IN        P2IN

// MCU MSP430F6659 FloripaSat (Beacon)
#define TRXEM_SPI_MOSI_PIN   BIT1		// P2.1
#define TRXEM_SPI_MISO_PIN   BIT2		// P2.2
#define TRXEM_SPI_SCLK_PIN   BIT3		// P2.3
#define TRXEM_SPI_SC_N_PIN   BIT0		// P2.0

// MCU MSP430F6659 FloripaSat
#define RF_RESET_N_PORT_OUT  P1OUT
#define RF_RESET_N_PORT_SEL  P1SEL
#define RF_RESET_N_PORT_DIR  P1DIR
#define RF_RESET_N_PIN       BIT3		// P1.3 (RESE_n transceiver)


#define RADIO_BURST_ACCESS   0x40		// [R/W' 1 A5 A4 A3 A2 A1 A0] = 0100 0000 = 0x40 (CC112x User's Guide pg.10)
#define RADIO_SINGLE_ACCESS  0x00		// [R/W' 0 A5 A4 A3 A2 A1 A0] = 0000 0000 = 0x00 (CC112x User's Guide pg.10)
#define RADIO_READ_ACCESS    0x80		// [1 B/S A5 A4 A3 A2 A1 A0]  = 1000 0000 = 0x80 (CC112x User's Guide pg.10)
#define RADIO_WRITE_ACCESS   0x00		// [0 B/S A5 A4 A3 A2 A1 A0]  = 0000 0000 = 0x00 (CC112x User's Guide pg.10)


/* Bit fields in the chip status byte */
												// [x7 y6 y5 y4 z3 z2 z1 z0]  (CC112x User's Guide pg.9)
#define STATUS_CHIP_RDYn_BM             0x80 	// x (default 1b): Stays high until power and crystal have stabilized. Should always be low when using the SPI interface.
#define STATUS_STATE_BM                 0x70	// y (default 111b): Indicates the current main state machine mode (State default TX FIFO ERROR)
#define STATUS_FIFO_BYTES_AVAILABLE_BM  0x0F	// z (default 1111b): Reserved


/******************************************************************************
 * MACROS
 */

/* Macros for Tranceivers(TRX) */
#define TRXEM_SPI_BEGIN()              st( TRXEM_PORT_OUT &= ~TRXEM_SPI_SC_N_PIN; NOP(); )
#define TRXEM_SPI_TX(x)                st( UCB0IFG &= ~UCRXIFG; UCB0TXBUF= (x); )
#define TRXEM_SPI_WAIT_DONE()          st( while(!(UCB0IFG & UCRXIFG)); )
#define TRXEM_SPI_RX()                 UCB0RXBUF
#define TRXEM_SPI_WAIT_MISO_LOW(x)     st( uint8 count = 200; \
                                           while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN) \
                                           { \
                                              __delay_cycles(5000); \
                                              count--; \
                                              if (count == 0) break; \
                                           } \
                                           if(count>0) (x) = 1; \
                                           else (x) = 0; )

#define TRXEM_SPI_END()                st( NOP(); TRXEM_PORT_OUT |= TRXEM_SPI_SC_N_PIN; )

/******************************************************************************
 * TYPEDEFS
 */

typedef struct
{
  uint16  addr;
  uint8   data;
}registerSetting_t;

typedef uint8 rfStatus_t;

/******************************************************************************
 * PROTOTYPES
 */

void trxRfSpiInterfaceInit(uint8 clockDivider);
rfStatus_t trx8BitRegAccess(uint8 accessType, uint8 addrByte, uint8 *pData, uint16 len);
rfStatus_t trxSpiCmdStrobe(uint8 cmd);

/* CC112X specific prototype function */
rfStatus_t trx16BitRegAccess(uint8 accessType, uint8 extAddr, uint8 regAddr, uint8 *pData, uint8 len);

#ifdef  __cplusplus
}
#endif


#endif /* HAL_SPI_RF_FLORIPASAT_H_ */
