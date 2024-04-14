/*
   Credits: www.plusivo.com

   Lesson 10: Buzzer and Digital Inputs
   
   The code below is created for the lesson "Buzzer and Digital Inputs"
   where you will learn how to use a buzzer and a push button.

   More information about the connection can be found in the guide.
*/

//define the pins used by the button and buzzer
const int button = D1;
const int buzzer = D6;

void setup()
{
  //set the mode of the pin used by the buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);

  //in order to read the state of a button, firstly, you have
  //to set the mode of the pin used by it as INPUT_PULLUP.
  pinMode(button, INPUT_PULLUP);
}

void loop()
{
  //read the current state of the button
  //if the button is pressed, turn on the buzzer
  //if the button is not pressed, turn off the buzzer
  if(digitalRead(button) == 0)
  {
    //we use a frequency of 1kHz(1000Hz)
    //you can change this frequency so the sound can be
    //more pleasant
    tone(buzzer, 1000);
  }
   
  //if the button is pushed down, we need something 
  //to keep the loop() function from running
  while(digitalRead(button) == 0)
  {
    //if we leave the while with no instructions to do
    //the board will crash, because it will stay too long 
    //in a while loop() and other processes will not be able to run
    yield();
  }
  
  noTone(buzzer);
  
  //wait 0.1 s
  delay(100);
}

