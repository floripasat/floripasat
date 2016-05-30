/*
 * codecs.h
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#ifndef UTIL_CODECS_H_
#define UTIL_CODECS_H_

#include <stdint.h>
#include "../hal/engmodel1.h"

#define DATAFRAME_LENGTH  35

#define SOF	0x7B		// '{' Start Of Frame
#define EOF	0x7D		// '}' End Of Frame

// Datastreams are initiated by 3 consecutives SOF, to minimize conflit with payloads of same value.
// TODO: implement a dynamic data encoding that always prevents conflit with SOF, deterministically.
//		 (eg. payload of conflicting value to be preceded by another special char)
// Termination is done by a EOF succeded by a \n\r for better formating in ascii debug environments.
// Example dataframe: {{{BBB}\n\r  , where BBB is a bytestream.


//char EPS_data_buffer[EPS_DATA_LENGTH];
//char BEACON_data_buffer[BEACON_DATA_LENGTH];
//char FSAT_frame[FSAT_FRAME_LENGTH];
//char misc_info_frame[MISC_INFO_LENGHT];


////debuf frames
//unsigned char Debug_FSAT_Frame[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
//									"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
//									"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
//									"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//TODO rm
//
//unsigned char Debug_EPS_Data[] = {"0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
//								  "0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00"};//TODO rm
//
//
//
//unsigned char Debug_BEACON_Data[] = {"0x00,0x00,0x00"};//TODO rm







char* dataframe2string 	   (char* frame);

#endif /* UTIL_CODECS_H_ */
