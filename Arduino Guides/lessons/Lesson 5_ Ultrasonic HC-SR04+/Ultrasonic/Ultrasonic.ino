/*
 * Credits: www.plusivo.com
 * 
 * Lesson 5: Ultrasonic HC-SR04+
 * 
 * The code below uses an ultrasonic module to measure
 * the distance. 
 * 
 * This module can work with voltages as low as 3V and up to 5.5V,
 * so we do not need an additional power supply and
 * neither a shift level.
 * 
 * The module is powered by the development board. 
 * 
 * For further information, check the guide.
 * 
 */

//declare the pins used by the module
const int echoPin = D5; 
const int trigPin = D3;

//declare 2 variables which help us later to calculate the distance
long duration;
double distance;

void setup() 
{
  //start the serial communication with the computer at 115200 bits/s
  Serial.begin(115200); 

  Serial.println("The board has started");

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
  //1 microsecond = 10^(-6) seconds 
  delayMicroseconds(2);

  //generate an ultrasound for 10 microseconds then turn off the transmitter.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //using the formula shown in the guide, calculate the distance
  distance = duration*0.034/2;

  //print the distance in Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
