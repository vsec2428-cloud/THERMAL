/*
 * ithenthrrr.c
 *
 * Created: 6/11/2026 11:46:28 AM
 * Author : TU33
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>


int main(void)
{
	lcd_init();
	
	DDRC&=~(1<<DDC3);     //PC3(ADC3) as input
	
	ADMUX|=(1<<REFS0);
	
	
	ADMUX|=(1<<MUX0);           //CHANNEL 3
	ADMUX|=(1<<MUX1);
	
	ADCSRA|=(1<<ADEN);      //ADEN=1, ENABLE ADC
	
	ADCSRA|=(1<<ADPS2);		//SET PRESCALAR
	ADCSRA|=(1<<ADPS1);
	ADCSRA|=(1<<ADPS0);
	
	

	/* Replace with your application code */
	while (1)
	{
		DDRB |= (1<<PB2);
		DDRB |= (1<<PB5);
		DDRB |= (1<<PB1);
		ADCSRA|=(1<<ADSC);		//ADSC=1, START CONVERSION
		
		
		while(ADCSRA&(1<<ADIF));		//check for conversion complete
		ADCSRA|=(1<<ADIF);
		
		uint16_t adcread=ADC;
		float voltage = (adcread * 5.0)/1024.0;
		float temperature = voltage*100.0;
		
		uint16_t temp_int = (uint16_t)temperature;
		uint16_t temp_dec = (uint16_t)((temperature - temp_int)*10);
		lcd_clear();
		
		lcd_set_cursor(0,0);
		lcd_print("temp:");
		lcd_set_cursor(0,6);
		lcd_print_uint16(temp_int);
		lcd_print(".");
		lcd_print_uint16(temp_dec);
		lcd_print("C");
		lcd_set_cursor(1,0);
		lcd_print("ADC:");
		lcd_print_uint16(adcread);
		DDRB|= (1<<PB2);
		
		if (temperature>45)
		{
			PORTB|=(1<<PB2);
			PORTB|=(1<<PB5);
			PORTB&=~(1<<PB1);
			
		}
		else
		{
			PORTB &=~(1<<PB2);
			PORTB &=~(1<<PB5);
			PORTB &=~(1<<PB1);
		}
		_delay_ms(1000);
	}
}

