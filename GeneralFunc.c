/*
 * GeneralFunc.c
 *
 *
 *      Author: squanixmachine
 */

#include <avr/io.h>
#include "GeneralFunc.h"
#include "PinDefined.h"
#include "USART.h"

void analogWrite(uint8_t pin, uint8_t val){

 DDRH |= (DDRH & 0x00) | (pin & 0xFF);
 switch(pin){
  	  case(0x08):
		OCR4A = val;
  	  	printString("4A \r\n");
  	  break;
  	  case(0x10):
		OCR4B = val;
  	  	printString("4B \r\n");
  	  break;
  	  case(0x11):
		OCR4A = val;
  	  	OCR4B = val;
  	  break;
  }
}

void pwm_init(){
  TCCR4A |= _BV(COM4A1) | _BV(COM4B1) | _BV(WGM41) | _BV(WGM40);
  TCCR4B |= _BV(CS41) | _BV(CS40);

}

uint16_t analogRead(uint8_t port){
	ADMUX = (ADMUX & 0xF0) | (port & 0x0F);

	ADCSRA |= (1 << ADSC);

	while(ADCSRA & (1<<ADSC));

	return ADC;
}

void adc_init(){
	ADMUX |= _BV(REFS0);
	ADCSRA |= _BV(ADPS2) | _BV(ADEN);
}

uint8_t mapping(uint16_t val){
	uint8_t mapped;

	mapped = val / (1023 / 255);

	return mapped;
}

