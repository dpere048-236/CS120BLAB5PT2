/*	Author: David Perez  dpere048@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4#  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{start, increase, decrease, zero, wait, wait2} state;
unsigned char button;
unsigned char button2;
unsigned char tmpC;
void button_Tick(){
    button = PINA&0x01; //button = pinA0
    button2 = PINA&0x02;//BUTTON2 = PINA1
      switch(state){
	case start:	
		if(!button && !button2){ 
			state = start;
		}
		else if(!button2 && button){
			state = increase;
		}
		else if(!button && button2){
			state = decrease;
		}
		else if(button && button2){
			state = zero;
		}
		break;
	case increase:
		if(button && button2){
			state = zero;
		}
		else{
			state = wait2;
		}
		break;
	case wait:
		if(button && button2){ 
			state = zero;
		}
		else if(!button && button2){ 
			state = decrease;
		}
		else if(button && !button2){
			state = increase;
		}
		else{
			state = wait;
		}
		break;
	case decrease:
		if(button && button2){
			state = zero;
		}
		else{
			state = wait2;
		}
		break;
	case wait2:
		if(button && button2){
			state = zero;
		}
		else if(!button2 && !button){
			state = wait;
		}
		else{
			state = wait2;
		}
		break;
	case zero:
		if(!button && !button2){
			state = start;
		}
		else if(button && !button2){
			state = increase;
		}
		else if(!button && button2){
			state = decrease;
		}
		else if(button &&  button2){
			state = zero;
		}
		break;
	}
	switch(state){
		case start:
			break;
		case increase:
			if(tmpC < 9){
				tmpC = tmpC +1;
		}
			break;
		case decrease:
			if(tmpC > 0){
				tmpC = tmpC -1;
		}
			break;
		case zero:
			tmpC = 0;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //configure port A as inputs
	DDRC = 0xFF; PORTB = 0x00; //configure port C as outputs
	state = start; //state is in initial state
    /* Insert your solution below */
	tmpC = 0x07;
    while (1) {
	button = PINA&0x01;
	button_Tick();
	PORTC = tmpC;
	}

    return 0;
}
