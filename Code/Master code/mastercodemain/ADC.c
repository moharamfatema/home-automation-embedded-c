/*
 * ADC.c
 * Tested, working
 * Created: 26/02/2020 03:56:35 pm
 * Author: Fatema Moharam
 */ 
#include "IncFile1.h"

void ADC_Init(char bitno)
{
	DDRA &=~(1<<bitno);
	ADMUX = bitno; //AREF , right-shifted result , selected A bitno
	ADCSRA |=0x87; //ADC enable, prescaler 128
}
int ADC_Read(char vref)
{
	uint32_t read = 0;
	ADCSRA |=(1<<ADSC); //start conversion
	while((ADCSRA&(1<<ADIF)) == 0){} //polling the flag bit
	read = ADCW; //binary
	read *= 1000*vref; //converted to milliVolt, reference = +5v
	read /= 1024; //volt reading is ready
	ADCSRA |=(1<<ADIF); //clear the flag
	return read;
}
void ADC_Shutdown(void)
{
	ADMUX &=~ 0x0f;
}
unsigned char Thermistor (void)
{
	ADC_Init(0);
	uint32_t temp = ADC_Read(5)/10;
	ADC_Shutdown();
	unsigned short result = 0;
	if (temp < 20)
	{
		result = TEMPLOW;
	} 
	else if (temp <=25)
	{
		result = TEMPMID;
	}else
	{
		result = TEMPHIGH;
	}
	return result;
}
unsigned char LDR (void)
{
	ADC_Init(1);
	uint64_t vout = ADC_Read(5);
	ADC_Shutdown();
	//res = ((10000)*(5000-VOUT))/VOUT;
	unsigned int resistance = (10*(5000-vout))/vout;
	//10k,100k,500k
	unsigned short result = 0;
	if (resistance <10)
	{
		result = LHIGH;
	} 
	else if (resistance <100)
	{
		result = LMIDH;
	}
	else if(resistance < 500)
	{
		result = LMIDL;
	}
	else
	{
		result = LLOW;
	}
	

	return result;
}