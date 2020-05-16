/*
 * ADC.c
 *
 * Created: 27/08/2016 12:16:25 م
 *  Author: tofaa
 */ 
#include "adc.h"

void ADC_Select(unsigned char channel){
	/* Select Ref = AVcc and Select ADC0 channel */
	ADMUX = (1<<REFS0)|channel;
	/* Enable ADC*/
	ADCSRA = (1<<ADEN); 
}
unsigned short ADC_Read(void){
	unsigned short adcValue = 0;
	/* Start Conversion */
	ADCSRA |= (1<<ADSC);
	/* Wait Conv. to complete */
	while(ADCSRA & (1<<ADSC));
	/* Read Value */
	adcValue = ADCL + ADCH*256;
	return adcValue;
}

unsigned short adc_readADC0(void)
{
	ADCSRA &=~ (1<<ADEN);
	ADMUX = 0x40 ;
	ADCSRA |= (1<<ADEN);
	//ADC_Select(0);
	return ADC_Read();
}
unsigned short adc_readADC1(void)
{
	ADCSRA &=~ (1<<ADEN);
	ADMUX = 0x41 ;
	ADCSRA |= (1<<ADEN);
	//ADC_Select(1);
	return ADC_Read();
}