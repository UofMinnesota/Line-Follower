
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <time.h>
#include <util/twi.h>
#include "sensor.h"
#include "motor.h"

#ifndef F_CPU
#define F_CPU 16000000ul
#endif
#define MinSpeed 4
#define MaxSpeed 35
uint16_t count_m1 = 20;
uint16_t count_m2 = 20;

inline void setupLeds(){
	DDRC |= (1 << DDC7);	// yellow led
	DDRD |= (1 << DDD5);	// green led
}


inline void toggle_yellowled(){
	PORTC ^= (1 << PORTC7);
}

inline void toggle_greenled(){
	PORTD ^= (1 << PORTD5);
}



int main(void){
	USBCON = 0;
	setupLeds();
	sensorDataSetup();
	Timer1setup();
	setPwm_Timer1_M2(count_m2);
  setPwm_Timer1_M1(count_m1);
	sei();

	while(1){
		if(turn_right){
			if(count_m1 > MinSpeed)
				count_m1--;
			if(count_m2 < MaxSpeed)
				count_m2++;

		}else if(turn_left){
			if(count_m2 > MinSpeed)
				count_m2--;
			if(count_m1 < MaxSpeed)
				count_m1++;
		}
		setPwm_Timer1_M2(count_m2);
	  setPwm_Timer1_M1(count_m1);
		_delay_ms(1000);

	}
}




ISR(__vector_default){}
