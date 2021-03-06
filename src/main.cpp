//Developer: team 212
//main.cpp controls the lcd and communication between the master and slave
//arduinos.  It also contains the main state machine for the master, which
//controls contains the switch logic and the logic for sending drink via serial

#include <Arduino.h>
#include <avr/io.h>
#include "lcd.h"
#include "timer.h"
#include "switch.h"
#include "drinkList.h"
#include "serial.h"

typedef enum stateType_enum{
  startMessage, drinkMenu, sendSerial, dispensingDrink
}stateType;

int main() {

  volatile stateType state = startMessage;

  int drinkNumber = 0; //keep track of current drink we're on for serial comms
  const char** drinkList = initDrinkList();

  unsigned char serialReceived;

  initTimer3();
  initTimer1();
  initLCD();
  initSwitches();
  initSerial1();


  while(1) {

      switch(state) {

          //Display initial welcome message
          case startMessage:

            writeString("DRINKMASTER5000");
            delayMs(10000);
            clearDisplay();
            resetCursor();
            writeString("Team 212");
            delayMs(10000);
            clearDisplay();
            resetCursor();

            state = drinkMenu;

          break;

          //default, displays the drink list and waits for switch to be pressed
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


          //state to send the drink order number to the slave
          case sendSerial:

            writeString("Sending drink");

            resetCursor();

            USART_Transmit('a' + drinkNumber); //send anything for test

            delayMs(100);

            clearDisplay();
            resetCursor();

            state = dispensingDrink;
          break; //end sendSerial

          //in the process of dispensing drink, wait for communication from slave
          case dispensingDrink:

            writeString("Pouring drink");


            //wait for information from the slave
            serialReceived = USART_Receive();


            if(serialReceived == 's') { //cup removed while pouring

              clearDisplay();
              resetCursor();
              writeString("No Cup Detected");

              while(serialReceived != 'r'){ //wait for the cup to be replaced
                serialReceived = USART_Receive();
              }

              clearDisplay();
              resetCursor();
            }

            if(serialReceived == 't') { //drink finished

              clearDisplay();
              resetCursor();
              state = startMessage;
            }

            resetCursor();

          break;//end dispensingDrink

      }//end switch



  }//end while(1)



    return 0;
}//end main
