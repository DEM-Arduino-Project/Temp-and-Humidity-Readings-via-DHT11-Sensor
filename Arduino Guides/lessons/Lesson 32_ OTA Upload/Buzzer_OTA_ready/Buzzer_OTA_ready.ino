/*
   Credits: www.plusivo.com

   Lesson 32: OTA Upload

   In this code we will turn on the buzzer, at a frequency of 1000Hz,
   for one second, and then turn off the buzzer for one second, turn on the buzzer,
   at a frequency of 500Hz, for one second, and then turn off the buzzer for
   one second, and the code will do this instructions over and over again.
   More information about the connection can be found in the guide.
   
*/

#include <ArduinoOTA.h>

const char* ssid = "..............";
const char* password = "..........";
  
//define the pin used by the buzzer
const int buzzer = D6;

void setup()
{
  //set the mode of the pin used by the buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);

  //start the serial communication with the computer at 115200 bits/s
  Serial.begin(115200);

  //print a message into the Serial Monitor
  Serial.println("Booting");
  
  WiFi.mode(WIFI_STA);

  //connect to the WiFi network using the ssid and password strings
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  //initialise the OTA
  ArduinoOTA.begin();

  //display the IP of the board in Serial Monitor
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  ArduinoOTA.handle();
  
  //turn on the buzzer and wait 1 s
  //we use a frequency of 1kHz(1000Hz)
  //you can change this frequency so the sound can be
  //more pleasant
  tone(buzzer, 1000);
  delay(1000);

  //turn off the buzzer and wait 1 s
  noTone(buzzer);
  delay(1000);

  //turn on the buzzer at a frequency
  //of 500Hz and wait 1 s
  tone(buzzer, 500);
  delay(1000);

  //turn off the buzzer
  noTone(buzzer);
  delay(1000);
}

