/*
 * UART.c
 *
 * Created: 10/13/2017 09:29:12 م
 * Author : محمد
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include <util/delay.h>
#include <math.h>
#define LED_PIN		    PIND3
#define RF_control_PIN	PIND2


char receive_data;
void send_data(unsigned char data);
int main(void)
{
	DDRD |= (1<<LED_PIN)|(1<<RF_control_PIN);
	PORTD &= ~(1<<LED_PIN);
	
	uart_init(9600);
	sei();
//  	    PORTD &= ~(1<<RF_control_PIN);
//  		_delay_ms(100) ;
// 		uart_SendString("AT+FU3\r\n"); // 1 , 2 , 3 all should be FU1
// 		uart_SendString("AT+C001\r\n");
// 		uart_SendString("AT+B9600\r\n");
// 		_delay_ms(100) ;
		 PORTD |= (1<<RF_control_PIN);
	
    while (1) 
    {
// 		int i ;
// 		
// 		for (i = 0; i < 9; i++)
// 		{
// 			uart_SendString("+INQ:9CE6:E7:160EB2,5A020C,FFC8\r\n");
// 			_delay_ms(2000);
// 		}
		
		uart_SendString("+INQ:9CE6:E7:160EB2,5A020C,FFC8\r\n");
		_delay_ms(100);
		uart_SendString("+INQ:4CA5:6D:10E4D4,5A020C,FFB7\r\n");
		_delay_ms(100);
		uart_SendString("+INQ:4CA5:6D:1600ed,5A020C,FFC3\r\n");
		_delay_ms(100);
		uart_SendString("OK\r\n");
		_delay_ms(1000);
		
		//PORTD |= (1<<LED_PIN);
// 			if(receive_data == 'R')
// 			{
// 				PORTD |= (1<<LED_PIN);
// 				_delay_ms(1000);
// 				PORTD &= ~(1<<LED_PIN);
// 				_delay_ms(1000);
// 			}
// 			else
// 			{
// 				PORTD |= (1<<LED_PIN);
// 				_delay_ms(1000);
// 			}
		
		
    }
}

// ISR(USART_RX_vect)
// {
// 	receive_data = UDR0;
// }
// ISR(USART_RX_vect)
// {
// 	char receive_data;
// 	receive_data = UDR0;
// 	
// 	if(receive_data == 'M')
// 	{
// 		PORTD |= (1<<LED_PIN);
// 		_delay_ms(1000);
// 		PORTD &= ~(1<<LED_PIN);
// 		_delay_ms(1000);
// 	}
// 	else
// 	{
// 		PORTD |= (1<<LED_PIN);
// 		_delay_ms(1000);
// 	}
// 
// }
// void send_data(unsigned char data)
// {
// 	uart_SendString(data);
// 	_delay_ms(100);
// }
// unsigned char receiveData(void)
// {
// 	char x;
// 	x = uart_Receive();
// 	_delay_ms(100);
// }