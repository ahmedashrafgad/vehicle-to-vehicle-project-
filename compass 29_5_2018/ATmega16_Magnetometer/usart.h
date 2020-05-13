/*
 * usart.h
 *
 * Created: 9/21/2017 3:08:55 PM
 *  Author: SHAKER
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
///------------------------------
// prototype for uart 1 
void uart1_init(unsigned short baudrate);
unsigned char uart1_Receive(void);
void uart1_Send(unsigned char  data);
void uart1_SendString(char* data) ;






#endif /* USART_H_ */