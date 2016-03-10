/*
						  +-------------------------------+
                          |                               |
                          |                (USCI_A0) P2.0 +(17)----------> SPI0_OBDH_SCLK
                          |                               |
                          |                          P2.3 +(20)----------> SPI0_OBDH_CSn
                          |                               |
                          |                (USCI_A0) P2.4 +(21)----------> SPI0_OBDH_MOSI
                          |                               |
                          |                (USCI_A0) P2.5 <(22)----------+ SPI0_OBDH_MISO
                          |                               |
                          |                 (Port A) P1.6 <----------> GPIO0_TRANS
                          |                               |
                          |                 (Port A) P1.5 <(39)-------> GPIO2_TRANS
                          |                               |
                          |                 (Port A) P2.7 <----------> GPIO3_TRANS
                          |                               |
                          |                 (Port A) P1.3 +----------> RESETn_TRANS
                          |                               |
                          |                          P7.6 +----------> CTRL_GAIN_PA0
                          |                               |
ENE_3V3_PA_TTC <----------+ P1.1                     P5.5 +----------> CTRL_RF_SWT_RX
                          |                               |
   OBDH_STATUS <----------> P1.2                     P5.3 +----------> CTRL_RF_SWT_TX
                          |                               |
      XIN_OBDH +----------+ XIN                      P5.4 +(32)----------> LED_SYSTEM
                          |                               |
     XOUT_OBDH +----------+ XOUT                          |
                          |                               |
 JTAG_OBDH_RST +----------> RST_N(RST active low)         |
                          |                               |
                          +-------------------------------+

*/




/*******************************************************************************
* INCLUDES
*/
#include <msp430.h>
#include "stdlib.h"
#include "stdint.h"
#include "bsp.h"
#include "hal_spi_rf_floripasat.h"
#include "cc112x_spi.h"
#include "cc1125_floripasat_reg_config.h"
#include "io_pin_int.h"


/******************************************************************************
* DEFINES
*/
#define ISR_ACTION_REQUIRED     1
#define ISR_IDLE                0

#define RX_FIFO_ERROR           0x11
#define PKTLEN                  30  		// 1 < PKTLEN < 126
//#define PKTLEN                60  		// 1 < PKTLEN < 126
#define GPIO3                   0x80		// P2.7 (1000 0000)	FloripaSat
#define GPIO2                   0x20		// P1.5 (0010 0000) FloripaSat
#define GPIO0                   0x40		// P1.6 (0100 0000) FloripaSat

/*******************************************************************************
* LOCAL VARIABLES
*/
static uint8_t  packetSemaphore;
uint16_t packetCounter = 0;

uint8 saveRegisterTest;
uint8 leituraFIFO;
uint8 leituratrans;

/*******************************************************************************
* STATIC FUNCTIONSb
*/
static void initMCU(void);
static void registerConfig(void);
static void runTX(void);
static void runRX(void);
static void manualCalibration(void);
static void radioTxISR(void);
static void radioRxISR(void);
static void createPacket(uint8_t randBuffer[]);
static void waitMs(uint16 mSec);
static void waitUs(uint16 uSec);


int main(void) {

	P5SEL &= ~OBDH_LED_SYSTEM;							// P5.4 (pin 32)
	P5DIR |=  OBDH_LED_SYSTEM;							// DIR output

    initMCU();											// Initialize MCU and peripherals

    registerConfig();									// Write radio registers
     //runTX();											// Enter runTX, never coming back
     runRX();
	return 0;
}




/*******************************************************************************
*   @fn         initMCU
*   @brief      Initialize MCU and board peripherals
*   @param      none
*   @return     none
*/
static void initMCU(void) {

    // Init clocks and I/O					// -----> Verificar essa função para utili configurar o MSP <-------
    bspInit(BSP_SYS_CLK_1MHZ);				// O valor maximo para programar o CC1125 (fsclk) é 8MHz


    // Instantiate transceiver RF SPI interface to SCLK ~ 4 MHz
    // Input parameter is clockDivider
    // SCLK frequency = SMCLK/clockDivider
    trxRfSpiInterfaceInit(2);				// ----> Configura USCI_A0 utilizado no FloripaSat


    // Enable global interrupt
    _BIS_SR(GIE);
}


/*******************************************************************************
*   @fn         registerConfig
*   @brief      Write register settings as given by SmartRF Studio found in
*               cc112x_easy_link_reg_config.h
*   @param      none
*   @return     none
*/

static void registerConfig(void) {

	uint16 i;
    uint8 writeByte;

    trxSpiCmdStrobe(CC112X_SRES);						// Reset radio

        // Write registers to radio
    for(i = 0; i < (sizeof(preferredSettings)/sizeof(registerSetting_t)); i++) {
        	writeByte = preferredSettings[i].data;
        	cc112xSpiWriteReg(preferredSettings[i].addr, &writeByte, 1);
        }



}


/*******************************************************************************
*   @fn         runTX
*
*   @brief      Continuously sends packets on button push until button is pushed
*               again. After the radio has gone into TX the function waits for
*               interrupt that packet has been sent. Updates packet counter and
*               display for each packet sent.
*
*   @param      none
*
*   @return    none
*/
static void runTX(void) {
	// Initialize packet buffer of size PKTLEN + 1
	uint8 txBuffer[PKTLEN+1] = {0};


	// Connect ISR (Interrupt Service Routine) function to GPIO2 ...
	// Register an interrupt handler to the specified GPIO pin(s).
	ioPinIntRegister(IO_PIN_PORT_1, GPIO2, &radioTxISR);

	// Interrupt on falling edge
	ioPinIntTypeSet(IO_PIN_PORT_1, GPIO2, IO_PIN_FALLING_EDGE);

	// Clear ISR flag
	ioPinIntClear(IO_PIN_PORT_1, GPIO2);

	// Enable interrupt
	ioPinIntEnable(IO_PIN_PORT_1, GPIO2);


	// Calibrate radio according to errata
	manualCalibration();

	// Infinite loop
	while(1){

		// Wait for button push
		if(1) {										// --------------->  Definir condição de entrada <----------------

			// Continiously sent packets until button is pressed
		    do {
		    	// Update packet counter
		        packetCounter++;

		        // Create a random packet with PKTLEN + 2 byte packet
		        // counter + n x random bytes
		        createPacket(txBuffer);

		        // Write packet to TX FIFO
		        cc112xSpiWriteTxFifo(txBuffer, sizeof(txBuffer));

		      //  cc112xSpiReadReg(CC112X_IOCFG2, &leituraFIFO, 1); //Test

		        // Strobe TX to send packet
		        trxSpiCmdStrobe(CC112X_STX);

		        //cc112xSpiReadReg(CC112X_IOCFG2, &leituratrans, 1); //Test


		        // Wait for interrupt that packet has been sent.
		        // (Assumes the GPIO connected to the radioRxTxISR function is
		        // set to GPIOx_CFG = 0x06)
		        while(packetSemaphore != ISR_ACTION_REQUIRED);

		        // Clear semaphore flag
               packetSemaphore = ISR_IDLE;


               //Wait for a random amount of time between each packet
		       waitMs(3*(rand()%10+3));				// ---------------> Função utilizada simplesmente para adicionar delay ente pacotes transmitidos

		     //  cc112xSpiReadReg(CC112X_IOCFG2, &saveRegisterTest, 1); //Test

		    //} while (!bspKeyPushed(BSP_KEY_ALL));
		    } while (1);							// --------------->  Definir condição de saida <----------------
		}



	}
}

/*******************************************************************************
*   @fn         runRX
*
*   @brief      Puts radio in RX and waits for packets. Function assumes
*               that status bytes are appended in the RX_FIFO
*               Update packet counter and display for each packet received.
*
*   @param      none
*
*   @return     none
*/
static void runRX(void) {

    //uint8 rxBuffer[128] = {0};
	uint8 rxBuffer[30] = {0};
	uint8 rxBytes;
    uint8 marcState;

    // Connect ISR function to GPIO2
    ioPinIntRegister(IO_PIN_PORT_1, GPIO2, &radioRxISR);

    // Interrupt on falling edge
    ioPinIntTypeSet(IO_PIN_PORT_1, GPIO2, IO_PIN_FALLING_EDGE);

    // Clear ISR flag
    ioPinIntClear(IO_PIN_PORT_1, GPIO2);

    // Enable interrupt
    ioPinIntEnable(IO_PIN_PORT_1, GPIO2);

    // Update LCD
  //  updateLcd();

    // Calibrate radio according to errata
    manualCalibration();

    // Set radio in RX
    trxSpiCmdStrobe(CC112X_SRX);


    // Infinite loop
    while(TRUE) {

        // Wait for packet received interrupt
        if(packetSemaphore == ISR_ACTION_REQUIRED) {

            // Read number of bytes in RX FIFO
            cc112xSpiReadReg(CC112X_NUM_RXBYTES, &rxBytes, 1);

            // Check that we have bytes in FIFO
            if(rxBytes != 0) {

                // Read MARCSTATE to check for RX FIFO error
                cc112xSpiReadReg(CC112X_MARCSTATE, &marcState, 1);

                // Mask out MARCSTATE bits and check if we have a RX FIFO error
                if((marcState & 0x1F) == RX_FIFO_ERROR) {

                    // Flush RX FIFO
                    trxSpiCmdStrobe(CC112X_SFRX);
                } else {

                    // Read n bytes from RX FIFO
                    cc112xSpiReadRxFifo(rxBuffer, rxBytes);

                    // Check CRC ok (CRC_OK: bit7 in second status byte)
                    // This assumes status bytes are appended in RX_FIFO
                    // (PKT_CFG1.APPEND_STATUS = 1)
                    // If CRC is disabled the CRC_OK field will read 1

                //    if(rxBuffer[rxBytes - 1] & 0x80) {

                        // Update packet counter
                        packetCounter++;
                  //  }
                }
            }

            // Update LCD
           // updateLcd();

            // Reset packet semaphore
            packetSemaphore = ISR_IDLE;

            // Set radio back in RX
            trxSpiCmdStrobe(CC112X_SRX);

            if( packetCounter==4)
            	packetCounter=0;
        }
    }
}


/*******************************************************************************
*   @fn         radioTxISR
*   @brief      ISR (Interrupt Service Routine) for packet handling in TX. Sets packet semaphore
*               and clears ISR flag
*   @param      none
*   @return     none
*/
static void radioTxISR(void) {

    // Set packet semaphore
    packetSemaphore = ISR_ACTION_REQUIRED;

    // Clear ISR flag
    ioPinIntClear(IO_PIN_PORT_1, GPIO2);
}


/*******************************************************************************
*   @fn         radioRxISR
*
*   @brief      ISR for packet handling in RX. Sets packet semaphore
*               and clears ISR flag
*
*   @param      none
*
*   @return     none
*/
static void radioRxISR(void) {

    // Set packet semaphore
    packetSemaphore = ISR_ACTION_REQUIRED;

    // Clear ISR flag
    ioPinIntClear(IO_PIN_PORT_1, GPIO2);
}


/*******************************************************************************
*   @fn         createPacket
*   @brief      This function is called before a packet is transmitted. It fills
*               the txBuffer with a packet consisting of a length byte, two
*               bytes packet counter and n random bytes.
*
*               The packet format is as follows:
*               |--------------------------------------------------------------|
*               |           |           |           |         |       |        |
*               | pktLength | pktCount1 | pktCount0 | rndData |.......| rndData|
*               |           |           |           |         |       |        |
*               |--------------------------------------------------------------|
*                txBuffer[0] txBuffer[1] txBuffer[2]            txBuffer[PKTLEN]
*
*   @param       Pointer to start of txBuffer
*   @return      none
*/
static void createPacket(uint8 txBuffer[]) {

    txBuffer[0] = PKTLEN;                           // Length byte
    txBuffer[1] = (uint8) (packetCounter >> 8);     // MSB of packetCounter
    txBuffer[2] = (uint8)  packetCounter;           // LSB of packetCounter

    uint8 i;
   /* for( i = 3; i <253; i++) {

       	   txBuffer[i] = 0xAA;
       }*/


    //uint8 i;
    // Fill rest of buffer with random bytes
    //for(i = 3; i < (PKTLEN + 1); i++) {
        //txBuffer[i] = (uint8)rand();
    	//txBuffer[i] = 0xAA;
    //}
    	txBuffer[3]=0x68;
    	txBuffer[4]=0x65;
    	txBuffer[5]=0x6c;
    	txBuffer[6]=0x6c;
    	txBuffer[7]=0x6f;
    	txBuffer[8]=0x20;
    	txBuffer[9]=0x46;
    	txBuffer[10]=0x6c;
    	txBuffer[11]=0x6f;
    	txBuffer[12]=0x72;
    	txBuffer[13]=0x69;
    	txBuffer[14]=0x70;
    	txBuffer[15]=0x61;
    	txBuffer[16]=0x53;
    	txBuffer[17]=0x61;
    	txBuffer[18]=0x74;



}




/*******************************************************************************
*   @fn         waitMs
*
*   @brief      Busy wait function. Waits the specified number of milliseconds.
*               Use assumptions about number of clock cycles needed for the
*               various instructions.
*
*               NB! This function is highly dependent on architecture and
*               compiler!
*
*   @param      uint16 mSec - number of milliseconds delay
*
*   @return     none
*/
#pragma optimize=none
static void waitMs(uint16 mSec) {
    while(mSec-- > 0) {
        waitUs(1000);
    }
}
/*******************************************************************************
*   @fn         waitUs
*   @brief      Busy wait function. Waits the specified number of microseconds.
*               Use assumptions about number of clock cycles needed for the
*               various instructions. The duration of one cycle depends on MCLK.
*               In this HAL it is set to 8 MHz, thus 8 cycles per us.
*
*               NB! This function is highly dependent on architecture
*               and compiler!
*
*   @param      uint16 uSec - number of microseconds delay
*   @return     none
*/
#pragma optimize=none
static void waitUs(uint16 uSec) { // 5 cycles for calling

    // The least we can wait is 3 usec:
    // ~1 usec for call, 1 for first compare and 1 for return
    while(uSec > 3) {  // 2 cycles for compare
                       // 2 cycles for jump
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        NOP();         // 1 cycle for nop
        uSec -= 2;     // 1 cycle for optimized decrement
    }
}                      // 4 cycles for returning





/*******************************************************************************
*   @fn         manualCalibration
*   @brief      Calibrates radio according to CC112x errata
*   @param      none
*   @return     none
*
*   [Julian]:	The ManualCalibration is suggested in "CC112x,CC1175 Silicon Errata" <http://www.ti.com/lit/er/swrz039d/swrz039d.pdf>
*/
#define VCDAC_START_OFFSET 2
#define FS_VCO2_INDEX 0
#define FS_VCO4_INDEX 1
#define FS_CHP_INDEX 2
static void manualCalibration(void) {

    uint8 original_fs_cal2;
    uint8 calResults_for_vcdac_start_high[3];
    uint8 calResults_for_vcdac_start_mid[3];
    uint8 marcstate;
    uint8 writeByte;

    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    writeByte = 0x00;
    cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);

    // 2) Start with high VCDAC (original VCDAC_START + 2):
    cc112xSpiReadReg(CC112X_FS_CAL2, &original_fs_cal2, 1);
    writeByte = original_fs_cal2 + VCDAC_START_OFFSET;
    cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);

    // 3) Calibrate and wait for calibration to be done
    //   (radio back in IDLE state)
    trxSpiCmdStrobe(CC112X_SCAL);

    do {
        cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
    } while (marcstate != 0x41);

    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with
    //    high VCDAC_START value
    cc112xSpiReadReg(CC112X_FS_VCO2,
                     &calResults_for_vcdac_start_high[FS_VCO2_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_VCO4,
                     &calResults_for_vcdac_start_high[FS_VCO4_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_CHP,
                     &calResults_for_vcdac_start_high[FS_CHP_INDEX], 1);

    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    writeByte = 0x00;
    cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);

    // 6) Continue with mid VCDAC (original VCDAC_START):
    writeByte = original_fs_cal2;
    cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);

    // 7) Calibrate and wait for calibration to be done
    //   (radio back in IDLE state)
    trxSpiCmdStrobe(CC112X_SCAL);

    do {
        cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
    } while (marcstate != 0x41);

    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained
    //    with mid VCDAC_START value
    cc112xSpiReadReg(CC112X_FS_VCO2,
                     &calResults_for_vcdac_start_mid[FS_VCO2_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_VCO4,
                     &calResults_for_vcdac_start_mid[FS_VCO4_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_CHP,
                     &calResults_for_vcdac_start_mid[FS_CHP_INDEX], 1);

    // 9) Write back highest FS_VCO2 and corresponding FS_VCO
    //    and FS_CHP result
    if (calResults_for_vcdac_start_high[FS_VCO2_INDEX] >
        calResults_for_vcdac_start_mid[FS_VCO2_INDEX]) {
        writeByte = calResults_for_vcdac_start_high[FS_VCO2_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_high[FS_VCO4_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_high[FS_CHP_INDEX];
        cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
    } else {
        writeByte = calResults_for_vcdac_start_mid[FS_VCO2_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_mid[FS_VCO4_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_mid[FS_CHP_INDEX];
        cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
    }
}
