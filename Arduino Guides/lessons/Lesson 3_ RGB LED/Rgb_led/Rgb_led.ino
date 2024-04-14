/*
 *  Credits: https://www.plusivo.com
 *
 *  Lesson 3: RGB LED
 *  
 *  The main purpose of the code is to show how to use the
 *  PWM technique and how to change the brightness and the colour 
 *  of a RGB LED.
 *  
 *  An RGB LED consist of 3 LEDs into the same body. These LEDs have
 *  different colour (RED, GREEN and BLUE).
 *  
 *  Moreover, you will learn how to create your own functions in
 *  order to better organize your code.
 *  
 *  Please connect the RGB LED accordingly, otherwise you will burn the LED.
 *  More information about the connections can be found in the guide.
*/

//create 3 variables that are used to stores the pins to which is the LED
//attached
const int red = D6;
const int green = D7;
const int blue = D8;

void setup() 
{
  //declase the pins as OUTPUT
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

//below, we have created 3 new functions called "single", "duo" and "all".

//"single" function fades just one led
//it requires one int parameter, which represents the pin of the led
//to fade
void single (int ledPin)
{
  //PWM is generated using 10 bits, so it ranges between
  //0 and 1023 (2^10 = 1024)

  for (int fade = 0; fade < 1024; fade++)
  {
    //set the brightness of the led using analogWrite();
    analogWrite(ledPin, fade);

    delay(2);//wait for 2 milliseconds
  }

  //turn off the led
  analogWrite(ledPin, 0);
}

//"duo" function fades two leds at the same time
//it requires two int parameters, which represents the pins of
//the leds to fade
void duo (int firstLed, int secondLed)
{
  for (int fade = 0; fade < 1024; fade++)
  {
    //set the brightness of the leds using analogWrite();
    analogWrite(firstLed, fade);
    analogWrite(secondLed, fade);
    delay(2);//wait for 2 milliseconds
  }

  //turn off both leds
  analogWrite(firstLed, 0);
  analogWrite(secondLed, 0);
}

//the last function created is "all()"
//it required three int parameters which represents all three pins of
//the leds 
void all (int firstLed, int secondLed, int thirdLed)
{
  for (int fade = 0; fade < 1024; fade++)
  {
    //set the brightness of the LEDs using analogWrite();
    analogWrite(firstLed, fade);
    analogWrite(secondLed, fade);
    analogWrite(thirdLed, fade);
    delay(2);//wait for 2 milliseconds
  }

  //turn off all LEDs
  analogWrite(firstLed, 0);
  analogWrite(secondLed, 0);
  analogWrite(thirdLed, 0);
}

void loop() 
{
  //in the loop function we are going to call
  //the previously created functions 

  //we are going to turn on the LEDs one by one
  single(red);
  single(green);
  single(blue);

  //turn on LEDs two by two
  duo(red, green);
  duo(red, blue);
  duo(green, blue);

  //turn on all 3 LEDs
  all(red, green, blue);
}
