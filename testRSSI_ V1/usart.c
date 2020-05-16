/*
 * usart.c
 *
 * Created: 9/21/2017 3:08:44 PM
 *  Author: Tofaa
 */ 

#include "usart.h"

/* initiation uart module*/
void uart_init(unsigned short int baudrate)
{
	// calculte baudrate 
	unsigned short baudRateValue ;
	baudRateValue = (F_CPU/(baudrate*16UL))-1 ;
	// baudrate reister low , high , set value
	UBRR0L = baudRateValue ; 
	UBRR0H = (baudRateValue >> 8);
	// 8- bit data 
	UCSR0C |=(1 << UCSZ00)|(1<<UCSZ01) ;
	// enable interrupt on Receive 
	UCSR0B |= (1 << RXCIE0) ;
	// enable rx, tx 
	UCSR0B |=(1 << RXEN0) | (1<<TXEN0) ;
	
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
	unsigned char i = 0 ;
	while(data[i] != '\0')
	{
		uart_Send(data[i]);
		i++ ;
	}
	
}

void uart_SendNumber(unsigned int number) 
{
	
	
	
}
