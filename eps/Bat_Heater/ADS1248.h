/*
 * ADS1248.h
 *
 *  Created on: 08/06/2016
 *      Author: Bruno Eiterer
 */

#ifndef ADS1248_H_
#define ADS1248_H_

/**** COMMANDS ****/

#define RESET_command 0x06				// reset command
#define RDATA_command 0x12				// command to read conversion data once
#define SDATAC_command 0x16				// stop read data continous mode command
#define RDATAC_command 0x14				// read data continous mode command
#define WREG_command 0x40				// write to register command
#define RREG_command 0x20				// read from register command
#define NOP_command 0xff				// no operation command, used to clock out data
#define SYNC_command 0x04				// command to start ADC conversion

/**** REGISTERS ****/

#define MUX0_register 0x00						// multiplexer control register 0
#define VBIAS_register 0x01						// bias voltage register
#define MUX1_register 0x02						// multiplexer control register 1
#define SYS0_register 0x03						// system control register 0


void config_ADS1248(int channel);
void read_ADS1248(int channel);

#endif /* ADS1248_H_ */
