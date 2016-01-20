
## Minimalistic test to evaluate MCU hardware and programming setup.

### Hardware setup overview:

- Bare MCU (MSP430F6659), using internal oscilator. 
- LED connected to the P1.1 port (pin 35), with a series resistor. 
- Programmer connection.

#### Connected pins:

MCU Pin   		 |  Programmer Pin
---------------  | -----------------
63  DVSS2 (GND)  |  Programmer GND (Pin 9) 
64  DVCC2 (VCC)  |  Programmer 3v3 VCC_TOOL (Pin 2) 
91	TCK			 |  Programmer TCK (Pin 7)	
96	TDIO		 |  Programmer TDIO (Pin 1), with a pullup	
35	P1.1  (LED)  |  LED anode

Opcional: (Analog Bus - not needed for blink test)
11  AVCC1 (3v3)  |  Programmer 3v3 VCC_TOOL (Pin 2) 
12  AVSS1 (GND)  |  Programmer GND (Pin 9)  

Notes:
- Led catode is connected to ground with a 470Ohm resistor.
- MCU is powered by the programmer, without external power supply.
- Programming is done with JTAG simplified mode (only TDIO,TCK,VCC and GND are used).


### Software

Code composer studio 6.1.2.00015 / Ubuntu Linux 15.10 x64

Project setup: 
- File -> New -> CCS Project
- Select MSP430F6659 target
- Blank Project with main.c
- insert the content of the main.c in this folder.
- build all
- debug
- debug play
