/*
   Credits: www.plusivo.com

   Lesson 11: Play songs with a buzzer
   
   The code below is created for the lesson "Play songs with a buzzer"
   where you will learn how to create simple songs and play them
   using a buzzer.

   If you know the frequencies of the notes and have a good musical ear,
   you can compose more complicated songs.
   
   More information about the connections can be found in the guide.
   
*/

//define the frequencies of the notes
//for all the 7 octaves
//these notes have an error because we 
//declared them as integers and not floats
const int c8 = 4187;
const int b7 = 3951;
const int a7 = 3520;
const int g7 = 3136;
const int f7 = 2794;
const int e7 = 2637;
const int d7 = 2349;
const int c7 = 2093;
const int b6 = 1975;
const int a6 = 1760;
const int g6 = 1568;
const int f6 = 1397;
const int e6 = 1318;
const int d6 = 1174;
const int c6 = 1046;
const int b5 = 988;
const int a5 = 880;
const int g5 = 784;
const int f5 = 698;
const int e5 = 659;
const int d5 = 587;
const int c5 = 523;
const int b4 = 494;
const int a4 = 440;
const int g4 = 392;
const int f4 = 349;
const int e4 = 330;
const int d4 = 293;
const int c4 = 261;
const int b3 = 247;
const int a3 = 220;
const int g3 = 196;
const int f3 = 174;
const int e3 = 165;
const int d3 = 146;
const int c3 = 130;
const int b2 = 123;
const int a2 = 110;
const int g2 = 97;
const int f2 = 87;
const int e2 = 82;
const int d2 = 73;
const int c2 = 65;
const int b1 = 61;
const int a1 = 55;
const int g1 = 49;
const int f1 = 43;
const int e1 = 41;
const int d1 = 37;
const int c1 = 33;

//define the pin used by the buzzer
const int buzzer = D6;

//define the pins used by the buttons
const int button1 = D1;
const int button2 = D2;

void setup()
{
  //set the modes of the pins
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}
 
void loop()
{
  //if the first button was pressed, play the first song
  if(digitalRead(button1) == 0)
  {
    //play ABC Alphabet song
    abc_song();
  }

  //if the second button was pressed, play the second song
  if(digitalRead(button2) == 0)
  {
    //play the second song
    old_mcdonald(); 
  }
}

//when calling this function, the buzzer will
//play the ABC Alphabet song
void abc_song()
{
  //define the waiting times
  int delay1 = 700;
  int delay2 = 1000; 
  int delay3 = 300;
  int delay4 = 100;

  //play every note indicated for delay1 (or delay2, or delay3)
  //milliseconds, then turn off the buzzer for delay4 milliseconds
  //then play the next note
  
  //first sequence
  //play: C C G G A A G
  tone(buzzer, c7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, c7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, g7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, g7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, a7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, a7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, g7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  //second sequence
  //play: F F E E D D D D C
  tone(buzzer, f7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, f7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, d7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, d7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, d7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, d7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);
 
  tone(buzzer, c7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  //third sequence
  //play: G G F E E D
  tone(buzzer, g7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, g7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, f7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, d7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  //fourth sequence
  //play: G G G F E E D
  tone(buzzer, g7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, g7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, g7);
  delay(delay3);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, f7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, d7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  //fifth sequence
  //play: C C G G A A G
  tone(buzzer, c7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, c7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, g7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, g7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, a7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, a7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, g7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);

  //sixth sequence
  //play: F F E E D D C
  tone(buzzer, f7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, f7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, e7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, d7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);
  
  tone(buzzer, d7);
  delay(delay1);
  noTone(buzzer);
  delay(delay4);

  tone(buzzer, c7);
  delay(delay2);
  noTone(buzzer);
  delay(delay4);
}

//when calling this function, the buzzer will
//play the Old Mcdonald had a farm song
void old_mcdonald()
{
  
  //play every note indicated for time1 (or time2, 
  //or time3, or time4, or time5) milliseconds, 
  //then turn off the buzzer for time0 milliseconds
  //then play the next note
  int time0 = 100;
  int time1 = 300;
  int time2 = 600;
  int time3 = 900;
  int time4 = 550;
  int time5 = 200;

  //first part
  //play: C C C G A A G
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, a4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, a4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time2);
  noTone(buzzer);
  delay(time0);

  //second part
  //play: E E D D C
  tone(buzzer, e4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, e4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, d4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, d4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time3);
  noTone(buzzer);
  delay(time0);

  //third part
  //play: G C C C G A A G
  tone(buzzer, g3);
  delay(time4);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time4);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, a4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, a4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time2);
  noTone(buzzer);
  delay(time0);

  //fourth part
  //play: E E D D C
  tone(buzzer, e4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, e4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, d4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, d4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time3);
  noTone(buzzer);
  delay(time0);

  //fifth part
  //play: G G C C C G G C C C 
  tone(buzzer, g3);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time2);
  noTone(buzzer);
  delay(time0);

  //sixth part
  //play: C C C C C C C C C C C C
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time5);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);

  //seventh part
  //play: C C C G A A G
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, a4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, a4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, g3);
  delay(time2);
  noTone(buzzer);
  delay(time0);

  //eight part
  //play: E E D D C
  tone(buzzer, e4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, e4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, d4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, d4);
  delay(time1);
  noTone(buzzer);
  delay(time0);
  
  tone(buzzer, c4);
  delay(time3);
  noTone(buzzer);
  delay(time0);
}

