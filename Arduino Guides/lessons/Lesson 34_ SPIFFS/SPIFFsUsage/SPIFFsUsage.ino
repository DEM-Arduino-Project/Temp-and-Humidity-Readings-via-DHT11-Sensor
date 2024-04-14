/*
   Credits: www.plusivo.com

   The code below is created for the Lesson , SPIFFS
   where you will learn how to store files on the development
   board.
   
   This is an advanced lesson, and after you master this, 
   you will be able to store web pages, configurations or data
   and will not be erased when the board is powered off.
  
   More information about this lesson can be found in the guide.
   
*/

#include "FS.h"

void setup()
{
  //start the Serial communication at 115200 baudrate
  Serial.begin(115200);

  //wait 1 s
  delay(1000);

  //initialize the SPIFFS and display
  //a message in Serial Monitor if it is available or not
  if (SPIFFS.begin()) 
  {
      Serial.println("SPIFFS Active");
  } 
  else 
  {
      Serial.println("Unable to activate SPIFFS");
  }

  //wait 2 s
  delay(2000);
}

void loop()
{
    //check if there is a file with that name
    //if not show a message in Serial Monitor
    if (SPIFFS.exists("/test.txt")) 
    {
      //open the file
      File f = SPIFFS.open("/test.txt", "r");
      if (!f) 
      {
        //display a message
        Serial.print("Unable To Open");
      } 
      else 
      {
        String s;
        Serial.print("Contents of the file: ");
        Serial.print("/test.txt \n\n");

        //f.position() returns the position of the pointer
        //in the file
        //f.size() returns the size of the file
        while (f.position() < f.size())
        {
          //readStringUntil() reads characters from the 
          //serial buffer into a string
          s = f.readStringUntil('\n');

          //get a version of the String with any leading 
          //and trailing whitespace removed
          s.trim();

          //print the string in Serial Monitor
          Serial.println(s);
        }
        //close the file
        f.close();
      }

      //add new lines in the file
      f = SPIFFS.open("/test.txt", "a");
      if (!f) 
      {
        Serial.print("Unable To Open");
      } 
      else 
      {
        //add new line in the file
        f.println("\n");
        f.println("This is a new line");
        f.close();
      }
      
      //wait 5 s
      delay(5000);

      //display the modified file in Serial Monitor
      f = SPIFFS.open("/test.txt", "r");
      if (!f) 
      {
        Serial.print("Unable To Open");
      } 
      else 
      {
        String s;
        Serial.print("Contents of the file: ");
        Serial.print("/test.txt \n\n");

        while (f.position() < f.size())
        {
          s = f.readStringUntil('\n');
          s.trim();
          Serial.println(s);
        }
        f.close();
      }
    }
    else
    {
      Serial.println("Unable to find \n");
    }

    //wait 10 s
    delay(10000);
}
