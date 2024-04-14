/*
   Credits: www.plusivo.com

   Lesson 17: Dim an LED from web

   The code below is created for the lesson "Dim an LED from 
   web", where we will define a slider to control
   the brightness of an LED from a browser

   More information about can be found in the guide.
*/

#include<ESP8266WebServer.h>

const char* ssid = "............";
const char* password = "........";

//create an instance of the ESP8266WebServer
ESP8266WebServer server(80);

//define the pin used by the LED
const int LED = D6;

String page =
R"(
<html lang='en'>
    <head>
        <title>Dim an LED</title>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css'/>
        <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    </head>
    <body>
    <div class='container-fluid text-center'>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Use the slider to control the brightness.</p>
            </div>
        </div>     
        <br/>
        <div class='col-sm-12'>
              <input type='range' min='0' max='100' class='form-control-range' id='slider'/>
        </div>
        <div class='row'>
          <div class='col-sm-12'>
            <h3 id='status'></h3>
          </div>
        </div>   
    </div>
    </body>
    
    <script>
        $('#slider').on('change', function(){
            var state_slider = $('#slider').val();

            $('#status').html('Brightness: ' + state_slider + ' %');
            $.ajax({
              url: '/',
              type: 'POST',
              data: {state: state_slider}
            });
        });
    </script>
</html>
)";

//the htmlIndex() is called everytime somebody access the address
//of the board in the browser and sends back a message.
void htmlIndex() 
{
  //server.arg(name) returns the value (as string) of the argument "name"
  //using the method String.toInt(), we convert a String variable to int
  int value = server.arg("state").toInt();

  //map function is used to re-map a number from one range to another
  //map(value, fromLOW, fromHIGH, toLOW, toHIGH);
  //value -> the number to map
  //fromLOW -> the lower bound of the value's current range
  //fromHIGH -> the upper bound of the value's current range
  //toLOW -> the lower bound of the value's target range
  //toHIGH -> the upper bound of the value's target range
  
  value = map(value, 0, 100, 0, 1023);

  //in case the value is 0, turn off the led using digitalWrite();
  //analogWrite(pin,0) doesn't turn off completely the led
  if(value == 0)
     digitalWrite(LED, LOW); //turn of the led
  else
     analogWrite(LED, value); //change the brightness of the led
     
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
  //the method "server.on()" is to call a function when
  //the user access the location
  //the default location is "/"
  server.on("/", htmlIndex);

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
}

void loop()
{
  //the method below is used to manage the incoming request
  //from the user
  server.handleClient();
}

