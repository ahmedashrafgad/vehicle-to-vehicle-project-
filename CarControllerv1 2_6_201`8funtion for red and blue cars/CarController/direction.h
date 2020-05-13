/*
 * direction.h
 *
 * Created: 02/06/2018 09:23:42 م
 *  Author: DELL
 */ 


#ifndef DIRECTION_H_
#define DIRECTION_H_

#define F_CPU	8000000UL
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "direction.h"
#include "usart.h"

#define IN1		PINB1
#define IN2		PINC4
#define IN3		PINC3
#define IN4		PINC2
#define ENA		PINC1
#define ENB		PINC0
#define  Trigger_pin	PINC5	/* Trigger pin */
#define  Echo_pin		PINB0



// #define Forward	         	F
// #define Backward          	B
// #define Left		            L
// #define Right		        R
// #define forward left		    G
// #define forward right		I
// #define back left		    H
// #define back right 		    J

#define setBit(PORT,PIN)	(PORT |=(1<<PIN))
#define clearBit(PORT,PIN)	 (PORT &=~(1<<PIN))

typedef enum{stop,forward,backword,forward_left,forward_right,back_left,back_right} movement;

//int state = 0;
//int flag=0;        //makes sure that the serial only prints once the state
//int stateStop=0;

void ultrasonicIinit(void);
double getDistance(void);
//------------------
void CarControlInit(void);
void speedControl(double dutyCycle);
void moveCar(movement direction);
char speed_car( void);
void setDirection(void);
void mov_all_Direc(void);
void mov_3_Direc(void);
#endif /* DIRECTION_H_ */