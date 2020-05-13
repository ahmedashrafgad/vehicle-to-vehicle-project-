/*
 * ATmega16_Magnetometer.c
 * http://www.electronicwings.com
 * 
 */ 

#define F_CPU 8000000UL									/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>										/* Include AVR std. library file */
#include <stdlib.h>										/* Include std. library file */
#include <math.h>										/* Include math header file */		
#include "I2C_Master_H_file.h"
#include "compass.h"
#include "usart.h"						               /* Include I2C header file */


int main(void)
{
	char buffer[10];
	I2C_Init();											/* Initialize I2C */
	Magneto_init();										/* Initialize magneto */
	uart_init(9600);
	
	while (1)
	{
		itoa (compass_direction(Magneto_GetHeading()),buffer,10);
		uart_SendString(buffer);
		uart_SendString("\n"); ///555
		_delay_ms(100);
	}
}
		