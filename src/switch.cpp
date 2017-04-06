//Developer: team 212
// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//
#include "switch.h"
#include <avr/io.h>

 //Initializes pull-up resistor on PB4, 5, and 6 and sets them into input mode
void initSwitches(){

  PORTB |= (1 << PORTB4);
  DDRB &= ~(1 << DDB4); //pin 4 to input mode, previous button

  PORTB |= (1 << PORTB5);
  DDRB &= ~(1 << DDB5); //pin 5 to input mode, select button

  PORTB |= (1 << PORTB6);
  DDRB &= ~(1 << DDB6); //pin 6 to input mode, next button
}
