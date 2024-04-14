/*
   Credits: https://www.plusivo.com

   Lesson 7: Digital Inputs

   The code below is created for the lesson "Digital Inputs",
   where we will use 2 momentary push buttons to turn on or off an LED.

   In order to use a button, you have to declare the button as INPUT_PULLUP.
   Next, to check the status of a button, you have to use "digitalRead(pin)".
   In case the button was pressed, the value returned by "digitalRead(pin)" is
   equal to 0 or LOW.
   In case the button was not pressed, the value is 1 or HIGH.

   More information about the connections can be found in the guide.
   Make sure you connect the components accordingly, contrary you will
   burn them.
*/

//define the pins used by the buttons and led
const int buttonON = D1;
const int buttonOFF = D2;
const int led = D7;

void setup() 
{
  //in order to read the state of a button, firstly, you have
  //to set the mode of the pin used by it as INPUT_PULLUP.
  pinMode(buttonON, INPUT_PULLUP);
  pinMode(buttonOFF, INPUT_PULLUP);

  //set the mode of the pin used by the led as OUTPUT
  pinMode(led, OUTPUT);
}

void loop() 
{
  //check if the button "ON" was pressed and turn on the LED
  if (digitalRead(buttonON) == 0)
  {
    //turn on the LED
    digitalWrite(led, HIGH); 
  }
  
  //check if the button "OFF" was pressed and turn off the LED
  if (digitalRead(buttonOFF) == 0)
  {
    //turn off the LED
    digitalWrite(led, LOW); 
  }

  //wait for 0.1s (100 ms)
  delay(100);
}
