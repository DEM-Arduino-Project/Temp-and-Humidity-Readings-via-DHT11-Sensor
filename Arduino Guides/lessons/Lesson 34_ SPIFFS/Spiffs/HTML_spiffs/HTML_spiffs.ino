/*
   Credits: www.plusivo.com

   Lesson 34: SPIFFS

   The code below is created for the lesson "SPIFFS"
   where you will learn how to send a HTML page to
   a user instead of including it here, in the code.
   
   More information about the code can be found in the guide.
   
*/

#include "FS.h"
#include <ESP8266WebServer.h>

const char* ssid = "..............";
const char* password = "..........";

ESP8266WebServer server(80);

void connectToWiFi()
{ 
  Serial.println("Connecting to the WiFi");
  WiFi.mode(WIFI_STA);

  //connect to the WiFi network using the ssid and password strings
  WiFi.begin(ssid, password);

  //below we check the status of the WiFi and wait until the
  //board is connected to the network
  Serial.println("Waiting for connection");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //when the board is successfully connected to the network,
  //display the IP assigned to it in the Serial Monitor.
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupServer()
{ 
  //serve the file located in the root directory
  server.serveStatic("/", SPIFFS, "/index.html");
  
  //start the server
  server.begin();
  //print in serial manager that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup(void) 
{
  //start the Serial communication at 115200 bits/s
  Serial.begin(115200);
  
  //wait 1 s until the Serial communication is started
  delay(1000);

  if (SPIFFS.begin()) 
  {
      Serial.println("SPIFFS Active");
  } 
  else 
  {
      Serial.println("Unable to activate SPIFFS");
  }
  
  //call the two functions used to connect connect to wifi
  //and setup the server
  connectToWiFi();
  setupServer();
}

void loop() 
{
  //the method below is used to manage the incoming request 
  //from the user
  server.handleClient();
}
