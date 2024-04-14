/*
 * Credits: https://www.plusivo.com
 *
 * Lesson 2: Dim an LED
 * 
 * The main purpose of the code is to show how to use the
 * PWM technique and how to change the brightness of an LED.
 * 
 * Make sure you connected the LED correctly (anode to positive and
 * cathode to ground), otherwise, you will burn the LED. Also, do not 
 * forget to use the resistor.
 *
 * More information about the connection can be found in the guide.
 * 
 */

//the int variable "LED" stores the pin used by the LED
const int LED = D6;

//the setup function runs only once when the board is powered
void setup() 
{
  //the following instruction initialises the pin stored in the
  //variable LED as OUTPUT
  pinMode(LED, OUTPUT);   
}

//the loop function runs over and over again forever
void loop() 
{
  //PWM is generated using 10 bits, so it ranges between 
  //0 and 1023 (2^10 = 1024)

  for(int fade = 0; fade < 1024; fade++)
  {
    //set the brightness of the LED using analoWrite();
    analogWrite(LED, fade);

    //wait 2 milliseconds
    delay(2);
  }

  //keep the LED at the maximum brightness for 500 ms
  delay(500);
  
  for(int fade = 1023; fade >= 0; fade--)
  {
    //set the brightness of the LED using analoWrite();
    analogWrite(LED, fade);

    //wait 2 milliseconds
    delay(2);
  }

  //keep the LED off for 500 ms
  delay(500);
}
