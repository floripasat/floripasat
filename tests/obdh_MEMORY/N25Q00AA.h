/*
 * N25Q00AA.h
 *
 *  Created on: 21/04/2016
 *      Author: Frata
 */

#ifndef _N25Q00AA_H_
#define _N25Q00AA_H_

//auxiliar defines

#define FloripaSatFrameSize 26								//frame size

//COMMANDS OF THE MEMORY

// reset operations
#define ResetEnable 								0x66
#define ResetMemory 								0x99

// identification operations
#define	ReadId 										0x9E
#define	MultipleIOReadId 							0xAF
#define	ReadSerialFlashDiscoveryParameter 			0x5A

// read operations
#define Read 										0x03
#define FastRead 									0x0B
#define DualOutputFastRead 							0x3B
#define DualInputOutputFastRead 					0x0B
#define QuadOutputFastRead 							0x6B
#define QuadInputOutputFastRead 					0x0B
#define FastReadDTR 								0x0D
#define DualOutputFastReadDTR 						0x3D
#define DualInputOutputFastReadDTR 					0x0D
#define QuadOutputFastReadDTR 						0x6D
#define QuadInputOutputFastReadDTR 					0x0D
#define FourByteRead 								0x13
#define FourByteFastRead 							0x0C
#define FourByteDualOutputFastRead 					0x3C
#define FourByteDualInputOutputFastRead 			0xBC
#define FourByteQuadOutputFastRead 					0x6C
#define FourByteQuadInputOutputFastRead 			0xEC

// write operation
#define WriteEnable 								0x06
#define WriteDisable 								0x04

// register operation
#define ReadStatusRegister 							0x05
#define WriteStatusRegister 						0x01
#define ReadLockRegister 							0xE8
#define WriteLockRegister 							0xE5
#define ReadFlagStatusRegister 						0x70
#define ClearFlagStatusRegister 					0x50
#define ReadNonvolatileConfigurationRegister 		0xB5
#define WriteNonvolatileConfigurationRegister 		0xB1
#define ReadVolatileConfigurationRegister 			0x85
#define WriteVolatileConfigurationRegister 			0x81
#define ReadEnhancedVolatileConfigurationRegister 	0x65
#define WriteEnhancedVolatileConfigurationRegister 	0x61
#define ReadExtendedAddressRegister 				0xC8
#define WriteExtendedAddressRegister 				0xC5

// program operations
#define PageProgram 								0x02
#define DualInputFastProgram 						0xA2
#define ExtendedDualInputFastProgram 				0x02
#define QuadInputFastProgram 						0x32
#define ExtendedQuadInputFastProgram 				0x02

// erase operations
#define SubsectorErase 								0x20
#define SectorErase 								0xD8
#define DieErase 									0xC4
#define ProgramEraseResume 							0x7A
#define ProgramEraseSuspend 						0x75

// one time programmable (otp) operations
#define ReadOTPArray 								0x4B
#define ProgramOTPArray 							0x42

// 4-byte address mode operations
#define Enter4ByteAddressMode 						0xB7
#define Exit4ByteAddressMode 						0xE9

//variables

unsigned long memory_adress;								//memory adress

// FUNCTIONS

// reset operations
void _ResetEnable(void);
void _ResetMemory(void);
// identification operations
void _ReadId(void);
void _MultipleIOReadId(void);
void _ReadSerialFlashDiscoveryParameter(void);
// read operations
void _Read(unsigned long startAdress, unsigned char Buffer[], int bytes);
void _FastRead(void);
void _DualOutputFastRead(void);
void _DualInputOutputFastRead(void);
void _QuadOutputFastRead(void);
void _QuadInputOutputFastRead(void);
void _FastReadDTR(void);
void _DualOutputFastReadDTR(void);
void _DualInputOutputFastReadDTR(void);
void _QuadOutputFastReadDTR(void);
void _QuadInputOutputFastReadDTR(void);
void _4ByteRead(void);
void _4ByteFastRead(void);
void _4ByteDualOutputFastRead(void);
void _4ByteDualInputOutputFastRead(void);
void _4ByteQuadOutputFastRead(void);
void _4ByteQuadInputOutputFastRead(void);
// write operation
void _WriteEnable(void);
void _WriteDisable(void);
// register operation
void _ReadStatusRegister(void);
void _WriteStatusRegister(void);
void _ReadLockRegister(void);
void _WriteLockRegister(void);
void _ReadFlagStatusRegister(void);
void _ClearFlagStatusRegister(void);
void _ReadNonvolatileConfigurationRegister(void);
void _WriteNonvolatileConfigurationRegister(void);
void _ReadVolatileConfigurationRegister(void);
void _WriteVolatileConfigurationRegister(void);
void _ReadEnhancedVolatileConfigurationRegister(void);
void _WriteEnhancedVolatileConfigurationRegister(void);
void _ReadExtendedAddressRegister(void);
void _WriteExtendedAddressRegister(void);
// program operations
void _PageProgram(unsigned long startAdress, unsigned char *Data);
void _DualInputFastProgram(void);
void _ExtendedDualInputFastProgram(void);
void _QuadInputFastProgram(void);
void _ExtendedQuadInputFastProgram(void);
// erase operations
void _SubsectorErase(void);
void _SectorErase(void);
void _DieErase(void);
void _ProgramEraseResume(void);
void _ProgramEraseSuspend(void);
// one time programmable (otp) operations
void _ReadOTPArray(void);
void _ProgramOTPArray(void);
// 4-byte address mode operations
void _Enter4ByteAddressMode(void);
void _Exit4ByteAddressMode(void);


#endif /* N25Q00AA_H_ */
