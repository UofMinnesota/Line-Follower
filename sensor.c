#include <avr/io.h>
#include <avr/interrupt.h>
#include "sensor.h"

void sensorDataSetup(){

	DDRB &= ~(1 << DDB1); //data 1 pin o/i
	DDRB &= ~(1 << DDB2); //data 4 pin o/i

	//power sensor
	DDRC |= (1 << DDC6);
	PORTC |= (1 << PORTC6);
	/*data interrupt*/
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT1); /*enable pcint1 and pcint2 isr*/
	PCMSK0 |= (1 << PCINT2);
}

ISR(PCINT0_vect){

	if(PINB & (1 << PINB1)){ //if there is line
		/*turn right*/
		/*data 1*/
		turn_right = 1;
		turn_left = 0;
		PORTC ^= (1 << PORTC7);
	}else if(PINB & (1 << PINB2)){ //if there is line
		/*turn left*/
		/*data 4*/
		turn_left = 1;
		turn_right = 0;
		PORTD ^= (1 << PORTD5);
	}
}
