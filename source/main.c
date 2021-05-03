/*	Author: lab
 *  Partner(s) Name: Jeremy Walker
 *	Lab Section:
 *	Assignment: Lab # 7 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://youtu.be/JR5CR0zdAdk
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}
unsigned char ADCMAX = 0x5D;
unsigned char ADCMIN = 0x11;
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
			tmpADC =ADC;
			if(tmpADC >=ADCMAX/2){
				tmpB =0x01;
				tmpD =0x00;
				PORTB = tmpB;
				PORTD = tmpD;
			}
			else{
				tmpB = tmpD = 0x00;
				PORTB = tmpB;
				PORTD = tmpD;
			}
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
