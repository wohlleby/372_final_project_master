#include <Arduino.h>
#include <avr/io.h>
#include "lcd.h"
#include "timer.h"
#include "switch.h"
#include "drinkList.h"
#include "serial.h"

typedef enum stateType_enum{
  startMessage, drinkMenu, sendSerial
}stateType;

int main() {

  volatile stateType state = startMessage;

  int drinkNumber = 0; //keep track of current drink we're on for serial comms
  const char** drinkList = initDrinkList();

  initTimer3();
  initTimer1();
  initLCD();
  initSwitches();
  initSerial1();


  while(1) {

      switch(state) {

          case startMessage:
            writeString("Eat my ass");

            delayMs(10000);

            clearDisplay();

            resetCursor();

            writeString("plebs");

            delayMs(10000);

            clearDisplay();

            resetCursor();

            state = drinkMenu;
          break;

          case drinkMenu:

            writeString(drinkList[drinkNumber]); //display current drink

            if(!(PINB & (1 << PINB4))) { //if previous button pressed
              _delay_ms(100);
              while (!(PINB & (1 << PINB4))) { //while button still pressed

              }
              _delay_ms(100);

              if(drinkNumber == 0) { //decrement the drink number
                drinkNumber = 9;
              }
              else {
              drinkNumber--;
              }

              resetCursor();
              clearDisplay();
            } //end previous button pressed

            if(!(PINB & (1 << PINB5))) { //if select pressed
              _delay_ms(100);
              while (!(PINB & (1 << PINB5))) { //while select still pressed

              }
              _delay_ms(100);


              resetCursor();
              clearDisplay();


              state = sendSerial;
            } //end select pressed

            if(!(PINB & (1 << PINB6))) { //if next pressed
              _delay_ms(100);
              while (!(PINB & (1 << PINB6))) { //while next still pressed

              }
              _delay_ms(100);

              if(drinkNumber == 9) {
                drinkNumber = 0;
              }
              else {
                drinkNumber++;
              }

              resetCursor();
              clearDisplay();
            }//end next pressed

            resetCursor();

          break; //end drinkMenu case


          case sendSerial:

            writeString("Sending drink");

            resetCursor();

            USART_Transmit('a');

            delayMs(10000);

            clearDisplay();

            state = startMessage;
          break; //end sendSerial
      }



  }



    return 0;
}
