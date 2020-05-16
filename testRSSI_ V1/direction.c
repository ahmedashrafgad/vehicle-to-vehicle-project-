/*
 * direction.c
 *
 * Created: 12/10/2017 03:24:32 ص
 *  Author: DELL
 * 
 */ 
#include <avr/io.h>
#include "direction.h"
#include "usart_driver.h"
#include "Ultrasonic.h"
movement direction = stop ;
unsigned char stoped = 1 ;
unsigned long overflowstimes = 0 ;
speed control = slow;
unsigned char slowed = 1 ;
char sp=0;
 

unsigned char buffer[50] ;


void CarControlInit(void)
{
	DDRC |= (1 << PINC2) | (1 << PINC3)| (1 << PINC4)| (1 << PINC5); /* for two motors output */
	PORTC |= (1 << PINC2) | (1 << PINC3)| (1 << PINC4)| (1 << PINC5) ; /* set all portC motor pins */
	US_Init();
	 // portc0,1 analog input 
}

void moveCar(movement direction)
{
	switch(direction)
	{
		/* time is in ms */
		case forword:
		clearBit(PORTC,5);
		clearBit(PORTC,3);
		stoped = 0;
		//usart0_puts("forword");
		//usart0_puts("F\n");
		startDelayTimer(sp);
		break;
		case backword :
		clearBit(PORTC,4);
		clearBit(PORTC,2);
		stoped = 0;
		//usart0_puts("B\n");
		startDelayTimer(sp);
		break;
		case right :
		clearBit(PORTC,3);
		stoped = 0;
		//usart0_puts("R\n");
		startDelayTimer(sp);
		break;
		case left :
		clearBit(PORTC,5);
		stoped = 0;
		//usart0_puts("L\n");
		startDelayTimer(sp);
		break;
		case stop:
		if (!stoped)
		{
			setBit(PORTC,5);
			setBit(PORTC,4);
			setBit(PORTC,3);
			setBit(PORTC,2);
			startDelayTimer(50);
			stoped =1 ;
			//usart0_puts("S0\n");
		}
		break;
	}
}

void startDelayTimer (unsigned int time)
{
	overflowstimes = (unsigned long)(3.906 * time) ;  // 3906 for 1ms delay
	setBit(TCCR2B,CS21); // 8 Prescaler
	setBit(TIMSK2,TOIE2); // enable overflow interrupt
	sei();
}

ISR(TIMER2_OVF_vect)
{
	overflowstimes -- ;
	if (overflowstimes == 0) // time for one second
	{
		moveCar(stop);
		
		TCCR2B = 0x00 ;  //stop timer counting
	}
}
void speed_car(speed control){
	switch(control)
	{ 
		case slow :
		sp =30;
		break;
		
		case moderate :
		sp=60;
		break;
		
		case fast :
		sp=80;
		break;
		
		
		case veryfast :
		sp=100;
		break;
		
		
	}
}

void setDirection(void)
{   unsigned char distance = US_getDistance() ;
	
	
	   usart0_puts("\n") ;
	   snprintf(buffer,50,"%d",distance);
	   usart0_puts(buffer) ;
	   usart0_puts("\n") ;
	   
	if (distance <= 15)
	{
		usart0_puts("in IF \n") ;
		moveCar(stop) ;
	unsigned int xValue  = 0, yValue = 0 ;

	yValue =  adc_readADC1();
	xValue = adc_readADC0();
	
		
		if (xValue > 614 && xValue <= 716)
		{
			speed_car(slow);
			moveCar(left);
			usart0_puts("sl\n");
		}
		else if (xValue > 716 && xValue <= 819)
		{
			speed_car(moderate);
			moveCar(left);
			usart0_puts("ml\n");
		}
		else if (xValue >819 && xValue <= 921)
		{
			speed_car(fast);
			moveCar(left);
			usart0_puts("fl\n");
		}
		else if (xValue > 921 && xValue <= 1023)
		{
			speed_car(veryfast);
			moveCar(left);
			usart0_puts("vl\n");
		}
		else if ( xValue >= 307 && xValue < 409 )
		{
			speed_car(slow);
			moveCar(right);
			usart0_puts("sr\n");
		}
		else if (xValue >= 204  && xValue < 307)
		{
			speed_car(moderate);
			moveCar(right);
			usart0_puts("mr\n");
		}
		else if ( xValue >= 102 && xValue < 204)
		{
			speed_car(fast);
			moveCar(right);
			usart0_puts("fr\n");
		}
		else if ( xValue >= 0 && xValue < 102)
		{
			speed_car(veryfast);
			moveCar(right);
			usart0_puts("vr\n");
		}
		else
		{
			moveCar(stop);
			usart0_puts("s\n");
		}
		
		 if ( yValue >= 307 && yValue < 409 )
		{
			speed_car(slow);
			moveCar(backword);
			usart0_puts("sb\n");
		}
		else if (yValue >= 204 && yValue < 307)
		{
			speed_car(moderate);
			moveCar(backword);
			usart0_puts("mb\n");
		}
		else if ( yValue >= 102 && yValue < 204)
		{
			speed_car(fast);
			moveCar(backword);
			usart0_puts("fb\n");
		}
		else if ( yValue >= 0 && yValue < 102)
		{
			speed_car(veryfast);
			moveCar(backword);
			usart0_puts("vb\n");
		}
		else
		{
			moveCar(stop);
			usart0_puts("s\n");
			
		}
	}
	else
	{
		usart0_puts("\nin else \n") ;
	unsigned int xValue  = 0, yValue = 0 ;

	yValue =  adc_readADC1();
	xValue = adc_readADC0();
	snprintf(buffer,50,"%d",xValue);
	usart0_puts(buffer);
	usart0_puts(" y= ");
	snprintf(buffer,50,"%d",yValue);
	usart0_puts(buffer);
	usart0_putc('\n');
	
	if (xValue > 614 && xValue <= 716)
	{
		speed_car(slow);
		moveCar(left);
		usart0_puts("sl\n");
	}
	else if (xValue > 716 && xValue <= 819)
	{
		speed_car(moderate);
		moveCar(left);
		usart0_puts("ml\n");	
	}
	else if (xValue >819 && xValue <= 921)
	{
		speed_car(fast);
		moveCar(left);
		usart0_puts("fl\n");
	}
	else if (xValue > 921 && xValue <= 1023)
	{
		speed_car(veryfast);
		moveCar(left);
		usart0_puts("vl\n");
	}
	else if ( xValue >= 307 && xValue < 409 )
	{
		speed_car(slow);
		moveCar(right);
		usart0_puts("sr\n");
	}
	else if (xValue >= 204  && xValue < 307)
	{
		speed_car(moderate);
		moveCar(right);
		usart0_puts("mr\n");
	}
	else if ( xValue >= 102 && xValue < 204)
	{
		speed_car(fast);
		moveCar(right);
		usart0_puts("fr\n");
	}
	else if ( xValue >= 0 && xValue < 102)
	{
		speed_car(veryfast);
		moveCar(right);
		usart0_puts("vr\n");
	}
	else
	{
		moveCar(stop);
		usart0_puts("s\n");
	}
	
 
   if (yValue > 614 && yValue <= 716)
  {
	speed_car(slow);
	moveCar(forword);
	usart0_puts("sf\n");
  }
  else if (yValue > 716 && yValue <= 819)
  {
	speed_car(moderate);
	moveCar(forword);
	usart0_puts("mf\n");
  }
  else if (yValue > 819 && yValue <= 921)
  {
	speed_car(fast);
	moveCar(forword);
	usart0_puts("ff\n");
  }
  else if (yValue > 921 && yValue <= 1023)
  {
	speed_car(veryfast);
	moveCar(forword);
	usart0_puts("vf\n");
  }
  else if ( yValue >= 307 && yValue < 409 )
  {
	speed_car(slow);
	moveCar(backword);
	usart0_puts("sb\n");
  }
else if (yValue >= 204 && yValue < 307)
{
	speed_car(moderate);
	moveCar(backword);
	usart0_puts("mb\n");
}
else if ( yValue >= 102 && yValue < 204)
{
	speed_car(fast);
	moveCar(backword);
	usart0_puts("fb\n");
}
else if ( yValue >= 0 && yValue < 102)
{
	speed_car(veryfast);
	moveCar(backword);
	usart0_puts("vb\n");
}
else
{
	moveCar(stop);
	usart0_puts("s\n");
	
}
}
}
