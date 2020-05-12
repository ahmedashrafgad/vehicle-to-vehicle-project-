/*
 * usart.c
 *
 * Created: 9/21/2017 3:08:44 PM
 *  Author: TOFAA
 */ 

#include "usart.h"

/* initiation UART module*/
void uart_init(unsigned short int baudrate)
{
	// calculate baudrate 
	unsigned short baudRateValue ;
	baudRateValue = (F_CPU/(baudrate*16UL))-1 ;
	// baudrate register low , high , set value
	UBRR0L = baudRateValue ; 
	UBRR0H = (baudRateValue >> 8);
	// 8- bit data 
	UCSR0C |=(1 << UCSZ00)|(1<<UCSZ01);//|(1<<UMSEL00);
	 
	// enable RX , TX
	UCSR0B |=(1 << RXEN0) | (1<<TXEN0) ;//| (1<<RXCIE0) ;
	
}
/* receive function  ( return one byte) */
unsigned char uart_Receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0 ;
}
/* send function ( send one byte ) */
void uart_Send(unsigned char  data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data	 ;
	
}
/*send function ( String )*/

void uart_SendString(char* data) 
{
    while(*data)
	{ //if there is a char
    uart_Send(*data); //process it as a byte data
	data++;
	}
}

/**
 * Check if the module is started
 *
 * This sends the `AT` command to the ESP and waits until it gets a response.
 *
 * @return true if the module is started, false if something went wrong
 */
