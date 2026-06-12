/*
 * fastpwm.c
 *
 * Created: 6/9/2026 2:13:27 PM
 * Author : TU33
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>



int main(void)
{
	DDRD |= (1<<PD6);
    TCCR0A |= (1<<WGM00);
	TCCR0A |=(1<<WGM01);
	TCCR0A &= ~(1<<COM0A0);
	TCCR0A |= (1<<COM0A1);
	TCCR0B &= ~(1<<CS02);
	TCCR0B |= (1<<CS01);
	TCCR0B |= (1<<CS00);
	OCR0A = 153;
    while (1) 
    {
		
	}
}

