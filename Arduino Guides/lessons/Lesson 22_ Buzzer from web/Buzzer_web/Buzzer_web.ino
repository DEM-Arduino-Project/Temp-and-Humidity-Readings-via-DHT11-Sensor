/*
   Credits: www.plusivo.com

   Lesson 22: Buzzer from web

   The code below is created for the Lesson "Buzzer from web"
   where you will learn how to turn On and Off a buzzer 
   from a browser.
   
   Make sure you connected the buzzer correctly as shown in the guide.

   If you do not understand some of the concepts used,
   please check the previous lessons for more details.
   
   More details about the code can be found in the guide.
   
*/

#include <ESP8266WebServer.h>

const char* ssid = ".............";
const char* password = ".........";

//define the pin used by the buzzer
const int buzzer = D6;

String container = "";

ESP8266WebServer server(80);

String page =
R"(
<html lang='en'>
    <head>
        <title>Buzzer control</title>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.1.0/css/all.css'/>
        <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css'/>
        <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
        <style>
            .css_on 
            {
                color: black;
            }
            .css_off 
            {
                color: white;
            }
        </style>
    </head>
    <body>
    <div class='container-fluid text-center'>
        <div class='row text-center'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Click/touch the button.</p>
            </div>
        </div>     
        <div class='row'>
            <div  class='col-sm-12'>
                <input type='button' class='btn btn-primary' id='id_button' value='Off'  style='font-size:7vh'>
            </div>
        </div>
        <br/>
        <div class='row'>
            <div  class='col-sm-12'>
                <i id='speaker' class='fas fa-volume-up css_off' style='font-size:15vh'></i>
            </div>
        </div>   
    </div>
    </body>
    
    <script>
      $(document).ready(function(){
        $('#id_button').click(function(){
            var current_state = $('#speaker').hasClass('css_off');

            if(current_state == true)
            {
                $.ajax({
                  url:'/buzzer_function',
                  type: 'POST',
                  data: {state: 'On'},
                });
                $('#id_button').val('On');
                $('#speaker').removeClass('css_off').addClass('css_on');
            }
            else
            {
                $.ajax({
                  url:'/buzzer_function',
                  type: 'POST',
                  data: {state: 'Off'},
                });
                $('#id_button').val('Off');
                $('#speaker').removeClass('css_on').addClass('css_off');
            }
        });
    });
    </script>
</html>
)";

//the buzzer_function() is used to turn on/off the buzzer
void buzzer_function()
{
  container = server.arg("state");
  if(container == "On")
  {
    //turn on the buzzer at a frequency of 1000Hz
    tone(buzzer, 1000);
  }
  else
  {
    //turn off the buzzer
    noTone(buzzer);
  }
  server.send(200, "text/html", "ok");
}

//the htmlIndex() is called everytime somebody access the address
//of the board in the browser and sends back a message.
void htmlIndex() 
{
  //send the message to the user
  server.send(200, "text/html", page);
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
  server.on("/", htmlIndex);
  server.on("/buzzer_function", buzzer_function);

  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup()
{
  //set the mode of the pin used by the buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);

  //start the Serial communication at the baudrates 115200
  Serial.begin(115200);

  delay(1000);
  
  connectToWiFi();
  setupServer();
}

void loop()
{
  //the method below is used to manage the incoming request 
  //from the user
  server.handleClient();
}
