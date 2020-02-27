/*
 * UART.c
 * Tested, working
 * Created: 26/02/2020 01:07:36 pm
 *  Author: Fatema Moharam
 */ 
#include "IncFile1.h"
void USART_Init( unsigned int baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}
void USART_stringTransmit(char str[])
{
	char n = 0;
	while(str[n])
	{
		USART_Transmit(str[n]);
		n++;	
	}
}
void USART_stringReceive(char str[])
{
	char n = 0;
	unsigned char recieved;
	do
	{
		recieved = USART_Receive();
		str[n] = recieved;
		n++;
		
	}while(recieved != '#');
	str[n-1] = '\0';
}
void USART_intTransmit(int data)
{
	char sdata[10];
	itoa(data,sdata,10);
	USART_stringTransmit(sdata);
}
int USART_intReceive(void)
{
	char rec[11];
	USART_stringReceive(rec);
	return atoi(rec);
}