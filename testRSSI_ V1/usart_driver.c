#include <avr/io.h>
#include "usart_driver.h"

void usart0_init(unsigned short int baudrate)
{
	//Set baud rate
	unsigned short int UBRRVAL=(FCLK_SYSTEM/(baudrate*16UL))-1;
	UBRR0L=UBRRVAL; 			//low byte
	UBRR0H=(UBRRVAL>>8); 	//high byte

	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSR0C=(0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(0<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00);

	//Enable Transmitter and Receiver
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
}
unsigned char usart0_getc( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
unsigned char usart0_getc_unblock( void )
{
	if (UCSR0A & (1<<RXC0) )
		return UDR0;
	return 0;
}
void usart0_putc( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
void usart0_puts( unsigned char* str )
{
	short int i=0;
	while(str[i]!='\0')
	{
		usart0_putc(str[i]);
		i++;
	}
}
