/*
 * usart.h
 *
 * Created: 9/21/2017 3:08:55 PM
 *  Author: Tofaa
 */ 


#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
//#define FCLK_SYSTEM 8000000UL
#define F_CPU 8000000UL
/* initiation uart module*/
void uart_init(unsigned short baudrate);
/* receive function  ( return one byte) */
unsigned char uart_Receive(void);
/* send function ( send one byte ) */
void uart_Send(unsigned char  data);
/*send function ( String )*/

void uart_SendString(char* data) ;

void uart_SendNumber(unsigned int number) ;





#endif /* USART_H_ */