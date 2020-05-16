/*
* Ultrasonic.c
*
* Created: 28/08/2016 05:07:31 م
*  Author: tofaa
*/
#include "Ultrasonic.h"
#include <avr/interrupt.h>

volatile unsigned short overflows = 0;

void US_Init(void){
	/* init io */
	US_PORT_DDR |=  (1<<TRIG_PIN); /* TRIG */
	US_PORT		&= ~(1<<TRIG_PIN); /* TRIG */
	US_PORT_DDR &= ~(1<<ECHO_PIN); /* ECHO */
	US_PORT		&= ~(1<<ECHO_PIN); /* ECHO */
	
	#ifdef APPLY_POWER_PINS
	US_PORT_DDR |=  (1<<VCC_PIN); /* VCC */
	US_PORT_DDR |=  (1<<GND_PIN); /* GND */
	US_PORT		|=  (1<<VCC_PIN); /* VCC */
	US_PORT		&= ~(1<<GND_PIN); /* GND */
	#endif
	
	/* init timer0 */
	
	TCCR1B |= (1<<CS11); /* 1/8 Prescaler */
	TIMSK1 |= (1<<TOIE1); /* Enable Overflow Int */
	sei();				/* Enable Global interrupt */
}
unsigned short US_getDistance(void){
	unsigned short pulse_width = 0,distance = 0;
	/* Send Trigger */
	US_PORT |= (1<<TRIG_PIN);
	_delay_us(10);
	US_PORT &= ~(1<<TRIG_PIN);
	/* Measure Pulse Width */
	while(!(US_PORT_PIN & (1<<ECHO_PIN))); /* Wait for rising edge */
	TCNT1L = 0;
	overflows = 0;
	while((US_PORT_PIN & (1<<ECHO_PIN)))/* Wait for falling edge */
	{
		if (overflows ==5) // maximum is 23 cm
		{
			break;
		}
	}  
	pulse_width = TCNT1L + overflows*256; /* Calc, Pulse Width in us */
	distance = (pulse_width/29.1)/2; /* distance in cm */
	return distance; 
}
ISR(TIMER1_OVF_vect){
	overflows++;
}