/*
   Credits: www.plusivo.com
   
   Lesson 18: Dim an RGB LED from web
   
   The code below is created for the lesson "Dim an RGB LED from 
   web", where we will define a slider for each colour of the
   RGB LED and controlling the individual brightnesses.

   More information about the code can be found in the guide.
*/

#include<ESP8266WebServer.h>

const char* ssid = ".............";
const char* password = ".........";

ESP8266WebServer server(80);

//create 3 variables that are used to stores the pins to which is the LED
//attached
const int red = D6;
const int green = D7;
const int blue = D8;

String page =
R"(
<html lang='en'>
    <head>
        <title>Dim an RGB LED</title>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.1.0/css/all.css'/>
        <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css'/>
        <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    </head>
    <body>
    <div class='container-fluid text-center'>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Use the sliders to control the brightness.</p>
            </div>
        </div>     
        <br/>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:3vh'>
                Red:
                <b id='status1'></b>
            </div>
        </div> 
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider_red'/>
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:green;font-size:3vh'>
                Green: 
                <b id='status2'></b>
            </div>
        </div> 
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider_green'/>
        </div>

        <div class='row'>
            <div class='col-sm-12' style='color:blue;font-size:3vh'>
                Blue:
                <b id='status3'></b>
            </div>
        </div> 
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider_blue'/>
        </div>
    </div>
    </body>
    
    <script>
        $('#slider_red').on('change', function(){
            var state_slider_red = $('#slider_red').val();
            
            $('#status1').html(state_slider_red + ' %');

            $.ajax({
              url: '/redFunction',
              type: 'POST',
              data: {state1: state_slider_red}
            });
        });

        $('#slider_green').on('change', function(){
            var state_slider_green = $('#slider_green').val();
            
            $('#status2').html(state_slider_green + ' %');

            $.ajax({
              url: '/greenFunction',
              type: 'POST',
              data: {state2: state_slider_green}
            });
        });

        $('#slider_blue').on('change', function(){
            var state_slider_blue = $('#slider_blue').val();
            
            $('#status3').html(state_slider_blue + ' %');

            $.ajax({
              url: '/blueFunction',
              type: 'POST',
              data: {state3: state_slider_blue}
            });
        });
    </script>
</html>
)";

//function for controlling the red LED
void redFunction()
{
  int value1 = server.arg("state1").toInt();
  value1 = map(value1, 0, 100, 0, 1023);

  if(value1 == 0)
     digitalWrite(red, LOW);//turn of the led
  else
     analogWrite(red, value1);//change the brightness of red
  
  server.send(200, "text/html", "red");
}

//function for controlling the green LED
void greenFunction()
{
  int value2 = server.arg("state2").toInt();
  value2 = map(value2, 0, 100, 0, 1023);

  if(value2 == 0)
     digitalWrite(green, LOW);//turn of the led
  else
     analogWrite(green, value2);//change the brightness of green
  
  server.send(200, "text/html", "green");
}

//function for controlling the blue LED
void blueFunction()
{
  int value3 = server.arg("state3").toInt();
  value3 = map(value3, 0, 100, 0, 1023);

  if(value3 == 0)
     digitalWrite(blue, LOW);//turn of the led
  else
     analogWrite(blue, value3);//change the brightness of blue
  
  server.send(200, "text/html", "blue");
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
  //set the WiFi mode to WiFi_STA
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
  server.on("/redFunction", redFunction);
  server.on("/greenFunction", greenFunction);
  server.on("/blueFunction", blueFunction);

  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  //start the Serial communication at 115200 bits/s
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

