/* EPS protocol file

This file contains all functions related to the creation of the data package to be sent to OBDH.

*/

#include "EPS_Definitions.h"


void write_data_package (void){

	SLV_Data[5] =  adc0_msb;
	SLV_Data[6] =  adc0_lsb;
	SLV_Data[7] =  adc1_msb;
	SLV_Data[8] =  adc1_lsb;
	SLV_Data[9] =  adc2_msb;
	SLV_Data[10] =  adc2_lsb;
	SLV_Data[11] =  adc3_msb;
	SLV_Data[12] =  adc3_lsb;
	SLV_Data[13] =  adc4_msb;
	SLV_Data[14] =  adc4_lsb;
	SLV_Data[15] =  adc5_msb;
	SLV_Data[16] =  adc5_lsb;
	SLV_Data[17] =  adc6_msb;
	SLV_Data[18] =  adc6_lsb;
	SLV_Data[19] =  adc7_msb;
	SLV_Data[20] =  adc7_lsb;
	SLV_Data[21] =  msp_ts_msb;
	SLV_Data[22] =  msp_ts_lsb;
	SLV_Data[27] =  avc_msb;
	SLV_Data[28] =  avc_lsb;
	SLV_Data[29] =  tr_msb;
	SLV_Data[30] =  tr_lsb;
	SLV_Data[31] =  vr_msb;
	SLV_Data[32] =  vr_lsb;
	SLV_Data[33] =  cr_msb;
	SLV_Data[34] =  cr_lsb;
	SLV_Data[35] =  acr_msb;
	SLV_Data[36] =  acr_lsb;
	SLV_Data[41] =  fault;
	SLV_Data[42] =  mppt_st;
	SLV_Data[43] =  reg_st;
	SLV_Data[44] =  crc;

}

