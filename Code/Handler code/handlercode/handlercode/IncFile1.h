/*
 * IncFile1.h
 *
 * Created: 26/02/2020 01:07:15 pm
 *  Author: Fatema Moharam
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#define F_CPU 16000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define TEMPLOW 'a'
#define TEMPMID 'b'
#define TEMPHIGH 'c'
#define LLOW 'd'
#define LMIDL 'e'
#define LMIDH 'f'
#define LHIGH 'g'
#define NEW_LINE 0x0d
 

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_stringTransmit(char str[]);
void USART_stringReceive(char str[]);
void USART_intTransmit(int data);
int USART_intReceive(void);

#endif /* INCFILE1_H_ */