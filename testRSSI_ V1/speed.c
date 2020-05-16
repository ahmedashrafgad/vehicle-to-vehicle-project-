/*
 * speed.c
 *
 * Created: 12/10/2017 04:11:53 ص
 *  Author: DELL
 */ 
#include "speed.h"
speed car = slow;
unsigned char slowed = 1 ;

void speed_contr(speed car){
	switch(car)
	{ case slow :
		PORTC|=((1<<PINC2)|(1<<PINC4));
		_delay_ms(3);
		PORTC &=~((1<<PINC2)|(1<<PINC4));
		_delay_ms(5);
		break;
		
		case moderate :
		PORTC|=((1<<PINC2)|(1<<PINC4));
		_delay_ms(5);
		PORTC &=~((1<<PINC2)|(1<<PINC4));
		_delay_ms(5);
		break;
		
		case fast :
		PORTC|=((1<<PINC2)|(1<<PINC4));
		_delay_ms(7);
		PORTC &=~((1<<PINC2)|(1<<PINC4));
		_delay_ms(5);
		break;
	}
}