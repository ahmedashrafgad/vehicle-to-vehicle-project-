/*
 * compass.c
 *
 * Created: 29/05/2018 05:17:17 م
 *  Author: DELL
 */ 
#include "compass.h"
#include <math.h>
#define PI	3.14159265359								/* Define Pi value */
#define Declination	0.07650359888   //tzbetha mnsba lmkna
/* Define declination of location from where measurement going to be done. e.g. here we have added declination from location Pune city,India. we can get it from http://www.magnetic-declination.com */

double Heading;
int COM ;
/* Magneto initialize function */
void Magneto_init()
{	
	I2C_Start(0x3C);									/* Start and write SLA+W */
	I2C_Write(0x00);									/* Write memory location address */
	I2C_Write(0x70);									/* Configure register A as 8-average, 15 Hz default, normal measurement */
	I2C_Write(0xA0);									/* Configure register B for gain */
	I2C_Write(0x00);									/* Configure continuous measurement mode in mode register */
	I2C_Stop();											/* Stop I2C */
}

int Magneto_GetHeading()
{
	int x, y, z;
	
	double Heading;
	I2C_Start_Wait(0x3C);								/* Start and wait for acknowledgment */
	I2C_Write(0x03);									/* Write X register address */
	I2C_Repeated_Start(0x3D);							/* Generate repeat start condition with SLA+R */
	/* Read 16 bit x,y,z value (2’s complement form) */
	x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();											/* Stop I2C */
	Heading = atan2((double)y,(double)x) + Declination;
	if (Heading>2*PI)									/* Due to declination check for >360 degree */
	Heading = Heading - 2*PI;
	if (Heading<0)										/* Check for sign */
	Heading = Heading + 2*PI;
	double Deg = (Heading* 180 / PI);
	return (Deg);							/* Convert into angle and return */
}

int compass_direction(int Deg)
{ 
	//double Deg = (Heading* 180 / PI);
	if ((0 <= Deg && Deg <= 20 )|| (340 <= Deg && Deg <= 360)) 
	{
		COM = north;
	}
  else if (160 <= Deg && Deg <= 200)
  {
	  COM = south;
  }
  else if ( 70 <= Deg && Deg <= 110)
  {
	  COM = east;
  }
  else if (250 <= Deg && Deg <= 290)
  {
	  COM = west;
  }
  else {
	 COM = non;
	  }
  return(COM);
}