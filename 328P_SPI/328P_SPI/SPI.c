/*
 * SPI.c
 *
 * Created: 12/06/2018 08:42:03 م
 *  Author: Ahmed Manzpur
 */ 
#include <stdio.h>
#include "SPI.h"
void spiInitMaster(void)
{

	DDRB |= (1<<PINB1)|(1<<PINB2)|(1<<PINB0);    // SCK, MOSI and SS as outputs
	DDRB &= ~ (1<<PINB3);                 // MISO as input
	PORTB |= (1<<PINB0) ;//Set slaves high
	
	SPCR |= (1<<MSTR);               // Set as Master
	SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
	SPCR |= (1<<SPE);                // Enable SPI
}
void spiInitSlave(void)
{

	DDRB &= ~(1<<PINB1)|(1<<PINB2)|(1<<PINB0);  // SCK, MOSI and SS as inputs
	DDRB |= (1<<PINB3);                  // MISO as output

	SPCR &= ~(1<<MSTR);                // Set as slave
	SPCR |= (1<<SPR0)|(1<<SPR1);       // divide clock by 128
	SPCR |= (1<<SPE);
}

char spiReceive(void)
{//Call in while(1)
	char dataIn;
	while(!(SPSR & (1<<SPIF)));    // wait until all data is received
	dataIn = SPDR;
	return dataIn;
}

void spiTransmit(char dataOut, int slavePin)
{   //Call in while(1)
	PORTB &= ~ (1<<slavePin);
	SPDR = dataOut;                 // send the data
	while(!(SPSR & (1<<SPIF)));
}
