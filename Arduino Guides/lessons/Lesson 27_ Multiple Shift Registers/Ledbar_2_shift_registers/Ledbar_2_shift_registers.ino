/*
 * Credits: www.plusivo.com
 * 
 * Lesson 27: Multiple Shift Registers
 * 
 * The code below is created for the lesson "Multiple Shift Registers",
 * where you will learn how to use multiple shift registers
 * and using only three pins from the development board.
 * 
 * In this example we are using two shift registers, but you can
 * connect multiple shift registers and obtain "infinite"
 * pins on your development board.
 * 
 * More details can be found in the guide.
 * 
 */
 
//declare the pins used by the shift register
const int dataPin = D8;
const int latchPin = D7;
const int clockPin = D6;

void setup() 
{
  //start the Serial communication at 115200 bits/s
  Serial.begin(115200);

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

  //turn On the LEDs and show a charging effect
  charging();

  //wait 500 ms
  delay(500);

  another_effect();

  //wait 500 ms
  delay(500);

  barcode();

  //wait 500 ms
  delay(500);
}

//the following function is used to turn each LED of
//the ledbar On for 1 s
void individual()
{
  //declaration of a 16 bit variable with the most 
  //significant bit set to HIGH
  uint16_t led = 0b0000000000000001;
  
  //using the for loop we are going to send each byte
  //data to the shift register and turn on the individual
  //LEDs
  for(int i = 0; i < 10; i++)
  { 
    byte high_byte = led >> 8;
    byte low_byte = led;
    
    //set the clock pin LOW before shiftOut() call
    digitalWrite(clockPin, LOW);
    
    //set latchPin to LOW so the LEDs don't flash while
    //sending in bits
    digitalWrite(latchPin, 0);

    //shift out the high byte
    shiftOut(dataPin, clockPin, MSBFIRST, high_byte);
    //shift out the low byte
    shiftOut(dataPin, clockPin, MSBFIRST, low_byte);

    //copy the values to the latch register
    digitalWrite(latchPin, 1);

    //left shift with one position
    led = led << 1;

    //wait 1 s before the next instruction
    delay(1000);
  }

  //send a 0 byte value to turn all the LEDs off
  //before any other instruction
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);
}

//the following function is used to create a charging effect
void charging()
{
  //declare an 16 bit array to store the states for the 
  //10 LEDs connected to the shift registers
  uint16_t charging_array[] = 
  {
    0b0000000000000001,
    0b0000000000000011,
    0b0000000000000111,
    0b0000000000001111,
    0b0000000000011111,
    0b0000000000111111,
    0b0000000001111111,
    0b0000000011111111,
    0b0000000111111111,
    0b0000001111111111
  };
    
  for(int i = 0; i < 10; i++)
  { 
    byte high_byte = charging_array[i] >> 8;
    byte low_byte = charging_array[i];
    
    //set the clock pin LOW before shiftOut() call
    digitalWrite(clockPin, LOW);

    //set latchPin to LOW so the LEDs don't flash while
    //sending in bits
    digitalWrite(latchPin, 0);

    //the if statement is used to differentiate the shift registers
    //shift out the high byte
    shiftOut(dataPin, clockPin, MSBFIRST, high_byte);
    //shift out the low byte
    shiftOut(dataPin, clockPin, MSBFIRST, low_byte);

    //copy the values to the latch register
    digitalWrite(latchPin, 1);

    //wait 500 ms
    delay(500);
  }

  //send a 0 byte value to turn all the LEDs off
  //before any other instruction
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);
}

void another_effect()
{
  uint16_t effect[] = 
  {
    0b0000001000000001,
    0b0000000100000010,
    0b0000000010000100,
    0b0000000001001000,
    0b0000000000110000,
    0b0000000001001000,
    0b0000000010000100,
    0b0000000100000010,
    0b0000001000000001
  };
  
  for(int i = 0; i < 9; i++)
  { 
    byte high_byte = effect[i] >> 8;
    byte low_byte = effect[i];
    
    //set the clock pin LOW before shiftOut() call
    digitalWrite(clockPin, LOW);

    //set latchPin to LOW so the LEDs don't flash while
    //sending in bits
    digitalWrite(latchPin, 0);
 
    //shift out the high byte
    shiftOut(dataPin, clockPin, MSBFIRST, high_byte);
    //shift out the low byte
    shiftOut(dataPin, clockPin, MSBFIRST, low_byte);

    //copy the values to the latch register
    digitalWrite(latchPin, 1);

    //wait 500 ms
    delay(500);
  }

  //send a 0 byte value to turn all the LEDs off
  //before any other instruction
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);
}

void barcode()
{
  uint16_t barcode_array[] = 
  {
    0b0000001001001001,
    0b0000000100100100,
    0b0000000010010010
  };

  //repeat 10 times
  for(int i = 0; i < 10; i++)
  { 
    //set the clock pin LOW before shiftOut() call
    digitalWrite(clockPin, LOW);

    //set latchPin to LOW so the LEDs don't flash while
    //sending in bits
    digitalWrite(latchPin, 0);
    //shift out the high byte
    shiftOut(dataPin, clockPin, MSBFIRST, barcode_array[0] >> 8);
    //shift out the low byte
    shiftOut(dataPin, clockPin, MSBFIRST, barcode_array[0]);
    //copy the values to the latch register
    digitalWrite(latchPin, 1);
    delay(200);

    digitalWrite(latchPin, 0);
    //shift out the high byte
    shiftOut(dataPin, clockPin, MSBFIRST, barcode_array[1] >> 8);
    //shift out the low byte
    shiftOut(dataPin, clockPin, MSBFIRST, barcode_array[1]);
    //copy the values to the latch register
    digitalWrite(latchPin, 1);
    delay(200);

    digitalWrite(latchPin, 0);
    //shift out the high byte
    shiftOut(dataPin, clockPin, MSBFIRST, barcode_array[2] >> 8);
    //shift out the low byte
    shiftOut(dataPin, clockPin, MSBFIRST, barcode_array[2]);
    //copy the values to the latch register
    digitalWrite(latchPin, 1);
    delay(200);
  }

  //send a 0 byte value to turn all the LEDs off
  //before any other instruction
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);
}

