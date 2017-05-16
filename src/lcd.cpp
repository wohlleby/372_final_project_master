//Developer: team 212
// Description: This file implements functions to operate an LCD
//----------------------------------------------------------------------//

#include "lcd.h"
#include "timer.h"
#include <util/delay.h>
#include <Arduino.h>



/* Asserts Logic High on Enable Pin
*/
void enableHigh(){
  PORTA |= (1 << PORTA4);
}

/* Asserts Logic Low on Enable Pin
*/
void enableLow(){
  PORTA &= ~(1 << PORTA4);
}

/* Asserts Logic Low on RS Pin
*/
void rsLow(){
  PORTA &= ~(1 << PORTA5);
}

/* Asserts Logic High on RS Pin
*/
void rsHigh(){
  PORTA |= (1 << PORTA5);
}

/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();
  initLCDProcedure();
}

//This is the command sequence to send the data on the lower 4 DDBA pins to the LCD
void sendCommand(){

  enableHigh();
  delayUs(1);
  enableLow();
  delayUs(1);
}

//Initialize the pins we will be using to interface with the LCD
void initLCDPins(){
  DDRA |= (1 << DDA4 | 1 << DDA5);

  DDRA |= ((1 << DDA0) | (1 << DDA1) | (1 << DDA2) | ( 1 << DDA3));
}

//send an initialization command to the LCD and delay the specified amount
void writeDataWithUsDelay(unsigned char data, unsigned int delay){

  PORTA =  (PORTA & 0xF0)|(0x0F & data);

  rsLow();

  sendCommand();

  delayUs(delay);
}

//Send the most significant and then the least significant bits of data and then
//delay the correct amount
void writeCommandWithUsDelay(unsigned char command, unsigned int delay){

  PORTA = (PORTA & 0xF0) | (command >> 4);

  rsHigh();
  sendCommand();

  PORTA = (PORTA & 0xF0) | (command & 0x0F);
  sendCommand();
  delayUs(delay);

}

//send the character with the correct delay
void writeCharacter(unsigned char character){

  writeCommandWithUsDelay(character, 46);
}


//Write a string to the lcd screen
void writeString(const char *string){

  unsigned int  i = 0;

  while(string[i] != '\0') {

    writeCharacter(string[i]);
    i++;
  }

}

//Initialize the LCD to using the 4 bit interface according to the datasheet
void initLCDProcedure(){

  delayUs(15000);

  writeDataWithUsDelay(0b0011, 4100);

  writeDataWithUsDelay(0b0011, 100);


  writeDataWithUsDelay(0b0011, 0);
  writeDataWithUsDelay(0b0010, 40);

  // Function set in the command table
  writeDataWithUsDelay(0b0010, 0);
  writeDataWithUsDelay(0b1000, 40);

  // Display off in the command table
  writeDataWithUsDelay(0b0000, 0);
  writeDataWithUsDelay(0b1000, 40);

  // Clear display in the command table. Remember the delay is longer!!!
  writeDataWithUsDelay(0b0000, 0);
  writeDataWithUsDelay(0b0001, 1640);

  // Entry Mode Set in the command table.
  writeDataWithUsDelay(0b0000, 0);
  writeDataWithUsDelay(0b0110, 40);

  // Display ON/OFF Control in the command table
  writeDataWithUsDelay(0b0000, 0);
  writeDataWithUsDelay(0b1111, 40);

}

//clears the display
void clearDisplay() {

  writeDataWithUsDelay(0b0000, 0);
  writeDataWithUsDelay(0b0001, 1640);
}

//resets the cursor to the top left corner (position 00)
void resetCursor() {

  writeDataWithUsDelay(0b1000, 0);
  writeDataWithUsDelay(0b0000, 40);
}
