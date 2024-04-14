/*
   Credits: www.plusivo.com

   Lesson 32: OTA Upload

   Mode details about the code can be found in the guide.
*/

#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>

const char* ssid = "..............";
const char* password = "..........";

ESP8266WebServer server(80);

//the int variable "LED" stores the pin used by the LED
const int LED = D6;

String storage = "";

String page =
R"(
<html lang='en'>
    <head>
        <title>Play with an LED</title>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.1.0/css/all.css'/>
        <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css'/>
        <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    </head>
    <body>
    <div class='container-fluid text-center'>
        <div class='row text-center'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Let's play with a bulb.</p>
            </div>
        </div>
        
        <div class='row'>
            <div  class='col-sm-12'>
                <i id='id_bulb' class='fas fa-lightbulb' style='font-size:25vh'></i>
            </div>
        </div>
            <br>
        <div class='row'>
            <div  class='col-sm-12' style='font-size:7vh'>
                <p>Click the button:</p>
            </div>
        </div>
        
        <div class='row'>
            <div  class='col-sm-12'>
                <input type='button' class='btn btn-primary' id='id_button' value='off'  style='font-size:7vh'>
            </div>
        </div>
    </div>
    
    <script>
    clicked = 1;
    $(document).ready(function(){
        $('input').click(function(){
            var color = clicked ? 'orange' : 'black';
            var button = clicked ? 'On' : 'Off';
            
            $.ajax({
              url:'/led',
              type: 'POST',
              data: {state: button},
            });
            
            $('#id_bulb').css('color', color);
            $('#id_button').val(button);
            clicked = !clicked;
        });
    });
    </script>
    </body>
</html>
)";

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
  server.on("/", htmlIndex);
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
  
  //call the two functions used to connect connect to wifi
  //and setup the server
  connectToWiFi();
  setupServer();

  //wait 4 s for the server to start
  delay(4000);

  //initialise the OTA
  //in setup we need to put only this command because
  //we have a separate function for connecting to WiFi
  ArduinoOTA.begin();
  
}
void loop()
{
  ArduinoOTA.handle();
  
  //the method below is used to manage the incoming request 
  //from the user
  server.handleClient();
}

