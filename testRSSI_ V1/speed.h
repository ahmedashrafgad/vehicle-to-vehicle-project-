/*
 * speed.h
 *
 * Created: 12/10/2017 04:12:15 ص
 *  Author: DELL
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define setBit(PORT,PIN) (PORT |=(1<<PIN))
#define clearBit(PORT,PIN) (PORT &=~(1<<PIN))


typedef enum{slow,moderate,fast}speed;


void speed_contr(speed car);