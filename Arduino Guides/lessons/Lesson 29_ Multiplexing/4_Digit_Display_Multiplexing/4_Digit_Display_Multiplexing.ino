/*
 * Credits: www.plusivo.com
 * 
 * Lesson 29: Multiplexing
 * 
 * The code below is created for the lesson 4 Digit 7 Segment Display,
 * where you will learn how to use multiple shift registers
 * to display numbers on a 4 Digit 7 Segment Display.
 * 
 * This program is tuned so that on the display can be use as a counter
 * from 0 to 1000 seconds (999.9 maximum showed on the display).
 * 
 * Make sure you made the right connections and connected the cables
 * in the order showed in the guide.
 * 
 * More details about the code can be found in the guide.
 * 
 */

//declare the pins used by the shift registers
const int dataPin = D8;
const int latchPin = D7;
const int clockPin = D6;

//declare a byte variable to store the current digit active
byte digit;

//declare a long variable to count how many times the loop()
//function ran
long n = 0;

//the next boolean variable will tell us when the third digit
//is active, so the dot next to it will turn on
boolean dot;

//fine-tuning value for clock
//at the time of writing the code, with this exact final code,
//this value was right and the loop function was running every 1 ms
//so the value on the third digit will increase every 1 second
//creating a good cronometer, and can count 1000 seconds
const int time_to_wait = 150;

void setup()
{
  //set the pins used by the shift registers to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //wait 1 s before start counting
  delay(1000);
}

//this function is used to select the digit to be turned on
void Digit(int x)
{
  //turn off all the digits and segments
  //because we use a common cathode display, to turn off the digits
  //we have to set them to HIGH 
  //15 written as 8 bits is B00001111 
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 15);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, 1);

  //reset the dot variable
  dot = 0;

  //the switch statement is used to select the right digit
  switch(x)
  {
  case 1: 
    //prepare to turn on only the first digit
    digit = 14; //B00001110
    //break is used to get out from the switch function
    break;
  case 2:
    //prepare to turn on only the second digit 
    digit = 13; //B00001101
    break;
  case 3: 
    //prepare to turn on only the third digit
    digit = 11; //B00001011
    break;
  default: 
    //prepare to turn on only the fourth digit
    digit = 7; //B00000111
    break;
  }
}

//this function is used to select a number to display
void Number(int x)
{
  //this if statement is used to decide if the third digit is 
  //selected to be turned on, then execute the first switch
  //else execute the one with the dot turned off
  //the functions zero() and zero_no_dot(), one() and one_no_dot()
  //and so on, are similar, the only difference is in the 8-th bit, which
  //is the bit used by the dots and in the simple functions(zero, one, two etc.)
  //it is set to HIGH (on), but in the ones ending with _no_dot( zero_no_dot, one_no_dot
  //etc.) the 8-th bit is set to LOW (off)
  if(dot == 1)
  {
    //deppending on the value of x, using the switch statement
    //we are calling a specific function to display on the selected 
    //digit a number indicated by the name of the function
    //with the bit for the dots set to HIGH
    switch(x)
    {
      default: 
        zero(); 
        break;
      case 1: 
        one(); 
        break;
      case 2: 
        two(); 
        break;
      case 3: 
        three(); 
        break;
      case 4: 
        four(); 
        break;
      case 5: 
        five(); 
        break;
      case 6: 
        six(); 
        break;
      case 7: 
        seven(); 
        break;
      case 8: 
        eight(); 
        break;
      case 9: 
        nine(); 
        break;
    }
  }
  else
  {
    //deppending on the value of x, using the switch function
    //we are calling a specific function to display on the selected 
    //digit a number indicated by the name of the function
    //with the bit for the dots set to LOW
    switch(x)
    {
      default: 
        zero_no_dot(); 
        break;
      case 1: 
        one_no_dot(); 
        break;
      case 2: 
        two_no_dot(); 
        break;
      case 3: 
        three_no_dot(); 
        break;
      case 4: 
        four_no_dot(); 
        break;
      case 5: 
        five_no_dot(); 
        break;
      case 6: 
        six_no_dot(); 
        break;
      case 7: 
        seven_no_dot(); 
        break;
      case 8: 
        eight_no_dot(); 
        break;
      case 9: 
        nine_no_dot(); 
        break;
     }
  }
}

void loop()
{
  //select first digit
  Digit(1);
  //display a number from 0 to 9
  //because the loop function has to run 100 times per second, 
  //we use n/100 to get a 4 digit number and
  // result/1000%10 for first digit
  // result/100%10 for second digit
  // result/10%10 for third digit
  // result%10 for the fourth digit
  Number((n/100/1000)%10);
  delayMicroseconds(time_to_wait);

  //select second digit
  Digit(2);
  //show a number on the display
  Number((n/100/100)%10);
  delayMicroseconds(time_to_wait);

  //select third digit
  Digit(3);
  //change the dot variable so the following functions know
  //that we are at the third digit and turn on the dot
  dot = 0b10000000;
  //show a number on the third digit of the display
  Number((n/100/10)%10);
  delayMicroseconds(time_to_wait);

  //select fourth digit
  Digit(4);
  //show a number on the fourth digit of the display
  Number((n/100)%10);
  delayMicroseconds(time_to_wait);

  //increment the number
  n++;

  //we have a four digit display, multiplied by 100
  //we will obtain a 6 digit number, but the loop function
  //will run over and over again, so we have to reset the counter 
  //when on our display the number 9999 will appear
  if(n == 1000000)
  {
    n = 0;
  }
}

void zero()
{
  //display on the selected digits a "0"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 191); //B10111111
  digitalWrite(latchPin, 1);
}

void zero_no_dot()
{
  //display on the selected digits a "0"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 63); //B00111111
  digitalWrite(latchPin, 1);
}

void one()
{
  //display on the selected digits a "1"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 134); //B10000110
  digitalWrite(latchPin, 1);
}

void one_no_dot()
{
  //display on the selected digits a "1"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 6); //B00000110
  digitalWrite(latchPin, 1);
}
 
void two()
{
  //display on the selected digits a "2"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 219); //B11011011
  digitalWrite(latchPin, 1);
}

void two_no_dot()
{
  //display on the selected digits a "2"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 91); //B01011011
  digitalWrite(latchPin, 1);
}
 
void three()
{
  //display on the selected digits a "3"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 207); //B11001111
  digitalWrite(latchPin, 1);
}

void three_no_dot()
{
  //display on the selected digits a "3"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 79); //B01001111
  digitalWrite(latchPin, 1);
}
 
void four()
{
  //display on the selected digits a "4"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 230); //B11100110
  digitalWrite(latchPin, 1);
}

void four_no_dot()
{
  //display on the selected digits a "4"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 102); //B01100110
  digitalWrite(latchPin, 1);
}
 
void five()
{
  //display on the selected digits a "5"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 237); //B11101101
  digitalWrite(latchPin, 1);
}

void five_no_dot()
{
  //display on the selected digits a "5"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 109); //B01101101
  digitalWrite(latchPin, 1);
}
 
void six()
{
  //display on the selected digits a "6"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 253); //B11111101
  digitalWrite(latchPin, 1);
}

void six_no_dot()
{
  //display on the selected digits a "6"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 125); //B01111101
  digitalWrite(latchPin, 1);
}
 
void seven()
{
  //display on the selected digits a "7"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 135); //B10000111
  digitalWrite(latchPin, 1);
}

void seven_no_dot()
{
  //display on the selected digits a "7"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 7); //B00000111
  digitalWrite(latchPin, 1);
}
 
void eight()
{
  //display on the selected digits a "8"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 255); //B11111111
  digitalWrite(latchPin, 1);
}

void eight_no_dot()
{
  //display on the selected digits a "8"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 127); //B01111111
  digitalWrite(latchPin, 1);
}
 
void nine()
{
  //display on the selected digits a "9"
  //and the dots are turned on
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 239); //B11101111
  digitalWrite(latchPin, 1);
}

void nine_no_dot()
{
  //display on the selected digits a "9"
  //and the dots are turned off
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  shiftOut(dataPin, clockPin, MSBFIRST, 111); //B01101111
  digitalWrite(latchPin, 1);
}
