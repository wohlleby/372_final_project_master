//Developer: team 212
//this file contains a MS timer and Us timer and their init functions

#include "timer.h"
#include <avr/io.h>

void initTimer3(){ //init timer 3 to ctc mode

  TCCR3B |= (1 << WGM32);
  TCCR3B &= ~(1 << CS30 | 1 << CS32 | 1 << CS31);

}

void initTimer1(){ //init timer 1 to ctc mode

  TCCR1A &= ~(1 << WGM10 | 1 << WGM11);
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);

}


//delay for "delay" amount of milliseconds
void delayMs(unsigned int delay){

  unsigned int ticks = 15*delay;

  TCNT3H = 0;
  TCNT3L = 0; //clear timer

  OCR3AH = ticks >> 8;
  OCR3AL = ticks & 0x00FF; //calculate high and low count amounts

  TCCR3B |= (1 << CS30 | 1 << CS32);
  TCCR3B &= ~(1 << CS31); //turn on the timer

  while(!(TIFR3 & (1 << OCF3A))); //do nothing until flag

  TIFR3 |= (1 << OCF3A); //clear flag
  TCCR3B &= ~(1 << CS31 | 1 << CS30 | 1 << CS32); //turn off timer

}

void delayUs(unsigned int delay){
  // clear the timer
  TCNT1H = 0;
  TCNT1L = 0;

  // calculate the TOP value and assign it to OCR1A
  unsigned int ticks = delay*2;
  OCR1AH = ticks >> 8;
  OCR1AL = ticks & 0x00FF;

  // Turn on the timer
  TCCR1B &= ~(1 << CS10 | 1 << CS12); //prescaler of 8
  TCCR1B |= (1 << CS11);

  // Do nothing while the OCF1A flag is not up
  while(!(TIFR1 & (1 << OCF1A)));

  // Clear the OCF1A flag
  TIFR1 |= (1 << OCF1A);

  // Turn off the timer

  TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12);

}
