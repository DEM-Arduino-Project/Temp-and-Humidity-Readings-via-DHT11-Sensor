/*
   Credits: www.plusivo.com

   Lesson 34: SPIFFS
   
*/
#include "FS.h"
#include <ESP8266WebServer.h>

const char* ssid = "..............";
const char* password = "..........";

ESP8266WebServer server(80);

//the int variable "LED" stores the pin used by the LED
const int LED = D6;

String storage = "";


//the led() function is used to turn On and Off the LED
void led()
{
  //server.arg(name) returns the value (as string) of the argument "name"
  storage = server.arg("state");
  
  //if the value returned is "On", we will turn On the LED
  //else, we will turn Off the LED
  if(storage == "On")
  {
    //turn On the LED
    digitalWrite(LED, HIGH);
  }
  else 
  {
    //turn Off the LED
    digitalWrite(LED, LOW);
  }

  //send a message to the user
   server.send(200,"text/html","ok");
}

//connectToWiFi() is used to connect to the WiFi network
//using the SSID and PASSWORD variables created at the
//beginning of the code
void connectToWiFi()
{ 
  Serial.println("Connecting to the WiFi");
  //set the WiFi mode to WiFi_STA.
  //the WiFi_STA means that the board will act as a station,
  //similar to a smartphone or laptop
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
  //display the IP assigned to it in the serial monitor.
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

//setupServer() function is used to set up and organise
//the website
void setupServer()
{ 
  //the method "server.on()" is to call a function when
  //the user access the location
  //the default location is "/"
  server.serveStatic("/", SPIFFS, "/index.html");
  
  server.on("/led", led);

  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  pinMode(LED, OUTPUT);

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

  //wait 4 s for the server to start
  delay(4000);
  
}
void loop()
{
  //the method below is used to manage the incoming request 
  //from the user
  server.handleClient();
}

