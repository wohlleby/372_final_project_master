#include <Arduino.h>
#include <avr/io.h>
#include "lcd.h"
#include "timer.h"
#include "switch.h"
#include "drinkList.h"

typedef enum stateType_enum{
  startMessage
}stateType;

int main() {

  volatile stateType state = startMessage;

  int drinkNumber = 0; //keep track of current drink we're on for serial comms
  const char** drinkList = initDrinkList();

  initTimer3();
  initLCD();
  initSwitches();


  while(1) {

      switch(state) {

          case startMessage:

          break;
      }

  }



    return 0;
}
