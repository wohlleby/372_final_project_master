// Description: This file describes functions used by the timer
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer3();
void initTimer1();
void delayUs(unsigned int delay);
void delayMs(unsigned int delay);

#endif
