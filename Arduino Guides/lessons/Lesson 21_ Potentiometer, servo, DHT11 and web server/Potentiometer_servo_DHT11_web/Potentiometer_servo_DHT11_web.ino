/*
   Credits: www.plusivo.com

   Lesson 21: Potentiometer, servo, DHT11 and web server

   The code below is created for the lesson Potentiometer,
   servo, DHT11 and web server where you will connect to a WiFi 
   network, host a simple web server and display the temperature, 
   humidity and the angle of the potentiometer in a web page.
   
   More information about the code can be found in the guide.
   
*/

#include <ESP8266WebServer.h>

//create an instance of the ESP8266WebServer library
ESP8266WebServer server(80);

//create two variables that will store the credentials of the wireless
//network
const char* ssid = "................";
const char* password = "............";

//the library "Servo.h" is used to control a servo motor using 
//PWM technique
#include <Servo.h>

//declare a new object called servo
Servo servo;

#include <SimpleDHT.h>

//create an instance for the SimpleDHT library
SimpleDHT11 dht11;

//define the digital pin used to connect the module
const int dht_pin = D7;

//declare two byte variables for temperature and humidity
byte temperature = 0;
byte humidity = 0;

//create a variable that will store the state of the potentiometer
int value = 0;

String page =
R"(
<html>  
  <head> 
    <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
    <title>Plusivo</title> 
  </head> 

  <body> 
    <h2>Hello from Plusivo!</h2> 
    <table style='font-size:20px'>  
      <tr>  
          <td> 
              <div>Angle:  </div>
          </td>
          <td> 
              <div id='Angle'></div> 
          </td>
      </tr> 

      <tr>  
          <td> 
              <div>Temperature:  </div>
          </td>
          <td> 
              <div id='Temperature'></div> 
          </td>
      </tr> 

      <tr>  
          <td> 
              <div>Humidity:  </div>
          </td>
          <td> 
              <div id='Humidity'></div> 
          </td>
       </tr> 
    </table>  
  </body> 
  
  <script> 
   $(document).ready(function(){ 
     setInterval(refreshFunction,100); 
   });

   function refreshFunction(){ 
     $.getJSON('/refresh', function(e){  
       $('#Angle').html(e.angle);  
       $('#Temperature').html(e.temperature);  
       $('#Humidity').html(e.humidity);  
     }); 
   }      
  </script> 
</html> 
)";

void refresh()
{ 
  //create a char array
  char messageFinal[100];

  char container[100] = 
  R"(
    {
      "angle": %d,
      "temperature":  %d,
      "humidity": %d
    }
  )";
  
  //put the values in messageFinal
  sprintf(messageFinal, container, value, temperature, humidity);

  //send data to user
  server.send(200, "application/javascript", messageFinal);
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
  //display the IP assigned to it in the serial manager.
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
  server.on("/refresh", refresh);
 
  //start the server
  server.begin();
  
  //print in serial manager that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  //start the serial communication with the computer at 115200 bits/s
  Serial.begin(115200);

  //attach the servo on digital pin D1
  servo.attach(D1);

  //call the two functions used to connect to wifi
  //and setup the web server
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
  
  //read the values
  dht11.read(dht_pin, &temperature, &humidity, NULL);

  //display the values in Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature); 
  Serial.println(" *C");
  Serial.print("Humidity: "); 
  Serial.print(humidity); 
  Serial.println(" H");
  Serial.println();

  //read the value on pin A0
  //the pin is able to read a value between 0 and 1024 corresponding
  //to 0 V and 3.3 V
  value = analogRead(A0);

  //remap the analog value to a new range (from 0 to 180) as the
  //servo can turn max 180 degrees.
  value = map(value, 0, 1024, 0, 180);
  
  //turn the servo motor accordingly to the angle stored in value
  servo.write(value);

  //print in Serial Monitor the current angle of the servo
  Serial.print("Angle: ");
  Serial.println(value);

  //pause the code for 100 ms;
  delay(100);
}

