/*
 * Credits: www.plusivo.com
 * 
 * Lesson 26: Shift Register
 * 
 * The code below is created for the lesson "Shift Register",
 * where you will learn how to use a shift register to get 
 * more pins for your development board, using the 74HC595
 * Serial to Parallel Converter.
 * 
 * More details can be found in the guide.
 * 
 */

//declare the pins used by the shift register
const int dataPin = D8;
const int latchPin = D7;
const int clockPin = D6;

//declare two pins used by the remaining LEDs
const int led_9 = D1;
const int led_10 = D2;

void setup() 
{
  //start the Serial communication at 115200 bits/s
  Serial.begin(115200);

  //set the pins used by the two LEDs to output
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() 
{
  //turn On each LED and wait 1 s
  individual();

  //wait 500 ms before the next effect
  delay(500);

  //turn On the LED and show a charging effect
  charging();

  //wait 500 ms
  delay(500);
}

//the following function is used to turn each LED of
//the ledbar On for 1 s
void individual()
{
  //declare byte data types to be sent to the 
  //shift register
  //a byte data stores 8 bits that corresponds 
  //to the 8 outputs of the shift register
  //"0" represents LOW state, and "1" HIGH
  byte first_led = 1;    //equivalent: 0b00000001
  byte second_led = 2;   //equivalent: 0b00000010
  byte third_led = 4;    //equivalent: 0b00000100
  byte fourth_led = 8;   //equivalent: 0b00001000
  byte fifth_led = 16;   //equivalent: 0b00010000
  byte sixth_led = 32;   //equivalent: 0b00100000
  byte seventh_led = 64; //equivalent: 0b01000000
  byte eighth_led = 128; //equivalent: 0b10000000
  
  //store the 8 byte variables into an array
  byte led[] = 
  {
    first_led, second_led, third_led, fourth_led, 
    fifth_led, sixth_led, seventh_led, eighth_led
  };
 
  //using the for loop we are going to send each byte
  //data to the shift register and turn on the individual
  //LEDs
  for(int i = 0; i < 8; i++)
  { 
    //set the clock pin LOW before shiftOut() call
    digitalWrite(clockPin, LOW);
    
    //set latchPin to LOW so the LEDs don't flash while
    //sending in bits
    digitalWrite(latchPin, 0);
    
    //shift the 8 bits out with Most Significant Bit First
    shiftOut(dataPin, clockPin, MSBFIRST, led[i]);

    //copy the values to the latch register
    digitalWrite(latchPin, 1);

    //wait 1 s before the next instruction
    delay(1000);
  }

  //send a 0 byte value to turn all the LEDs off
  //before any other instruction
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);

  //turn On the nineth LED of the ledbar
  //for 1 s
  digitalWrite(led_9, HIGH);
  delay(1000);
  digitalWrite(led_9, LOW);

  //turn On the tenth LED of the ledbar
  //for 1 s
  digitalWrite(led_10, HIGH);
  delay(1000);
  digitalWrite(led_10, LOW);
}

//the following function is used to create a charging effect
void charging()
{
  //declare an byte array to store the states for the 
  //8 LEDs connected to the shift register
  byte charging_array[] = 
  {
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
    0b11111111
  };
  
  for(int i = 0; i < 8; i++)
  { 
    //set the clock pin LOW before shiftOut() call
    digitalWrite(clockPin, LOW);

    //set latchPin to LOW so the LEDs don't flash while
    //sending in bits
    digitalWrite(latchPin, 0);

    //shift the 8 bits out with Most Significant Bit First
    shiftOut(dataPin, clockPin, MSBFIRST, charging_array[i]);

    //copy the values to the latch register
    digitalWrite(latchPin, 1);

    //wait 500 ms
    delay(500);
  }

  //turn On the nineth LED and wait 500 ms
  digitalWrite(led_9, HIGH);
  delay(500);

  //turn On the tenth LED and wait 500 ms
  digitalWrite(led_10, HIGH);
  delay(500);

  //turn Off all the LEDs of the ledbar
  digitalWrite(led_9, LOW);
  digitalWrite(led_10, LOW);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);
}


