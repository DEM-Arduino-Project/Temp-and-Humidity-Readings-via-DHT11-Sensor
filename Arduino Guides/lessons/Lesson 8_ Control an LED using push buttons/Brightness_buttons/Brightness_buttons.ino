/*
   Credits: https://www.plusivo.com

   Lesson 8: Control an LED using push buttons
   
   The code below is created for the lesson "Control an LED using push buttons",
   where we will use 2 momentary push buttons to modify the brightness of an LED.

   In order to use a button, you have to declare the button as INPUT_PULLUP.
   Next, to check the status of a button, you have to use "digitalRead(pin)".
   In case the button was pressed, the value returned by "digitalRead(pin);" is
   equal to 0 or LOW.
   In case the button wasn't pressed, the value is 1 or HIGH.

   We will use two buttons, one for lowering the brightness and one for 
   increasing the brightness.
  
   More information about the connections can be found in the guide.
   Make sure you connect the components accordingly, contrary you'll
   burn them.
*/

//define the pins used by the buttons and led
const int button_down = D1;
const int button_up = D2;
const int led = D7;

//declare a variable that will store a value
//from 0 to 1023
int container = 0;

void setup() 
{
  //in order to read the state of a button, firstly, you have
  //to set the mode of the pin used by it as INPUT_PULLUP.
  pinMode(button_down, INPUT_PULLUP);
  pinMode(button_up, INPUT_PULLUP);

  //set the mode of the pin used by the led as OUTPUT
  pinMode(led, OUTPUT);
}

void loop() 
{
  //while the "down" button is pressed, the block of 
  //code will run and the brightness will be reduced
  while(digitalRead(button_down) == 0)
  {
    //the minimum value for container is 0, so if the
    //value is greater than 50, we can substract 50
    //else, the value will be set to 0
    if(container > 50)
    {
      //change the value
      container = container - 50;
    }
    else
    {
      //set the value to 0
      container = 0;
    }
    
    //turn on the LED
    analogWrite(led, container); 
    //wait 50 ms before the next run
    delay(50);
  }

  //while the "up" button is pressed, the block of 
  //code will run and the brightness will increase
  while(digitalRead(button_up) == 0)
  {
    //the maximum value for container is 1023
    //if the value is less than 972, we can add 50
    //otherwise, the value will be set to 1023
    if(container < 972)
    {
      container = container + 50;
    }
    else
    {
      container = 1023;
    }
    
    //turn on the LED
    analogWrite(led, container);
    //wait 50 ms before the next run
    delay(50);
  }
}
