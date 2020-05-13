/*
 * direction.c
 *
 * Created: 02/06/2018 09:23:13 م
 *  Author: DELL
 */ 
#include "direction.h"
#include "usart.h"
#define Forward_Led		PIND3
#define Backward_Led	PIND4
#define Buzzer			PIND5

movement direction = stop ;

//double dutyCycle = 0;
//-----for Ultrasonic----
int TimerOverflow = 0;
long count;
double distance;
double Range;
unsigned char data ;


void CarControlInit(void)
{
	DDRC  |= (1 << PINC2) | (1 << PINC3)| (1 << PINC4); /* for two motors output */
	PORTC &= ~((1 << PINC2) | (1 << PINC3)| (1 << PINC4));  /* set all portC motor pins */
	DDRB |= (1<<IN1);
	PORTB &=~ (1<<IN1);
	PORTC |= (1<<ENA)|(1<<ENB);
}
void speedControl(double duty_Cycle)
{
	DDRD = (1<<PIND6);
	TCCR0A = (1<<COM0A1)|(1<<WGM00)|(1<<WGM01);
	TIMSK0 = (1<<TOIE0);
	OCR0A = (duty_Cycle/100.0)*255.0;
	
	//sei();
	TCCR0B = (1<<CS00)|(1<<CS02);
}
void ultrasonicIinit(void)
{
	
	
	DDRC |=(1<<Trigger_pin);		/* Make trigger pin as output */
	PORTB |= (1<<Echo_pin);		/* Turn on Pull-up */
	
	
	//	sei();			/* Enable global interrupt */
	TIMSK1 = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;		/* Set all bit to zero Normal operation */
	
	
}
double getDistance(void)
{
	PORTC |= (1 << Trigger_pin);
	_delay_us(10);
	PORTC &= (~(1 << Trigger_pin));
	
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
	TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */

	/*Calculate width of Echo by Input Capture (ICP) */
	
	while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for rising edge */
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
	TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
	TimerOverflow = 0;/* Clear Timer overflow count */

	while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for falling edge */
	count = ICR1 + (65535 * TimerOverflow);	/* Take count */
	/* 8MHz Timer freq, sound speed =343 m/s */
	distance = (double)count / 466.47;
	return distance;
}
// ISR(TIMER0_OVF_vect)
// {
// 	OCR0A = (dutyCycle/100.0)*255.0;
// }
ISR(TIMER1_OVF_vect)
{
	cli();
	TimerOverflow++;	/* Increment Timer Overflow count */
	reti();
}
void moveCar(movement direction)
{   
	 switch(direction)
   {
	case forward:
		setBit(PORTB,IN1);
		clearBit(PORTC,IN2);
		setBit(PORTC,IN3);
		clearBit(PORTC,IN4);
	    break;
	case backword:
	     clearBit(PORTB,IN1);
	     setBit(PORTC,IN2);
	     clearBit(PORTC,IN3);
	     setBit(PORTC,IN4);
		 break;
	case forward_left:
	     setBit(PORTB,IN1);
	     clearBit(PORTC,IN2);
	     clearBit(PORTC,IN3);
	     clearBit(PORTC,IN4);
		 break;
	case forward_right:
	     clearBit(PORTB,IN1);
	     clearBit(PORTC,IN2);
	     setBit(PORTC,IN3);
	     clearBit(PORTC,IN4);
		 break;
	case stop:
	     clearBit(PORTB,IN1);
	     clearBit(PORTC,IN2);
	     clearBit(PORTC,IN3);
	     clearBit(PORTC,IN4);
		 break;
	case back_left:
         clearBit(PORTB,IN1);
         setBit(PORTC,IN2);
         clearBit(PORTC,IN3);
         clearBit(PORTC,IN4);
		 break;
	case back_right:
	     clearBit(PORTB,IN1);
	     clearBit(PORTC,IN2);
	     clearBit(PORTC,IN3);
	     setBit(PORTC,IN4);
		 break;
}
}
char speed_car(void)
{ 
	if(data == '0')
	{
		data = 'S';
	}
	else if(data == '1')
	{
		speedControl(10);
	}
	else if(data == '2')
	{
		speedControl(12);
	}
	else if(data == '3')
	{
		speedControl(14);
	}
	else if(data == '4')
	{
		speedControl(16);
	}
	else if(data == '5')
	{
		speedControl(18);
	}
	else if(data == '6')
	{
		speedControl(20);
	}
	else if (data == '7')
	{
		speedControl(30);
	}
	else if(data == 'W')
	{
		setBit(PORTD,Forward_Led);
	}
	else if(data == 'w')
	{
		clearBit(PORTD,Forward_Led);
	}
	else if(data == 'U')
	{
		setBit(PORTD,Backward_Led);
	}
	else if(data == 'u')
	{
		clearBit(PORTD,Backward_Led);
	}
	else if(data == 'V')
	{
		setBit(PORTD,Buzzer);
	}
	else if(data == 'v')
	{
		clearBit(PORTD,Buzzer);
	}
	return data;
	
}
void mov_3_Direc(void)
{
	if(data == 'B')
	{
		moveCar(backword);
	}
	else if(data == 'G'||data == 'L')
	{
		moveCar(forward_left);
	}
	else if(data == 'I'|| data == 'R')
	{
		moveCar(forward_right);
	}
	else if(data == 'S')
	{
		moveCar(stop);
	}
	else if(data == 'H')
	{
		moveCar(back_left);
	}
	else if(data == 'J')
	{
		moveCar(back_right);
	}

	
}
void mov_all_Direc(void){
	//PORTD &= ~((1<<PIND2));
	if(data == 'F')
	{
		
		moveCar(forward);
	}
	if(data == 'B')
	{
		moveCar(backword);
		
	}
	else if(data == 'G'||data == 'L')
	{
		
		
		moveCar(forward_left);
		
	}
	else if(data == 'I'|| data == 'R')
	{
		
		
		moveCar(forward_right);
		
	}
	else if(data == 'S')
	{
		
		moveCar(stop);
	}
	else if(data == 'H')
	{
		
		moveCar(back_left);
	}
	else if(data == 'J')
	{
		
		moveCar(back_right);
		
	}
	
}

void setDirection(void){ 
		
	if(Range <= 15)
	{
		PORTD &= ~((1<<PIND2));
		moveCar(stop);
	    mov_3_Direc();	
	}
	
	else if (Range >= 15)
	
	{
		mov_all_Direc();
	}
	else
	{
		PORTD |= (1<<PIND2);
		
		moveCar(stop);
		
	}
	
	
}
