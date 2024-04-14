/*
 * Credits: https://www.plusivo.com
 *
 * Lesson 1: Blink an LED
 * 
 * In this lesson, you will learn how to turn on and off an LED.
 * 
 * Make sure you connected the LED correctly (anode to positive and
 * cathode to ground), otherwise, you will burn the LED. Also, do not 
 * forget to use the resistor.
 *
 * More information about the connection can be found in the guide.
 * 
 */

//the int variable "LED" stores the pin used by the LED
const int LED = D1;

//the int variable "delayTime" stores the time (in milliseconds) between the blinks
//1000 milliseconds = 1 second
const int delayTime = 1000;

//the setup function runs only once when the board is powered
void setup() 
{
  //the following instruction initialises the pin stored in the
  //variable LED as OUTPUT
  //this instruction lowers the impedance of the pin so it can provide
  //a higher current to other components.
  pinMode(LED, OUTPUT);   
}

//the loop function runs over and over again forever
void loop() 
{
  //in order to turn on/off the LED, you have to use the
  //instruction digitalWrite(pin, state);
  //Parameters:
  //pin: it can be one of the 9 available on the board (from D0-D8)
  //state: it can be either HIGH, either LOW.
  
  //the next two instructions are used to turn off the LED and wait for 1 second
  digitalWrite(LED, LOW);   
  delay(1000); 
  
  //the next two instructions are used to turn on the LED and wait for 1 second                  
  digitalWrite(LED, HIGH);  
  delay(1000);                     
}
