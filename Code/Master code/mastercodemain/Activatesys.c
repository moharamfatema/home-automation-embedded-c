/*
 * Activatesys.c
 *
 * Created: 27/02/2020 10:11:04 pm
 *  Author: Fatema Moharam
 */ 
#include "IncFile1.h"


void INT_init (void)
{
	sei();
	GICR |=0xc0;
	MCUCR|=0x0c;
	DDRC |=0x03;
	PORTC|=(1<<LINACTIVE);
	PORTC&=~(1<<LACTIVE);
}
ISR(INT1_vect)
{
	//check
	unsigned char check = passcheck();
	if (check)
	{
		go = 1;
		
	} 
	else
	{	
		//block
		deactivate();
		USART_stringTransmit("Blocking system for 30 seconds.");
		_delay_ms(30000);
	}
}
ISR(INT0_vect)
{
	deactivate();
}
void deactivate (void)
{
	USART_Transmit(LHIGH);
	USART_Transmit(TEMPLOW);
	PORTC|=(1<<LINACTIVE);
	go = 0;
}
void sevenSeg (void)
{	//tested,Working
	unsigned char noOfDevices = USART_Receive();
	PORTB = (PORTB&0xf0) | (noOfDevices&0x0f);
}
unsigned char passcheck(void)
{//tested working
	char pass[11];
	unsigned char i = 0;
	unsigned char test = 0;
	do{
		USART_stringTransmit("PIN: ");
		USART_stringReceive(pass);
		if(!strcmp(pass,PASSWORD))
		{
			test++;
			break;
		}else{
			USART_stringTransmit("Wrong Password.");
			USART_Transmit(NEW_LINE);
			i++;
		}
	}while(i<3);
	return test;
}
void activate (void)
{
		PORTC &=~(1<<LINACTIVE);
		PORTC |= (1<<LACTIVE);
	
		unsigned char temp = Thermistor();
		unsigned char light = LDR();	
	
		USART_Transmit('*');
		USART_Transmit(light);
		USART_Transmit(temp);
		sevenSeg();
}
