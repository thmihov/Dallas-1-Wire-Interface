# Dallas-1-Wire-Interface
AVR-GCC library which implements basic 1-Wire interface functions,needed for comunicating with other devices.
The library is for the MASTER device,slave is not implemented.
The lbrary contain routines for:
-Setting DQ line low - OW_LOW()
-Setting DQ at IDLE state - OW_IDLE()
-Send "Write 0" command - OW_WR0()
-Send "Write 1" command - OW_WR1()
-Send "RESET" command - OW_RESET()
-Read single bit from the slave - OW_READB()
-Read single byte from the slave - OW_READBYTE()
-Write single byte to the slave - OW_WRITE()

For detailed description of the signals and the protocol,see Atmel's AVR318: Dallas 1-Wire Master on tinyAVR and
megaAVR.
The timings and time-slot lenghts could be different for some devices,so first read device's datasheet and change values if needed.

Tested and working with DS18S20 and DS18B20 temperature sensors.
