/*
 * main.c
 *
 * Created: 27/02/2020 01:10:21 pm
 *  Author: Fatema Moharam
 */ 
#include "IncFile1.h"
unsigned char fans (void)
{
	unsigned char thermo = USART_Receive();
	switch (thermo)
	{
		case TEMPLOW:
		PORTB &= ~0x03;
		return 0;
		case TEMPMID:
		PORTB |=(1<<0);
		PORTB &=~(1<<1);
		return 1;
		case TEMPHIGH:
		PORTB |=0x03;
		return 2;
		default:
		//PORTB &=~0x03;
		return 0;
	}
}
unsigned char leds (void)
{
	unsigned char light = USART_Receive();
	switch (light)
	{
		case LHIGH:
		PORTA &=~0x07;
		return 0;
		case LMIDH:
		PORTA |=(1<<0);
		PORTA &=~0x06;
		return 1;
		case LMIDL:
		PORTA |=0x03;
		PORTA&=~0x04;
		return 2;
		case LLOW:
		PORTA |= 0x07;
		return 3;
		default:
		//PORTA &=~0x07;
		return 0;
	}
}
unsigned char devices (void)
{
	unsigned char noOfDev = 0;
	noOfDev +=leds();
	noOfDev +=fans();
	return noOfDev;
}
void main (void)
{
	
	DDRA |=0x07;
	DDRB |=0x03;
	USART_Init(103);
	unsigned char go;
	//go = USART_Receive();
	//while (!(go == '*'));
	unsigned char devs;
	USART_Transmit(0);

	while(1)
	{
			do
			{
				go = USART_Receive();
			}while (!(go == '*'));
	
		devs = devices();
		USART_Transmit(devs);
	}
}