/*
 * usart.c
 *
 * Created: 6/11/2026 3:20:47 PM
 * Author : TU33
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    UBRR0H = 0;
	UBRR0L = 103;
	UCSR0C &=~(1<<UPM01)|(1<<UPM00)|(1<<USBS0);
	UCSR0C &=~ (1<<UMSEL01)|(1<<UMSEL00);
	UCSR0C |=(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<TXEN0);
	
		while (1) 
    {
		char a[6]="HELLO";
		for(int i=0;i<6;i++)
		{
			UDR0 = a[i];
			while (!(UCSR0A&(1<<TXC0)));
			UCSR0A|=(1<<TXC0);
			
		}
		UDR0 = '\n';
		while(!(UCSR0A&(1<<TXC0)));
		UCSR0A|=(1<<TXC0);
		_delay_ms(1000);
		
    }
}

