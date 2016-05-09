#include <avr/io.h>
#include <avr/interrupt.h>
#include "motor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
volatile uint8_t direction_m1 = 0; // for calibration
volatile uint8_t direction_m2 = 0;

void setPwm_Timer1_M2(int duCycle){
	 uint32_t t = (float)255*(float)duCycle/(float)100;
	 OCR1B = roundf(t);
}

void setPwm_Timer1_M1(int duCycle){
	 uint32_t t = (float)255*(float)duCycle/(float)100;
	 OCR1A = roundf(t);
}

void forward_M2(){
	if(direction_m2){
		PORTE |= (1 << PORTE2); //setting 1
	}else{
		PORTE &= ~(1 << PORTE2); //setting 0
	}
}

void forward_M1(){
	if(direction_m1){
		PORTD |= (1 << PORTD6); //setting 1
	}else{
		PORTD &= ~(1 << PORTD6); //setting 0
	}
}


void Timer1setup(){
  DDRB |= (1 << DDB6); // motor 2
	DDRB |= (1 << DDB5); // motor 1
  TCCR1A |= (1<<WGM10)|(1<<COM1B1)|(1<<COM1A1); // pwm 8 bits
  TCCR1B |=  (1 << CS10); //1 prescale
}
