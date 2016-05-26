/*
 * codecs.h
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */

#ifndef UTIL_CODECS_H_
#define UTIL_CODECS_H_

#define DATAFRAME_LENGTH  35



void dataframe_encode_obdh (char* frame, int a, int b);
void dataframe_encode_radio(char* frame, int a, int b);
void dataframe_encode_eps  (char* frame, int a, int b);
void dataframe_encode_imu  (char* frame, int a, int b);

char* dataframe2string 	   (char* frame);

#endif /* UTIL_CODECS_H_ */
