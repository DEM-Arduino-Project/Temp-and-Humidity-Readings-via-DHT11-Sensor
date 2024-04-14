/*
 * Credits: www.plusivo.com
 * 
 * Lesson 15: Wireless Connectivity
 * 
 * The code below is created for the lesson "Wireless Connectivity",
 * where you connect to a WiFi network and host a simple website.
 * 
 * In this project, you don't have to use any external components.
 * The code consists of 3 custom functions used to connect to the
 * WiFi ("connectToWiFi()"), to setup the server ("setupServer()"),
 * and a function that sends a message to the browser ("htmlIndex()").
 * 
 */

#include <ESP8266WebServer.h>

//here you have to insert your wireless network name and password
const char* ssid = "ssid";
const char* password = "password";

//create a new object ESP8266WebServer
//the parameter "80" represents the port that the board listens to.
//if you use a port different than 80, you need to be sure you access it  
//correctly from the browser.
//For example:
//if the ip is 100.32.12.39 and the port is 2093, you have to access 
//the following address: "100.32.12.39:2093"
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
  //You can find on the internet a list with all HTML codes but here
  //are the most used ones:
  //200 -> OK
  //400 -> Bad Request
  //403 -> Forbidden
  //404 -> Not found
  //500 -> Internal Server Error
  int replyCode = 200;

  //contentType refers to the type of the mssage sent to the user
  //The most used ones are:
  // text/plain -> used just for text, without using HTML
  // text/html -> used to create a page using HTML

  String contentType = "text/plain";

  //the mssage variable is used to store the message sent to the
  //user
  String message = "Hello world!";

  //send the message to the user
  server.send(replyCode, contentType, message);
}

//connectToWiFi() is used to connect to the WiFi network
//using the "ssid" and "password" variables created at the
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
  while (WiFi.status() != WL_CONNECTED) 
  {
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

void setup() 
{
  //start the Serial communication at the baudrate 115200
  Serial.begin(115200);
  
  //wait 1 s until the Serial communication is started
  delay(1000);

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
