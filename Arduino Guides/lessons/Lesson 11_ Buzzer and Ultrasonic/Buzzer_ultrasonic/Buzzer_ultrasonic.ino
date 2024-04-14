/*
   Credits: www.plusivo.com

   Lesson 11: Buzzer and Ultrasonic

   The code below is created for the lesson "Buzzer and Ultrasonic"
   and combines two lessons, lesson 9, Buzzer, and lesson 5, Ultrasonic.

   The code below uses an ultrasonic module to measure the distance
   and when the distance is less than 25 cm, the buzzer will start
   to beep.
   
   More information about the connections can be found in the guide.
   
*/

//declare the pins used by the module
const int echoPin = D6; 
const int trigPin = D5;

//declare the pin used by the buzzer
const int buzzer = D2;

//declare 2 variables which help us later to calculate the distance
long duration;
double distance;

void setup()
{
  //start the serial communication with the computer at 115200 bits/s
  Serial.begin(115200);
  
  //set the mode of the pin used by the buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);

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
  // 1 microsecond = 10^(-6) seconds 
  delayMicroseconds(2);

  //generate a ultrasound for 10 microseconds then turn off the transmitter.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //using the formula shown in the guide, calculate the distance
  distance = duration*0.034/2;

  if(distance < 25)
  {
    //creating the beeping effect
    //turn on the buzzer at a
    //frequency of 1kHz(1000Hz)
    //and wait 50 ms
    tone(buzzer, 1000);
    delay(50);

    //turn off the buzzer
    //and wait 50 ms
    noTone(buzzer);
    delay(50);
  }
  else
  {
    //turn off the buzzer
    noTone(buzzer);
  }

  //wait for 0.1s
  delay(100);
}

