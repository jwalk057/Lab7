/*	Author: lab
 *  Partner(s) Name: Jeremy Walker
 *	Lab Section:
 *	Assignment: Lab # 7 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://youtu.be/A-z_zVovpgw
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}
unsigned char tmpB=0x00;
unsigned char tmpD=0x00;
unsigned short tmpADC=0x00;

enum SM {Start, Go} sm;
void Tick(){
	switch(sm){
		case Start:
			sm = Go;
			break;
		case Go:	
			break;
	}
	switch(sm){
		case Start:
			tmpB = tmpD = 0;
			PORTB = tmpB;
			PORTD = tmpD;
			break;
		case Go:
			tmpADC = ADC;
			tmpB = (char)tmpADC;
			tmpD = (char)(tmpADC >> 8);
			PORTB = tmpB;
			PORTD = tmpD;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	ADC_init();
	sm = Start;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
