/*
 * Credits: www.plusivo.com
 * 
 * Lesson 33: Soft Access Point
 * 
 * The code below is created for the lesson 15 "Soft Access Point"
 * where you will learn how to set the development board in the
 * Soft Access Point mode.
 * 
 * In this project, you don't have to use any external components.
 * 
 * More details about the code can be found in the guide.
 */
 
#include <ESP8266WiFi.h>

//here you have to insert your the desired credentials
const char* ssid = "ssid";
const char* password = "password";

void setup() 
{
  //start the Serial communication at 115200 bits/s
	Serial.begin(115200);
 
  //wait 1 s until the Serial communication is started
  delay(1000);

  //display a message in Serial Monitor
	Serial.print("Configuring access point...");
  
	//set the AP with the ssid and password entered above
	WiFi.softAP(ssid, password);
}

void loop() 
{
	
}
