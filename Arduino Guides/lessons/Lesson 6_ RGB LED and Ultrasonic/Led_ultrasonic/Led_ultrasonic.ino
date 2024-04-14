/*
   Credits: www.plusivo.com

   Lesson 6: RGB LED and Ultrasonic
   
   The code below is created for the lesson RGB LED and Ultrasonic and 
   combines two lessons: lesson RGB LED and lesson Ultrasonic HC-SR04+.

   The code below uses an ultrasonic module to measure the distance
   and when the distance is less than 25 cm, the red LED will
   flash quickly, otherwise, the green LED will slowly flash.
   
   More information about the connections can be found in the guide.
   
*/

//declare the pins used by the module
const int echoPin = D5; 
const int trigPin = D3;

//declare the pins used by the RGB LED
const int red = D6;
const int green = D7;
const int blue = D8;

//declare 2 variables which will help us later to calculate the distance
long duration;
double distance;

void setup()
{
  //start the serial communication with the computer at 115200 bits/s 
  Serial.begin(115200);
  
  //set the mode of the pins used by the RGB LED as OUTPUT
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  //the trigger pin (transmitter) must be set as OUTPUT  
  pinMode(trigPin, OUTPUT); 

  //the echo pin (receiver) must be set as INPUT
  pinMode(echoPin, INPUT); 
}

void loop()
{
  //set the trigPin LOW in order to prepare for the next reading
  digitalWrite(trigPin, LOW);

  //delay for 2 microseconds
  delayMicroseconds(2);

  //generate a ultrasound for 10 microseconds then turn off the transmitter
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //using the formula shown in the guide, calculate the distance
  distance = duration*0.034/2;
  
  //display the distance in Serial Monitor
  Serial.println(distance);
  
  if(distance < 25)
  {
    //the next 4 instructions are used
    //to create the flashing effect
    //turn on the LED and wait 35 ms
    digitalWrite(red, HIGH);
    delay(35);

    //turn off the LED and wait 35 ms
    digitalWrite(red, LOW);
    delay(35);
  }
  else
  {
    //turn on the green LED and wait 300 ms
    digitalWrite(green, HIGH);
    delay(300);

    //turn off the green LED and wait 200 ms
    digitalWrite(green, LOW);
    delay(200);
  }
}

