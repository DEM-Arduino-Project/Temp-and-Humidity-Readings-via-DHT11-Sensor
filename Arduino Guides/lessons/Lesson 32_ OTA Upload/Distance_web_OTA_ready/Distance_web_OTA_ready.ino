/*
   Credits: www.plusivo.com

   Lesson 32: OTA Upload

   More information about the code can be found in the guide.
  
*/

#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>

//declare the pins used by the module
const int echoPin = D5; 
const int trigPin = D3;

//declare 2 variables which help us later to calculate the distance
long duration;
double distance;

const char* ssid = "..............";
const char* password = "..........";

ESP8266WebServer server(80);

const char* page =
R"(
 <html>  

  <head> 
    <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    <title> Plusivo </title> 
    <script> 
    $(document).ready(function(){ 
          setInterval(refreshFunction,100); 
          });

    function refreshFunction(){ 
      $.getJSON('/refresh' , function(result){  
        $('#Distance').html(result.Distance);  
      }); 
      } 
            
    </script> 
  </head> 

  <body> 
    <h2>Hello from Plusivo!</h2> 

    <table style='font-size:20px'>  
    <tr>  
      <td> 
        <div>Distance:  </div>
      </td>
      <td> 
        <div id='Distance'> </div> 
      </td>
     </tr> 
    </table>  

 
 </body> </html> 
 )";

void json_refresh(){
  
  char Distance[60] = R"(
    {
    "Distance":  %.2f
    }
   )";
  
  char messageFinal[100];
  
  sprintf(messageFinal, Distance, distance);
  server.send(200, "application/javascript", messageFinal);
}

//the htmlIndex() is called everytime somebody access the address
//of the board in the browser and sends back a message.
void htmlIndex() 
{
  //send the message to the user
  server.send(200, "text/html", page);
}

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
  //display the IP assigned to it in the serial manager.
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void setupServer()
{ 
  //the method "server.on()" is to call a function when
  //the user access the location
  //the default location is "/"
  server.on("/", htmlIndex);
 
  server.on("/refresh", json_refresh);
 
  //start the server
  server.begin();
  
  //print in serial manager that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  //the trigger pin (transmitter) must be set as OUTPUT  
  pinMode(trigPin, OUTPUT); 

  //the echo pin (receiver) must be set as INPUT
  pinMode(echoPin, INPUT); 

  //start the Serial communication at 115200 bits/s
  Serial.begin(115200);
  
  //wait 1s so the serial communication has enough time to start
  delay(1000);

  //call the two functions used to connect to wifi
  //and setup the web server
  connectToWiFi();
  setupServer();

  //initialise the OTA
  //in setup we need to put only this command because
  //we have a separate function for connecting to WiFi
  ArduinoOTA.begin();
}
 
void loop() 
{
  ArduinoOTA.handle();
  
  //the method below is used to manage the incoming requests 
  //from the user
  server.handleClient();

  //set the trigPin LOW in order to prepare for the next reading
  digitalWrite(trigPin, LOW);
  
  //delay for 2 microseconds 
  delayMicroseconds(2);

  //generate a ultrasound for 10 microseconds then turn off the transmitter.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //using the formula shown in the guide, calculate the distance
  distance = duration*0.034/2;
}
