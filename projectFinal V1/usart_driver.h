#include <avr/io.h>

#define       FCLK_SYSTEM     8000000UL

void          usart0_init(unsigned short int baudrate);
void          usart0_putc(unsigned char data);
unsigned char usart0_getc(void);
void          usart0_puts(unsigned char *str);
unsigned char usart0_getc_unblock( void );