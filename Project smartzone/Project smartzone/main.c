#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
   lcd_init();
   UBRR0H =0;   //USART configuration 
   UBRR0L = 103;
   uint8_t temp;
   temp = 0;
   DDRD |= (1<<DDD6);
   TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00); //timer 0
   TCCR0B = (1<<CS02);     // Prescaler 
   
   UCSR0B|=(1<<RXEN0); //USART reciever enable.
   UCSR0B|=(1<<TXEN0); //USART Transmitter enable.
   
   UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);                                 // 8-Bit  No parity  1 stop bit
   DDRC &= ~(1<<PC3);                                                //Set analog channel as PC3
    DDRB |= (1<<DDB1) | (1<<DDB2);  //Enable L293d
   ADMUX = (1<<REFS0) | (1<<MUX1) | (1<<MUX0);  
   ADCSRA = (1<<ADEN) |(1<<ADPS2) |(1<<ADPS1) |(1<<ADPS0); //prescalar value analog
 
 PORTB |= (1<<PB1);
 PORTB &= ~(1<<PB2);

    while (1) 
    {
	
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC));  //analog read
		int temp_int = ADC * 0.49; 
		lcd_clear();
		
		
		if(!(UCSR0A & (1<<UDRE0))); //Send bits without waiting. 
		UDR0 = temp_int;
		_delay_ms(2000);
		OCR0A = 0;
			
				//Fan speed control
				if(temp > 60)
				{
					OCR0A = 255; //Fan speed Maximum
				}
				else if(temp > 30)
				{
					OCR0A = 128;	//Fan speed 50%
				}
				else
				{
					OCR0A = 0; //Fan off
				}
				
				lcd_set_cursor(0,0);
				lcd_print("Recieve:");
				lcd_print_uint16(temp);
				lcd_set_cursor(1,0);
				lcd_print("Local: ");
				lcd_print_uint16(temp_int);
		
		if(!(UCSR0A & (1<<RXC0)));  //data received from usart
		temp = UDR0;
		_delay_ms(2000);



		
    }
}

