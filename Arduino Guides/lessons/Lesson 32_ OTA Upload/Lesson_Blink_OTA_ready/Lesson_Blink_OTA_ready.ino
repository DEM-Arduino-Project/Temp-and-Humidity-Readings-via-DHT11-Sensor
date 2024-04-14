/*
 * Credits: https://www.plusivo.com
 *
 * Lesson 32: OTA Upload
 * 
 * More information about the code can be found in the guide.
 */

#include <ArduinoOTA.h>

const char* ssid = "................";
const char* password = "............";

//the int variable "LED" stores the pin used by the LED
const int LED = D6;

//the int variable "delayTime" stores the time (in milliseconds) between the blinks
//1000 milliseconds = 1 second
const int delayTime = 1000;

//the setup function runs only once when the board is powered
void setup() 
{
  pinMode(LED, OUTPUT);

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

// the loop function runs over and over again forever
void loop() 
{
  ArduinoOTA.handle();
  
  //the next two instructions are used to turn off the LED and wait for 1 second
  digitalWrite(LED, LOW);   
  delay(delayTime); 
  
  //the next two instructions are used to turn on the LED and wait for 1 second                  
  digitalWrite(LED, HIGH);  
  delay(delayTime);                     
}
