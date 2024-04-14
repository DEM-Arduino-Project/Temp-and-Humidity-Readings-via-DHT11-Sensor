/*
   Credits: www.plusivo.com

   Lesson 19: Control a motor from web
    
   The code below is created for the lesson "Control a motor from web"
   where you will connect to a WiFi network and host a simple website.
   
   The code consists of 3, main,  custom functions used to connect to the
   WiFi ( "connectToWiFi()"), to setup the server ("setupServer()"),
   and a function that sends a message to the browser ("htmlIndex()"). 

   Also we defined multiple functions for helping us control the motor.
   
*/
#include <ESP8266WebServer.h>

const char* ssid = "..................";
const char* password = "..............";

ESP8266WebServer server(80);

//the int variable "motorspeed_pin" stores the pin used to control the speed of the motor
const int motorspeed_pin = D5;

//the next two variables store the pins used to control the direction of the motor
const int DIRA = D6;
const int DIRB = D7;

//the int variable "motorspeed" stores a value between 0 and 1023
//used with the function analogWrite(pin, value);
//more details can be found in the lesson "Motor Control"
//initially is set to 100%
int motorspeed = 1023;

//below you can find the html page
//here we have define two buttons to set the direction of the motor
//and a slider to ajust the speed of the motor
//more details about the html page can be found in the guide
String page =
R"(
<!doctype html>
<html>
  <head>
    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css'/>
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.1.0/css/all.css'/>
    <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>
  </head>
  <body>
    <div class='container-fluid' style='font-size:10vh;color:red'>
      <div class='row'>
        <div class='col-sm-12 text-center'>
          <h1 id='status'>Control App</h1>
        </div>
      </div>
      
      <div class='row'>
        <div class='col-sm-12 text-center'>
          <i id='button-forward' class='fas fa-chevron-circle-up'></i>
        </div>
      </div>
      
      <div class='row'>
        <div class='col-sm-12 text-center'>
          <i id='button-backward' class='fas fa-chevron-circle-down'></i>
        </div>
      </div>
      
      <div class='row' style='height: 10vh;'> </div>
      
      <div class='row'>
        <div class='col-sm-12 text-center'>
          <h3>Use the slider for adjusting the motorspeed</h3>
        </div>
      </div>
      <div class='row'>
        <div class='col-sm-12 offset-lg-4 col-lg-4'>
          <input type='range' class='form-control-range' id='motorspeed-slider'/>
        </div>
      </div>
      
    </div>
  </body>
       
  <script language='javascript'>
      $('#motorspeed-slider').on('change', function() {
          var variable = $('#motorspeed-slider').val();
              
          $('#status').html('Speed: ' + variable + '%');
          $.ajax({
              url: '/setmotorspeed',
              type: 'POST',
              data: {motorspeed: variable},
          });
      });
            
      $('#button-forward').on('touchstart mousedown', function() {
          $('#status').html('Forward');
          $.ajax('/forward');
      });

      $('#button-forward').on('touchend mouseup', function() {
          $('#status').html('Stop');
          $.ajax('/stopp');
      });
        
      $('#button-backward' ).on('touchstart mousedown', function() {
          $('#status').html('Backward');
          $.ajax('/backward');
      });

      $('#button-backward').on('touchend mouseup', function() {
          $('#status').html('Stop');
          $.ajax('/stopp');
      });
  </script>
</html> 
)";

//the forward() is called for moving the motor in one direction
//(let's say forward)
void forward()
{
  //set the speed of the motor
  analogWrite(motorspeed_pin, motorspeed);
  
  //set the direction of the motor forward
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);

  //send an OK message(see more details below)
  server.send(200,"text/html","forward");

  //display a message in Serial Monitor to 
  //see when the function is called
  Serial.println("Forward");
}

//the backward() is called for moving the motor in the
//opposite direction (backward)
void backward()
{
  //set the speed of the motor
  analogWrite(motorspeed_pin, motorspeed);
  
  //set the direction of the motor backward
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);

  //send an OK message(see more details below)
  server.send(200,"text/html","backward");

  //display a message in Serial Monitor to 
  //see when the function is called
  Serial.println("Backward");
}

//the stopp() function is used to turn off the motor
void stopp()
{ 
  //this instruction is used to set the speed of the motor to 0 (off)
  digitalWrite(motorspeed_pin, LOW);

  //in these instructions the state is irrelevant because the motor is off 
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  
  //send an OK message(see more details below)
  server.send(200,"text/html","stop");

  //display a message in Serial Monitor to 
  //see when the function is called
  Serial.println("Stop");
}

void setmotorspeed()
{
  //server.arg(name) returns the value (as string) of the argument "name"
  //using the method String.toInt(), we convert a String variable to int
  motorspeed = server.arg("motorspeed").toInt();
  
  if(motorspeed == 0)
  {
    motorspeed = 0;
  }
  else
  {
      //map function is used to re-map a number from one range to another
      //map(value, fromLOW, fromHIGH, toLOW, toHIGH);
      //value -> the number to map
      //fromLOW -> the lower bound of the value's current range
      //fromHIGH -> the upper bound of the value's current range
      //toLOW -> the lower bound of the value's target range
      //toHIGH -> the upper bound of the value's target range
      //for "toLow" we started from 200 because 0 is too low to start the motor
      //if using the slider at 1-5%(or more) the motor does not start
      //you can increase the value "toLow" to the point when the motor
      //starts spinning even from 1%
      motorspeed = map(motorspeed, 0, 100, 200, 1023);
  }

  //display a message in Serial Monitor to 
  //see when the function is called
  Serial.println(motorspeed);

  //send an OK message(see more details below)
  server.send(200,"text/html","ok");
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
  while (WiFi.status() != WL_CONNECTED) 
  {
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
  server.on("/", htmlIndex);;
  server.on("/forward", forward);
  server.on("/stopp", stopp);
  server.on("/backward", backward); 
  server.on("/setmotorspeed", setmotorspeed);

  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  //the following instruction initialise the pin stored in the
  //variable motorspeed_pin(also DIRA and DIRB) as OUTPUT
  pinMode(motorspeed_pin, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  //start the Serial communication with a baud rate of 115200
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

