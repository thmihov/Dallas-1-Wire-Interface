# Dallas-1-Wire-Interface
AVR-GCC library which implements basic 1-Wire interface functions,needed for comunicating with other devices.
The library is for the MASTER device,slave is not implemented.
The lbrary contain routines for:
<ul>
	<li>-Setting DQ line low - OW_LOW()</li>
<li>-Setting DQ at IDLE state - OW_IDLE()</li>
<li>-Send "Write 0" command - OW_WR0()</li>
<li>-Send "Write 1" command - OW_WR1()</li>
<li>-Send "RESET" command - OW_RESET()</li>
<li>-Read single bit from the slave - OW_READB()</li>
<li>-Read single byte from the slave - OW_READBYTE()</li>
<li>-Write single byte to the slave - OW_WRITE()</li>
</ul>
For detailed description of the signals and the protocol,see Atmel's AVR318: Dallas 1-Wire Master on tinyAVR and
megaAVR.
The timings and time-slot lenghts could be different for some devices,so first read device's datasheet and change values if needed.

Tested and working with DS18S20 and DS18B20 temperature sensors.
