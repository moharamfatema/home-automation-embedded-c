/*
 * mastercodemain.c
 *
 * Created: 26/02/2020 01:06:40 pm
 * Author : Fatema Moharam
 */ 

#include <avr/io.h>
#include "IncFile1.h"

int main(void)
{	
	DDRB |= 0x0f;
	USART_Init(103);
	INT_init();
	/*USART_Transmit('*');*/
    /* Replace with your application code */
    while (1) 
    {	
		
		if(go)
	    {
			
		    activate();
	    }
	
		
    }
}

