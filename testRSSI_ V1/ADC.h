/*
 * ADC.h
 *
 * Created: 27/08/2016 12:15:44 م
 *  Author: tofaa
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define		ADC0	0
#define		ADC1	1
#define		ADC2	2
#define		ADC3	3
#define		ADC4	4
#define		ADC5	5
#define		ADC6	6
#define		ADC7	7

void ADC_Select(unsigned char channel);
unsigned short ADC_Read(void);
unsigned short adc_readADC1(void);
unsigned short adc_readADC0(void);


#endif /* ADC_H_ */