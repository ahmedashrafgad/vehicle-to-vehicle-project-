/*
 * CarController.c
 *
 * Created: 1/2/2018 5:24:43 PM
 * Author : shaker
 */ 

#define F_CPU	8000000UL
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "direction.h"
#include "usart.h"

#define Forward_Led		PIND3
#define Backward_Led	PIND4
#define Buzzer			PIND5

unsigned char data ;
double dutyCycle = 0;
double Range;


int main(void)
{   DDRD |= (1<<PIND2)|(1<<PIND3)|(1<<Forward_Led)|(1<<Backward_Led);
	PORTD &= ~((1<<PIND2)|(1<<PIND3)|(1<<Forward_Led)|(1<<Backward_Led));
	
	
	//char string[10];
	ultrasonicIinit();
	CarControlInit();
	uart_init(9600);
	speedControl(dutyCycle);
	//sei();
	
	while(1)
	{
			 data = uart_Receive();
			 Range = 30;
			 setDirection();
	  
    }
    return 0;
}