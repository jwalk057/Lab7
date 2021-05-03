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
const unsigned char ADCMAX = 0x5D;
const unsigned char ADCMIN = 0x11;
unsigned char ADCThresh = 0x00;

unsigned char tmpB=0x00;
unsigned short tmpADC=0x00;

enum SM {Start, Go} sm;
void Tick(){
	ADCThresh = ADCMAX/8;
	switch(sm){
		case Start:
			sm = Go;
			break;
		case Go:	
			break;
	}
	switch(sm){
		case Start:
			tmpB = 0;
			PORTB = tmpB;
			break;
		case Go:
			tmpADC =ADC;
			if(tmpADC <= ADCMIN+1){
				tmpB =0x01;
				PORTB = tmpB;
			}
			else if(tmpADC <= ADCThresh*2){
				tmpB = 0x03;
				PORTB = tmpB;
			}
			else if(tmpADC <= ADCThresh*3){
                                tmpB = 0x07;
                                PORTB = tmpB;
                        }
			else if(tmpADC <= ADCThresh*4){
                                tmpB = 0x0F;
                                PORTB = tmpB;
                        }
			else if(tmpADC <= ADCThresh*5){ 
                                tmpB = 0x1F;
                                PORTB = tmpB;
                        }
                        else if(tmpADC <= ADCThresh*6){
                                tmpB = 0x3F;
                                PORTB = tmpB;
                        }
                        else if(tmpADC <= ADCThresh*7){
                                tmpB = 0x7F;
                                PORTB = tmpB;
                        }
			else if(tmpADC >= ADCThresh*8){
				tmpB = 0xFF;
				PORTB = tmpB;
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
