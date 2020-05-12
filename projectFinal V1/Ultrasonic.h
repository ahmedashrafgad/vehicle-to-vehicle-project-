/*
* Ultrasonic.h
*
* Created: 28/08/2016 05:07:05 م
*  Author: tofaa
*/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 8000000UL
#include "util/delay.h"
#include "avr/io.h"

#define	APPLY_POWER_PINS//859346   204592

#ifdef APPLY_POWER_PINS
	#define VCC_PIN		PIND6
	#define GND_PIN		PIND7
#endif

#define TRIG_PIN		PIND3 // 5
#define ECHO_PIN		PIND4 //6
#define US_PORT			PORTD
#define US_PORT_DDR		DDRD
#define US_PORT_PIN		PIND

void US_Init(void);
unsigned short US_getDistance(void);


#endif /* ULTRASONIC_H_ */