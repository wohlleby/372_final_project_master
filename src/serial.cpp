//Developer: team 212
//purpose: to initialize and enable the use of uart serial communications.

#include <avr/io.h>
#include "serial.h"
#include "timer.h"
#include <Arduino.h>

//This function initalizes uart use
void initSerial1(){
  UCSR1A |= (1 << U2X1); // doubled the rate  // enable the interrupts and transmit
  UCSR1B |= (1 << TXCIE1| 1 << TXEN1 | 1 << RXEN1);  //Sets data size to be 8 bits (1 character)
  UCSR1B &= ~(1 << UCSZ12);
  UCSR1C |= (1 << UCSZ11 | 1 << UCSZ10| 1<< UPM11);// set to even parity
  UCSR1C &= ~(1 << USBS1);
  UBRR1L = 207; // baud rate 9600
}


//Waits for a message from the master
unsigned char USART_Receive()
{
/* Wait for data to be received */
while ( !(UCSR1A & (1<<RXC1)) );
/* Get and return received data from buffer */

return UDR1;
}



//this function is used to trasmmit a character of uart
void USART_Transmit( unsigned char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR1A & (1<<UDRE1)) ){}
  /* Put data into buffer, sends the data */
  UDR1 = data;
  delayMs(10);
}
