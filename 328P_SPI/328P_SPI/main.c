/*
 * SPI_ATMEGA128.c
 *
 * Created: 22/03/2018 04:37:27 PM
 * Author : 8.1
 */  

#include <avr/io.h>
#define	 F_CPU	 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


void spiInitMaster(void);
void spiInitSlave(void);
char spiReceive(void);
void spiTransmit(char dataOut, int slavePin);


int main(void)
{
	char DATA;
	DDRD = (1<<PIND);
	PORTD = 0x00;
	
    /* Replace with your application code */
	spiInitSlave ();
    while (1) 
    {
		
		DATA = spiReceive();
		PORTD ^= (1<<SPIE);	
		if(DATA == 'S')
		{
			PORTD ^= (1<<PIND0);
		}
			
				
    }
}