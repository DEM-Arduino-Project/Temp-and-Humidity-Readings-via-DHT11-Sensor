/*
 * Credits: www.plusivo.com
 * 
 * Lesson 23: Set the frequency of a buzzer from web
 * 
 * The code below is created for the lesson "Set the
 * frequency of a buzzer from web", where you will learn
 * how to fully control a buzzer from a web browser.
 * 
 * More information about the code can be found in the guide.
 */

#include<ESP8266WebServer.h>

const char* ssid = ".............";
const char* password = ".........";

//define the pin used by the buzzer
const int buzzer = D6;

//the following String variable will be used
//to store the last state of the button (On or Off)
String container = "";

//set the initial frequency of the buzzer
unsigned int frequency = 500;

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
              color: lightgray;
            }
        </style>
    </head>
    <body>
    <div class='container-fluid text-center'>
        <div class='row'>
            <div class='col-sm-12' style='color:red;font-size:7vh'>
                <p>Click/touch the button.</p>
            </div>
        </div>     
        <div class='row'>
            <div  class='col-sm-12'>
                <input type='button' class='btn btn-primary' id='id_button' style='font-size:7vh'>
            </div>
        </div>
        <br/>
        <div class='row'>
            <div  class='col-sm-12'>
                <i id='speaker' class='fas fa-volume-up css_off' style='font-size:15vh'></i>
            </div>
        </div>
        <div class='col-sm-12'>
              <input type='range' min='31' max='6000' class='form-control-range' id='slider'/>
        </div>
        <div class='row'>
          <div class='col-sm-12'>
            <h3 id='status'></h3>
          </div>
        </div>   
    </div>
    </body>
    
    <script>
        $(document).ready(refreshFunction);
        
        function refreshFunction(){
          $.getJSON('/refresh', function(result){
            $('#slider').val(result.frequency);
            
            if(result.state == 1)
            {
                $('#id_button').val('On');
                $('#speaker').removeClass('css_off').addClass('css_on');
            }
            else
            {
                $('#id_button').val('Off');
                $('#speaker').removeClass('css_on').addClass('css_off');
            }
            $('#status').html('Frequency: ' + result.frequency + ' Hz');
          });
        };
        
        $('#id_button').click(function(){
            var current_state = $('#speaker').hasClass('css_off');

            if(current_state == true)
            {
                $.ajax({
                  url:'/button_state',
                  type: 'POST',
                  data: {state: 'On'},
                });
                $('#id_button').val('On');
                $('#speaker').removeClass('css_off').addClass('css_on');
            }
            else
            {
                $.ajax({
                  url:'/button_state',
                  type: 'POST',
                  data: {state: 'Off'},
                });
                $('#id_button').val('Off');
                $('#speaker').removeClass('css_on').addClass('css_off');
            }
        });
        
        $('#slider').on('change', function(){
            var state_slider = $('#slider').val();
      
            $('#status').html('Frequency: ' + state_slider + ' Hz');
            $.ajax({
              url: '/buzzer_frequency',
              type: 'POST',
              data: {sound: state_slider}
            });
        });
    </script>
</html>
)";

//the htmlIndex() is called everytime somebody access the address
//of the board in the browser and sends back a message.
void htmlIndex() 
{
  //send the message to the user
  server.send(200, "text/html", page);
}

//get the state of the button
//and if the state is "On", turn on the buzzer
//at the specified frequency
void button_state()
{
  container = server.arg("state");
  
  if(container == "On")
  {
    tone(buzzer, frequency);
  }
  else
  {
    noTone(buzzer);
  }
  server.send(200, "text/html", "ok");
}

//the buzzer_frequency() is used to read the state of the slider
//for setting the frequency, and also control the frequency if the
//state is "On"
void buzzer_frequency()
{
  frequency = server.arg("sound").toInt();
  
  if(container == "On")
  {
    tone(buzzer, frequency);
  }
  else
  {
    noTone(buzzer);
  }
  server.send(200, "text/html", "ok");
}

//function for sending the last state of the
//button, and the frequency after refreshing
void refresh()
{
  //store the last state of the button
  //"On", state = 1
  //"Off", state = 0;
  int state = 0;

  if(container == "On")
  {
    state = 1;
  }
  
  char data[60] = R"(
    {
      "state": %d,
      "frequency": %d
    }
  )";
  
  char output[100];
  sprintf(output, data, state, frequency);
  server.send(200, "application/javascript", output);
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
  server.on("/button_state", button_state);
  server.on("/buzzer_frequency", buzzer_frequency);
  server.on("/refresh", refresh);

  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup()
{
  //set the mode of the pin used by the buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);

  //start the Serial communication at 115200 bits/s
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
