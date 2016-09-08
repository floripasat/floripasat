
VERSION: 0.7

Floripasat uG Mission 
Partial mission, to be tested under a micro-gravity enviroment by a rocket launch.

Keypoints:
- Language: C99
- Variables should use fixed length definitions (int16_t instead of int)
- times are in miliseconds (ms)
- Max_time should include some margin and consider worst case cenario.
- Item total time correspond to, at least, the sum of all subitems times, but not limited to it (may contain extra time in the parent function itself).
- Item times can be lower, since are calculated by worst case cenario.
- Debug message or extra functions should be accounted in the worst case cenario.

EXECUTION TIME TABLE
----------------------------------------------------------------------------------------------------------
TASK_ITEM	NORMAL_TIME		MAX_TIME	DESCRIPTION								

1										Boot Setup									
1.1										  OBDH Setup													
1.1.1									    MSP430 Internal Setup						
1.1.2										Watchdog Setup								
1.1.3 										Sysclock setup							
1.1.4										UART Setup								
1.1.5										I2C Setup								
1.1.5										SPI Setup								
1.1.5										Internal Flash Setup						
1.3										  Radio Setup									
1.4										  IMU Setup									
1.5										  Proceed to Task 2							


2			213				500			  Main Loop (continuous execution)			
2.1			0.5				250			  Read OBDH internal data (6 bytes)			
2.2			 31				250			  Read EPS data (23 bytes)					
2.3			  7				250			  Read IMU data (14 bytes)					
2.4			 92				250			  Read Radio data (5 bytes)					
2.5			  6				250			  Encode dataframe 							
2.6			 46				250			  Send dataframe to UART (uG host downlink)	
2.7			 32				250			  Save dataframe to internal flash			
2.8			285			   1000			  Sleep for X ms									
2.9										  Repeat Task 2 																		  	
										  	
3										Error State (hibernation)					NOT_IMPLEMENTED
3.1										  Log and transmit error messages			NOT_IMPLEMENTED	
3.2										  Hibernate									NOT_IMPLEMENTED
3.3 									  Periodic wakeup 							NOT_IMPLEMENTED
3.3.1									    Re-evaluate system conditions 			NOT_IMPLEMENTED

* MAX_TIME is the time slot for the task.
Currently there is no scheduler or task switching with context preserving. 
The system behavior must be deterministic within these limits. Any exceeded 
time is considered a general failure and incurs into a general reset, by 
the watchdog.  
----------------------------------------------------------------------------------------------------------




DATAFRAME FORMAT
----------------------------------------------------------------------------------------------------------

	// Frame sent to uG Host mission: 41 Bytes 
	// (uZed board adds an extra byte in the host side, indicating if it read the packet correclt formated). 
	// SOF (3B) + Payload (35B) + EOF (3B)
	// Ex: {{{BBB..BBB}\n\r
	// 7b 7b 7b 00 01 02 03 04  05 05 00 00 00 00 00 00 00 00 00 00 00 01 00 00 09 00 0d 01 02 03 04 05 06 07 08 09 0a 06 7d 0a 0d

	//Start of Frame
	ugFrame[0] = '{';				// 0x7B
	ugFrame[1] = '{';				// 0x7B
	ugFrame[2] = '{';				// 0x7B

	// Payload
	ugFrame[3]  = obdhData[0];		//Sysclock  S H
	ugFrame[4]  = obdhData[1];		//Sysclock  S L
	ugFrame[5]  = obdhData[2];		//Sysclock MS H
	ugFrame[6]  = obdhData[3];		//Sysclock MS L
	ugFrame[7]  = obdhData[4];		//Internal Temperature H
	ugFrame[8]  = obdhData[5];  	//Internal Temperature L
	ugFrame[9]  = obdhData[6];		//Status Code

	ugFrame[10] = imuData[0];		//Acc X H
	ugFrame[11] = imuData[1];		//Acc X L
	ugFrame[12] = imuData[2];		//Acc Y H
	ugFrame[13] = imuData[3];		//Acc Y L
	ugFrame[14] = imuData[4];		//Acc Z H
	ugFrame[15] = imuData[5];		//Acc Z L
	ugFrame[16] = imuData[8];		//Gyr X H
	ugFrame[17] = imuData[9];		//Gyr X L
	ugFrame[18] = imuData[10];		//Gyr Y H
	ugFrame[19] = imuData[11];		//Gyr Y L
	ugFrame[20] = imuData[12];		//Gyr Z H
	ugFrame[21] = imuData[13];		//Gyr Z L

	ugFrame[22] = radioData[0];		//Counter H
	ugFrame[23] = radioData[1];		//Counter L
	ugFrame[24] = radioData[2];		//Counter H
	ugFrame[25] = radioData[3];		//Counter L

	ugFrame[26] = epsData[3];		// Current H
	ugFrame[27] = epsData[4];		// Current L
	ugFrame[28] = epsData[5];		// Voltage BAT1 H
	ugFrame[29] = epsData[6];		// Voltage BAT1 L
	ugFrame[30] = epsData[7];		// Voltage BAT2 H
	ugFrame[31] = epsData[8];		// Voltage BAT2 L
	ugFrame[32] = epsData[9];		// Temperature  H
	ugFrame[33] = epsData[10];		// Temperature  L
	ugFrame[34] = epsData[11];		// Current Accum. H
	ugFrame[35] = epsData[12];		// Current Accum  L
	ugFrame[36] = epsData[13];		// Bat Mon. Protection Reg.

	// ugFrame[37] = CRC FIELD

	// End of Frame
	ugFrame[38] = '}';				// 0x7D
	ugFrame[39] = '\n';				// 0x0A
	ugFrame[40] = '\r';				// 0x0D





----------------------------------------------------------------------------------------------------------
 				MEMORY DUMP PROCEDURE 

**************************MAIN METHOD****************************

/////////////LINUX//////////////

1 - Download the MSP430Flasher from this link:

https://www.ti.com/licreg/productdownload.tsp?toPerform=productDownload&downloadPage=true&location=http%3A%2F%2Fdownloads.ti.com%2Fdownloads%2Fmsp430%2Fmsp430_public_sw%2Fmcu%2Fmsp430%2FMSP430Flasher%2Flatest%2FMSPFlasher-1_03_09_00-linux-x64-installer.zip%3F__gda__%3D1466373554_73d014e74e37264a1740b49626f42c99

2 - in the install folder, add write permission to the file, by typing the command below in the terminal:

chmod a+x MSPFlasher-1_03_09_00-linux-x64-installer.run

3 - then execute the following command to dump the whole memory(my need to rename the ouput file)

export LD_LIBRARY_PATH=. && ./MSP430Flasher -r [memory.dump.txt,0x00000-0xFFFFF]


////////////WINDOWS//////////////

1 - Download the MSP430Flasher from this link:

https://www.ti.com/licreg/productdownload.tsp?toPerform=productDownload&downloadPage=true&location=http%3A%2F%2Fdownloads.ti.com%2Fdownloads%2Fmsp430%2Fmsp430_public_sw%2Fmcu%2Fmsp430%2FMSP430Flasher%2Flatest%2FMSPFlasher-1_03_09_00-windows-installer.zip%3F__gda__%3D1466544358_3eb8138bc2696972963adf396dc00889

2 - extract, install it. In the install folder edit the msp430example.bat file to:

CLS
MSP430Flasher.exe -r [memory_dump_output_file.hex,0x00000-0xFFFFF]
PAUSE

3 - run the edited .bat file

*********************ALTERNATIVE METHODS****************************

Method 1: CCS

  1 - After the board recovery *****DO NOT START TO DEBUG***** otherwise
the memory will be erased!
  2 - Plug the board in the USB port, it should start blinking.
  3 - In the CCS, the tools bar, find the arrow \/ at the side of the 
debug button. Click  and select the "Debug Configurations...". A new window 
will open.
  4 - At the right side of the Window find the Program TAB.
  5 - In the loading options, mark the "Load Symbols Only", and click 
"Apply" and then "Debug". It will start the board and trap.
  6 - In the "View", Click "Memory Browser".
  7 - At the memmory browser window, click at the "Save memory" arrow
  8 - Select the file path (.dat) and hit next.
  9 - Select the 8 bit HEX TI Style, Start Adress = 0 and 
words to read = 0xfffff and hit finish.

Method 2: UNIFLASH

http://www.ti.com/tool/UniFlash

- Select Select TI MSP430 USB 1 as programmer
- Target: MSP430F6659
- Menu: Program -> Export Memory
- Format BIN
- Wordsize 8
- Start address 0
- length: 0x0fffff
- Export file: target file

