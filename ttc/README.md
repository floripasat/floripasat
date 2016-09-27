# FloripaSat - TTC
## Telemetry, Tracking and Command (TT&amp;C) module of the FloripaSat project

This module is divided in two submodules:
* Beacon
* Transceiver

The software of the transceiver submodule is under development in the OBDH module, and for now is not described in this page.

## Implementation

Main characteristics of the beacon submodule:
* Language: C
* The MCU used in this module is the [MSP430F6659](http://www.ti.com/product/MSP430F6659).
* As transmitter, the [CC1175](http://www.ti.com/product/CC1175) IC is used.
* All MCU peripherals are controlled with the ["MSP Driver Library"](http://www.ti.com/tool/mspdriverlib) library, also know as ["DriverLib"](http://www.ti.com/tool/mspdriverlib).
* All software was developed in the [Code Composer Studio IDE](http://www.ti.com/tool/ccstudio) (version 6.1.3).

[//]: # (## Block diagram (Software)

Block diagram (in the perspecptive of the software, and not actually the real hardware )

[beacon-bd](doc/block-diagram.png)> )

## CC1175 configuration

For the CC1175 configuration, the [SmartRF Studio](http://www.ti.com/tool/smartrftm-studio) software was used, with the follow configuration:
* Carrier frquency = 437,5 MHz
* XTAL frequency = 32 MHz
* Symbol rate = 1,2 ksps
* Deviation = 3,997803 (~= 4)
* Modulation = 2-GFSK
* RX filter bandwidth = 12,5 kHz
* TX power = 15 dBm

## Beacon operation

The step-by-step operation of the beacon is described bellow:

1. Watchdog initialization
2. SPI and UART initiazation
3. CC1175 configuration (with the data obtained from SmartRF Studio)
4. CC1175 calibration (In agree with ["CC112X, CC1175 Silicon Errata"](http://www.ti.com/lit/er/swrz039d/swrz039d.pdf))
5. RF switch selection (beacon transmition)
6. RF power amplifier (PA) activation by setting the gain
8. Test message transmition ("FloripaSat")

### Debug mode

There is also a debug mode (turned on/off with the DEBUG\_MODE macro in the main file), where all software execution is described through the UART port. Example of output: [Log file](https://github.com/mgm8/floripasat-ttc/blob/master/beacon/log/beacon_tx.log).

The debug mode can be used with a UART-USB converter (FTDI chip for example) with the follow configuration:
* Baudrate = 115200 bps
* Data bits = 8
* Parity bit = None
* Stop bits = 1

As a serial port monitor, the following softwares can be used:
* Linux: [CuteCom](http://cutecom.sourceforge.net/)
* Windows: [PuTTY](http://www.putty.org/)

## References

The general documentation of the project can be found in [GitBook](https://www.gitbook.com/book/tuliogomesp/floripasat-technical-manual).

All source code of the project can be found in [GitHub](https://github.com/mariobaldini/floripasat).

Doxygen documentation [here](http://fsat-server.duckdns.org:8000/ttc/).

The official website of the project is [www.floripasat.ufsc.br](http://www.floripasat.ufsc.br/).
