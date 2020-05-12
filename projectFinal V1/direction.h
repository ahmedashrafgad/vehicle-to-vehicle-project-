/*
 * direction.h
 *
 * Created: 12/10/2017 03:24:58 ص
 *  Author: DELL
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "Ultrasonic.h"


#ifndef DIRECTION_H_
#define DIRECTION_H_

#define setBit(PORT,PIN) (PORT |=(1<<PIN))
#define clearBit(PORT,PIN) (PORT &=~(1<<PIN))

typedef enum{stop,forword,backword,right,left} movement;
typedef enum{slow,moderate,fast,veryfast}speed;

void moveCar(movement direction);
void startDelayTimer (unsigned int time);
void speed_car(speed control);
void CarControlInit(void);
void setDirection(void);


#endif
