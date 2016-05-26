
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

2										Main Loop (continuous execution)			NOT_IMPLEMENTED
										  Read OBDH internal data (? bytes)			NOT_IMPLEMENTED
										  Read EPS data (18 bytes)					NOT_IMPLEMENTED
										  Read Radio data (5 bytes)					NOT_IMPLEMENTED
										  Read IMU data (12 bytes)					NOT_IMPLEMENTED
										  Encode dataframe 							NOT_IMPLEMENTED
										  Save dataframe to internal flash			NOT_IMPLEMENTED
										  Send dataframe to UART (uG host downlink)	NOT_IMPLEMENTED
										  	
3										Error State (hibernation)					NOT_IMPLEMENTED
3.1										  Log and transmit error messages			NOT_IMPLEMENTED	
3.2										  Hibernate									NOT_IMPLEMENTED
3.2.1									    Periodic wakeup							NOT_IMPLEMENTED

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




