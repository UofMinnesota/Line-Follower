
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <time.h>
#include <util/twi.h>
#include "sensor.h"
#include "motor.h"
#include "analog.h"


#ifndef F_CPU
#define F_CPU 16000000ul
#endif

#define MinSpeed -20
#define MaxSpeed 20
#define incVar 1

uint16_t count_m1 = 20;
uint16_t count_m2 = 20;
int16_t diffVal = 0;
uint8_t analog_reference = 0;

//void StartADC()
//{
	//#if defined(ADCSRA)
	//// set a2d prescale factor to 128
	//ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
//
	//// enable a2d conversions
	//ADCSRA |= (1<<ADEN);
//#endif
//}

inline void setupLeds(){
	DDRC |= (1 << DDC7);	// yellow led
	DDRD |= (1 << DDD5);	// green led
	DDRB |= (1 << DDB0);	// red led
}


inline void toggle_yellowled(){
	PORTC ^= (1 << PORTC7);
}

inline void toggle_greenled(){
	PORTD ^= (1 << PORTD5);
}

void Timer0setup(){//1ms - 1000hz
	TCCR0A |= (1 << WGM01);    // Enables CTC mode for timer0
	TCCR0B |= (1 << CS01) | (1 << CS00); // For setting the timer offset value to 64
	OCR0A = 249; // Sets the counter to 249
	TIMSK0 |= (1 << OCIE0A); // Enable time keeper (timer0)
}

int main(void){
	USBCON = 0;
	setupLeds();
	sensorDataSetup();
	Timer1setup();
	Timer0setup();
	setPwm_Timer1_M2(count_m2);
  setPwm_Timer1_M1(count_m1);
	_delay_ms(100); //delay to be sure that it wont get garbage from sensor.
	sei();

	while(1){

		setPwm_Timer1_M2(count_m2 - diffVal);
	  setPwm_Timer1_M1(count_m1 + diffVal);

	}
}

ISR(TIMER0_COMPA_vect){
	if(!(PINB & (1 << PINB1))){ /* it is crossing the line */
		/*turn right*/
		/*data 1*/
		if(diffVal > MinSpeed)
			diffVal-=incVar;

		PORTC |= (1 << PORTC7);
	}
	else if(!(PINB & (1 << PINB2))){ /* if there is line */
		/*turn left*/
		/*data 4*/
		if(diffVal < MaxSpeed)
			diffVal+=incVar;
		PORTD &= ~(1 << PORTD5);
	}
	else{ /* in line */
		diffVal = 0;
		PORTC &= ~(1 << PORTC7);
		PORTD |= (1 << PORTD5);
	}
}


ISR(__vector_default){}
