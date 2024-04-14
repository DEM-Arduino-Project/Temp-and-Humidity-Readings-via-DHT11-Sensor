/*
 * Credits: https://www.plusivo.com
 *
 * Lesson 4: Motor Control
 * 
 * In this lesson, you will learn how to control a DC motor.
 * 
 * Make sure you have connected the components correctly according 
 * to the guide.
 *
 * More information about the connection can be found in the guide.
 * 
 */


//the int variable "motorspeed_pin" stores the pin used to control the speed of the motor
const int motorspeed_pin = D5;

//the next two variables store the pins used to control the direction of the motor
const int DIRA = D6;
const int DIRB = D7;

//the int variable "delayOn" stores the time (in miliseconds) for the motor to remain on
const int delayOn = 3000;

//the int variable "delayOff" stores the time (in miliseconds) for the motor to remain off
const int delayOff = 1500;

//the setup function runs only once when the board is powered
void setup() 
{
  //the following instruction initialises the pin stored in the
  //variable motorspeed_pin(also DIRA and DIRB) as OUTPUT
  pinMode(motorspeed_pin, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
}

//this function is used to turn off the motor
void turnOff()
{
  //this instruction is used to set the speed of the motor to 0 (off)
  digitalWrite(motorspeed_pin, LOW);
  //in these instructions the state is irrelevant because the motor is off 
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  //wait 1.5 seconds
  delay(delayOff);
}

void loop() 
{
  //this instruction is used to set the maximum speed of the motor
  digitalWrite(motorspeed_pin, HIGH);
  //these instructions are used to turn on the motor in one direction
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  delay(delayOn);

  //turn off the motor
  turnOff();

  //this instruction is used to set the maximum speed of the motor
  digitalWrite(motorspeed_pin, HIGH);
  //these instructions are used to turn on the motor in the opposite direction
  digitalWrite(DIRB, HIGH);
  digitalWrite(DIRA, LOW);
  //wait 3 seconds
  delay(delayOn);

  //turn off the motor
  turnOff();

  //this instruction sets the motor speed to about 50%
  //you can put any integer from 0 to 1023
  analogWrite(motorspeed_pin, 512);
  //these instructions are used to turn on the motor in one direction
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  //wait 3 seconds
  delay(delayOn);

  //turn off the motor
  turnOff();

  //this instruction sets the motor speed to about 50%
  analogWrite(motorspeed_pin, 512);
  //these instructions are used to turn on the motor in the opposite direction
  digitalWrite(DIRB, LOW);
  digitalWrite(DIRA, HIGH);
  //wait 3 seconds
  delay(delayOn);

  //turn off the motor
  turnOff();
}
