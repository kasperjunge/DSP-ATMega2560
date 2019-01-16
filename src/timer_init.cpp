#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include "timer_init.h"
#include "adc_init.h"

/*initialisering af timer0-interrupt, sat til CTC mode, med aktivering af interrupt af compare register A -- prescaleret 64 gange
OCR0A er sat til CompareValue, som isætte i main();
*/

void init_timer(unsigned int Freqq)
{
	pinMode(12, OUTPUT);
	TCCR1A |= (1 << COM1B0); //toggle pin 12 for debug

	TCCR1B |= (1 << WGM12); // CTC mode
	TCCR1B |= (1 << COM1B1);
	TCCR1B |= (0 << CS12)|(0<< CS11)|(1<<CS10); // 256 prescale //16000000/64 = 250000
	TIMSK1 |= (1 << OCIE1B); //activates interrupt at compare register b


	OCR1B = Freqq; //= F_CPU/f_sampl*2*N (N = 1)
	
}
