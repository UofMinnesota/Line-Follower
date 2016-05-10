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
	//PCICR |= (1 << PCIE0);
	//PCMSK0 |= (1 << PCINT1); /*enable pcint1 and pcint2 isr*/
	//PCMSK0 |= (1 << PCINT2);
}
