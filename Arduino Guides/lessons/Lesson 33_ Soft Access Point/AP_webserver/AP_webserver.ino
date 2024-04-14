/*
 * Credits: www.plusivo.com
 * 
 * Lesson 33: Soft Access Point
 * 
 * The code below is created for the lesson "Soft Access Point"
 * where you will learn how to set the development board in the
 * Soft Access Point mode, set up a web server and display
 * a simple message in the browser.
 * 
 * In this project, you don't have to use any external components.
 * 
 * More details can be found in the guide.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//here you have to insert your the desired credentials
const char* ssid = "ssid";
const char* password = "password";

ESP8266WebServer server(80);

//setupServer() function is used to set up and organise
//the website
void setupServer()
{ 
  //the method "server.on()" is to call a function when
  //the user access the location
  //the default location is "/"
  server.on("/", htmlIndex);

  //start the server
  server.begin();
  //print in serial manager that the HTTP server is started
  Serial.println("HTTP server started");
}

//the htmlIndex() is called everytime somebody access the address
//of the board in the browser and sends back a message.
void htmlIndex() 
{
  //the mssage variable is used to store the message sent to the
  //user
  String message = "Hello world!";

  //send the message to the user
  server.send(200, "text/html", message );
}

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

  //display the server IP address in Serial Monitor
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //call the function used to setup the server
  setupServer();
}

void loop() 
{
  //the method below is used to manage the incoming request 
  //from the user
  server.handleClient();
}
