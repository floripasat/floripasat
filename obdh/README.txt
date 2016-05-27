
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


2										Main Loop (continuous execution)			NOT_IMPLEMENTED
2.1										  Read OBDH internal data (? bytes)			NOT_IMPLEMENTED
2.2										  Read EPS data (18 bytes)					NOT_IMPLEMENTED
2.3										  Read Radio data (5 bytes)					NOT_IMPLEMENTED
2.4										  Read IMU data (14 bytes)					NOT_IMPLEMENTED
2.5										  Encode dataframe 							NOT_IMPLEMENTED
2.6										  Save dataframe to internal flash			NOT_IMPLEMENTED
2.7										  Send dataframe to UART (uG host downlink)	NOT_IMPLEMENTED
2.8										  Sleep for X ms							NOT_IMPLEMENTED		
2.9										  Repeat Task 2 							NOT_IMPLEMENTED											  	
										  	
3										Error State (hibernation)					NOT_IMPLEMENTED
3.1										  Log and transmit error messages			NOT_IMPLEMENTED	
3.2										  Hibernate									NOT_IMPLEMENTED
3.3 									  Periodic wakeup 							NOT_IMPLEMENTED
3.3.1									    Re-evaluate system conditions 			NOT_IMPLEMENTED
----------------------------------------------------------------------------------------------------------


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




