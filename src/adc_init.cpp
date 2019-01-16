#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include "adc_init.h"

void init_adc(){

	ADCSRA |=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE);  //(autotrigger on compare timer 0 A match) 128 prescalling clock 125 kHz
	ADCSRA |= (0<<ADPS0)|(0<<ADPS1)|(0<<ADPS2);
	ADCSRB |= (1<<ADTS2)|(0<<ADTS1)|(1<<ADTS0); //(autotrigger on compare timer1 B match)
	ADMUX  |=(1<<REFS0); //referencespænding, AVCC med extern kondensator på AREF pin - p.289
}

/*
Initialisering af kanaler
*/
void select_channel(unsigned char channel){

	ADMUX = (0x07 & channel); //kanaler 0-7
	DIDR0 = (1<<channel);
	DIDR0 =!DIDR0;
	DIDR0|= 0x02; //digital input disabled for kanaler 0-3
}
/*
Start af samplin
*/
unsigned int get_sample1(){

	ADCSRA|=(1<<ADSC);   //her starter adc'en sin sampling

	while(!(ADCSRA &(1<<ADIF))); //poll
		return (ADCL + (ADCH<<8)); //returnere 10 bit sampleværdi
}
