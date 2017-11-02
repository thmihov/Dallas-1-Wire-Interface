/**************************************************/
/* Some low level functions,like pulling line low */
/* setting line high (idle state),Write 1,Write 0 */
/* reading single bit,reading single byte         */
/* writing single byte and etc.                   */
/**************************************************/

#include "OW_Port_Def.h"
#include <avr/io.h>
#include <util/delay.h>

/**************************************************/
/*Pulls DQ line low */
/**************************************************/

void OW_LOW()
{
	DQDDR |=(1<<DQPIN);	//Sets the DQ pin as output
	DQPORT&=~(1<<DQPIN);	//Sets the DQ pin low

}

/**************************************************/
/*      Sets DQ line at idle state (high)*/
/**************************************************/

void OW_IDLE()
{
	DQDDR &=~(1<<DQPIN);	//Sets the DQ pin as input.Because of the external  pull-up resistor,this puts the DQ line high (idle)
}


/**************************************************/
/* Write 1 time slot */
/* Pull DQ low,wait 1us (1-15us) and release. */
/* Wait another 60us because the time slot cannot be less than 60us -> Tlow+Tidle >= 60us */
/**************************************************/
	
void OW_WR1()
{
	OW_LOW();	//Pull DQ low
	_delay_us(6);	//Wait 1 us
	OW_IDLE();	//Release DQ
	_delay_us(64);	//Wait 60us
}


/**************************************************/
/* Write 0 time slot */
/* Pull DQ low,wait min 60us (one time slot) and release */
/* Wait another 2us because the time slot cannot be less than 60us ->Tlow+Tidle >= 60us */
/**************************************************/

void OW_WR0()
{
	OW_LOW();	//Pull DQ low
	_delay_us(60);	//Wait 60us
	OW_IDLE();	//Release DQ
	_delay_us(10);	//Wait 2us
}

/**************************************************/
/* Read single bit from slave*/
/* Pull DQ low,wait min. 1us than relese.Wait 15uS and read the result.*/
/* Wait about 40us (min. time slot is 60uS) to complete the time slot */
/**************************************************/

unsigned char OW_READB()
{
	unsigned char res=0;	//Result var
	OW_LOW();	//Pull DQ low
	_delay_us(6);	//Wait 5us
	OW_IDLE();	//Release
	_delay_us(9);	//Wait 15us
	
	if (!(PINB&(1<<0)))	//Read line
	{
		res=0;	//Slave sends 0
	}
	else
	{
		res=1;	//Slave sends 1
	}
	_delay_us(55);	//Wait 40us to complete the minimum time slot
	return res;

}


/**************************************************/
/*Read single byte from slave*/
/*Calls 8 times OW_READB(),stores the results in array */
/*and converts it into single byte */
/**************************************************/

unsigned char OW_READBYTE()
{
	 unsigned char i=0;	//counter var
	 unsigned char tarr[8];	//array for storing bits
	 unsigned char data=0;	//final hex value after shifting array elements
	 while (i<8)	//8 times read 1bit and store it in the array
	 {
	 	tarr[i]=OW_READB();	//read 1 bit
		i++;
	 }
	 i=0;
	 while(i<8)	//convert the array to single byte
	 {
	 	if (tarr[i])
		{
			data+=(1<<i);
		}
		i++;
	 }
		return data;
}

/**************************************************/
/* Write single byte to the slave*/
/* Check every bit of the number and calls the corresponding function-Write 1 ot Write 0 */
/**************************************************/

void OW_WRITE(unsigned char data)
{
	unsigned char i=0;	//Counter var
	unsigned char res;	//Result var
	while (i<8)	//do 8 times
	{
	res=(data&(1<<0));
	if (res==1)	//if current bit is 1,call "write 1" function
	OW_WR1();
	if (res==0)	//if current bit is 0,call "write 0" function
	OW_WR0();
	data=data>>1;	//shift for the next bit
	i++;
	}
}

/**************************************************/
/* Reset condition */
/* Pull DQ low for min.480uS,than release it.Wait 60us (15-60uS) and then read the DQ line. */
/* If the line is low,than there is at least one device (return 1) */
/* if the line is high there is no device or there is malfunction - short circuit or so (return 0)*/
/**************************************************/

unsigned char OW_RESET()
{
	unsigned char res=0; //Variable for the result
	OW_LOW();	//Pull the line LOW
	_delay_us(480);	//Wait 480us
	OW_IDLE();	//Release the line
	_delay_us(70);	//WAit 60uS
	if (!(DQIN&(1<<DQPIN)))	//Read the line
	{
		res=1;	//If the line is low,there is a device (return 1)
	}
	else
	{
		res=0;	//If the line is high trehe is no device (return 0)
	}
	_delay_us(410);	//Wait (datasheet)
	return res;
}
