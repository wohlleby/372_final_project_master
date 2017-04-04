#include "timer.h"
#include <avr/io.h>
void initTimer3(){ //init timer to ctc mode

  TCCR3B |= (1 << WGM32);
  TCCR3B &= ~(1 << CS30 | 1 << CS32 | 1 << CS31);

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
