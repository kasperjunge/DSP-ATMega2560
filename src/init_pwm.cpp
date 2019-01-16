#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>

void init_fastPWM_timer3()
{
	DDRE |=(1<<PE3); //PWM output, digital pin 5, OC3A

	TCCR3A |= (1<<COM3A1)|(1<<WGM31);	//FAST PWM, 16 bit, non-inverting mode.
	TCCR3B |= (1<<WGM32)|(1<<WGM33);

	TCCR3B |= (0<<CS31)|(1<<CS30); //prescale by 8.

	ICR3=2666; // creates the 50 Hz signal
	OCR3A = 1333;
}
