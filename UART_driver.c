#define FOSC 4915200// Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <util/delay.h>  
#include <avr/io.h>





void USART_Init( unsigned int ubrr0 )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr0>>8);
UBRR0L = (unsigned char)ubrr0;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);


}


void USART_Transmit( char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

char USART_Receive( void )
{
/* Wait for data to be received */
while ((!(UCSR0A)) & (1<<RXC0))  
;
/* Get and return received data from buffer */
return UDR0;
}

void USART_Flush( void )
{
char dummy;
while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
} 

void main( void )
{

//fdevopen(USART_Transmit,USART_Receive);
USART_Init ( MYUBRR );

while(1){
 //_delay_ms(500); 
//USART_Transmit('a');
USART_Transmit(USART_Receive());
_delay_ms(50);
//printf(USART_Receive());
}
}