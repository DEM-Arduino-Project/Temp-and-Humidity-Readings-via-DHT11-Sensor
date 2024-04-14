/*
 * Credits: www.plusivo.com
 * 
 * Lesson 14: Potentiometer and Servo Motor
 * 
 * A new instruction used in this code is "analogRead(pin)". On the board
 * included in the kit, there is only one analog pin (A0) that is able to read
 * the voltage between 0 V and 3.3 V. However, "analogRead(pin)" returns a value
 * between 0 (0 V) and 1024 (3.3 V).
 * 
 * Information about the connections can be found in the guide.
 * 
 */

//the library "Servo.h" is used to control a servo motor using 
//PWM technique
#include <Servo.h>

//declare a new object called servo
Servo servo;

void setup() 
{
  //start the serial communication with the computer at 115200 bits/s
  Serial.begin(115200);

  //attach the servo on digital pin D1
  servo.attach(D1);
}

void loop() 
{
  //read the value on pin A0
  //the pin is able to read a value between 0 and 1024 corresponding
  //to 0 V and 3.3 V
  int value = analogRead(A0);

  //remap the analog value to a new range (from 0 to 180) as the
  //servo can turn max 180 degrees.
  value = map(value, 0, 1024, 0, 180);
  
  //turn the servo motor accordingly to the angle stored in value
  servo.write(value);

  //print in Serial Monitor the current angle of the servo
  Serial.print("Angle: ");
  Serial.println(value);

  //pause the code for 50ms;
  delay(50);
}
