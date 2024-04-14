/*
   Credits: www.plusivo.com

   Lesson 9: Buzzer
   
   The code below is created for the lesson "Buzzer"
   where you will learn how to use a buzzer.
   
   Make sure you connected the buzzer correctly, as shown in the guide.

   In this code we will turn on the buzzer, at a frequency of 1000Hz,
   for one second, and then turn it off for one second, then turn it back on,
   at a frequency of 500Hz, for one second, and then turn it off for
   one second, and the code will do these instructions over and over again.
   
   More information about the connections can be found in the guide.
   
*/

//define the pin used by the buzzer
const int buzzer = D6;

void setup()
{
  //set the mode of the pin used by the buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  //turn on the buzzer and wait 1 s
  //we use a frequency of 1kHz(1000Hz)
  //you can change this frequency so the sound can be
  //more pleasant
  tone(buzzer, 1000);
  delay(1000);

  //turn off the buzzer and wait 1 s
  noTone(buzzer);
  delay(1000);

  //turn on the buzzer at a frequency
  //of 500Hz and wait 1 s
  tone(buzzer, 500);
  delay(1000);

  //turn off the buzzer
  noTone(buzzer);
  delay(1000);
}

