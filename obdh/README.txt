
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

1										Boot Setup									NOT_IMPLEMENTED
1.1										  OBDH Setup								NOT_IMPLEMENTED					
1.1.1									    MSP430 Internal Setup					NOT_IMPLEMENTED	
1.1.2										Watchdog Setup							NOT_IMPLEMENTED	
1.1.3 										Sysclock setup							NOT_IMPLEMENTED
1.1.4										UART Setup								NOT_IMPLEMENTED
1.1.5										I2C Setup								NOT_IMPLEMENTED
1.1.5										SPI Setup								NOT_IMPLEMENTED
1.1.5										Internal Flash Setup					NOT_IMPLEMENTED	
1.3										  Radio Setup								NOT_IMPLEMENTED	
1.4										  IMU Setup									NOT_IMPLEMENTED
1.5										  Proceed to Task 2							NOT_IMPLEMENTED


2			500				500			Main Loop (continuous execution)			NOT_IMPLEMENTED
2.1							10			  Read OBDH internal data (? bytes)			NOT_IMPLEMENTED
2.2							100			  Read EPS data (18 bytes)					NOT_IMPLEMENTED
2.3							10			  Read IMU data (14 bytes)					NOT_IMPLEMENTED
2.4							50			  Read Radio data (5 bytes)					NOT_IMPLEMENTED
2.5							10			  Encode dataframe 							NOT_IMPLEMENTED
2.6							50			  Save dataframe to internal flash			NOT_IMPLEMENTED
2.7			46				50			  Send dataframe to UART (uG host downlink)	NOT_IMPLEMENTED
2.8							180			  Sleep for X ms							NOT_IMPLEMENTED		
2.9										  Repeat Task 2 							NOT_IMPLEMENTED											  	
										  	
3										Error State (hibernation)					NOT_IMPLEMENTED
3.1										  Log and transmit error messages			NOT_IMPLEMENTED	
3.2										  Hibernate									NOT_IMPLEMENTED
3.3 									  Periodic wakeup 							NOT_IMPLEMENTED
3.3.1									    Re-evaluate system conditions 			NOT_IMPLEMENTED
----------------------------------------------------------------------------------------------------------

TIME SLOTS
----------------------------------------------------------------------------------------------------------

ms		Task







DATAFRAME FORMAT
----------------------------------------------------------------------------------------------------------

////////////////////frame///////////////////////////
[START BYTE][EPS DATA][BEACON DATA][IMU DATA][CRC][END BYTE]
/////////////frame to save into flash///////////////
[RTC_TIME][EPS DATA][BEACON DATA][IMU DATA]

----------------------------------------------------------------------------------------------------------



MEASUREMENTS 
----------------------------------------------------------------------------------------------------------
OBDH INTERNAL
Main cycle counter		



EPS
17 bytes


RADIO



IMU


----------------------------------------------------------------------------------------------------------
 				MEMORY DUMP PROCEDURE 

  This is the guide for the memory dump of the uG mission of the OBDH 
memory.

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
words to read = 0xffffff and hit finish.

Method 2:
Using TI UniFlash software
http://www.ti.com/tool/UniFlash

- Select Select TI MSP430 USB 1 as programmer
- Target: MSP430F6659
- Menu: Program -> Export Memory
- Format BIN
- Wordsize 8
- Start address 0
- length: 0x0fffff
- Export file: target file

