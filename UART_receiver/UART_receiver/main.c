/*
 * UART_receiver.c
 *
 * Created: 2/14/2018 7:15:30 PM
 * Author : Mahmoud
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <assert.h>
#include <avr/interrupt.h>
#include "usart.h"
#include <util/delay.h>
#include <math.h>
#define LED_PIN		    PIND3
#define RF_control_PIN	PIND2

char receive_data;
void send_data(unsigned char data);
unsigned char receiveData(void);
int main(void)
{
    DDRD |= (1<<LED_PIN)|(1<<RF_control_PIN);
    PORTD &= ~(1<<LED_PIN);
   // PORTD |= (1<<RF_control_PIN);
    uart_init(9600);
	sei();
	
//	 PORTD &= ~(1<<RF_control_PIN);
// 	 _delay_ms(100) ;
// 	 uart_SendString((unsigned char*)"AT+FU1\r\n"); // 1 , 2 , 3 all should be FU1
	 PORTD |= (1<<RF_control_PIN);
	// char x;
    while (1) 
    {
		//receive_data = uart_Receive;
			if(receive_data == 'T')
			{
				PORTD |= (1<<LED_PIN);
				_delay_ms(500);
				PORTD &= ~(1<<LED_PIN);
				_delay_ms(500);
			}
			else if(receive_data == NULL)
			{
					PORTD &= ~(1<<LED_PIN);
					_delay_ms(1000);
			}
				else
				{
					PORTD |= (1<<LED_PIN);
					_delay_ms(1000);
				}
		
		uart_SendString("R");
		_delay_ms(1000);
		
    }
}

ISR(USART_RX_vect)
{
	receive_data = UDR0;
}
// ISR(USART_RX_vect)
// {
// 	char receive_data;
// 	receive_data = UDR0;
// 	//PORTD |= (1<<LED_PIN);
// 	if(receive_data == 'K')
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
// 	return x;
// }