/*
 * Credits: www.plusivo.com
 * 
 * Lesson 24: Piano
 * 
 * The code below is created for the lesson "Piano"
 * where you will learn how to create a piano style, with one octave,
 * in HTML and using JavaScript we will call special functions that
 * will play a specific note on the buzzer when any key of the piano 
 * is pressed.
 * 
 * Make sure you connected the buzzer correctly, according to the guide.
 * 
 * More information about the code can be found in the guide.
 */

#include <ESP8266WebServer.h>

//declare the credentials of the wireless network
const char* ssid = "..............";
const char* password = "..........";

//declare the pin used by the buzzer
const int buzzer = D6;

//declare variables that will hold the frequencies of the 
//notes from the sixth octave
const int c6 = 1047;
const int cs6 = 1109;
const int d6 = 1175;
const int ds6 = 1245;
const int e6 = 1319;
const int f6 = 1397;
const int fs6 = 1480;
const int g6 = 1568;
const int gs6 = 1661;
const int a6 = 1760;
const int as6 = 1865;
const int b6 = 1976;

ESP8266WebServer server(80);

String page = 
R"(
<html>
    <head>
        <title>Piano</title>
        
        <meta charset='utf-8'>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css'/>
        <script src='https://code.jquery.com/jquery-3.3.1.min.js'></script>
        
        <style>
            .whiteKey 
            {
                position: relative;
                border-style: solid;
                border-color: #000000;
                border-width: 0.42vh 0.21vh 0.42vh 0.21vh;
                border-radius: 0.84vh 0.84vh 0.84vh 0.84vh;
                text-align: center;
                width: 6.32vh;
                height: 31.61vh;
                background: #FFFFFF;
            }
            
            .blackKey 
            {
                position: relative;
                border-style: solid;
                border-color: #000000;
                border-width: 0.42vh 0.21vh 0.42vh 0.21vh;
                border-radius: 0 0 0.84vh 0.84vh;
                text-align: center;
                top: 0;
                background: #000000;
                z-index: 1;
                width: 4.21vh;
                height: 21.07vh;
                margin: 0 0 0 -2.1vh;
            }
            
            .whiteKeyText 
            {
                margin-top: 27.5vh;
                color: black;
                font-size: 2.3vh;
            }
            
            .blackKeyText 
            {
                margin-top: 17.91vh;
                color: white;
                font-size: 1.8vh;
            }
            
            #c1
            {
                border-left-width: 0.42vh;
            }
            
            #c12
            {
                border-right-width: 0.42vh;
            }
            
            .blackKey + .whiteKey 
            {
                margin-left: -2.1vh;
            }

            div 
            {
                webkit-user-select: none; /* Safari 3.1+ */
                moz-user-select: none; /* Firefox 2+ */
                ms-user-select: none; /* IE 10+ */
                user-select: none; /* Standard syntax */
            }
        </style>
    </head>
    <body>
    <div class='container-fluid'>
        <div class='row'>
            <div class='col-sm-12 col-xs-12 text-center'>
                <p style='color: blue; font-size: 7vh'>Piano style</p>
            </div>
        </div>
        <div class='row'>
            <div class='col-sm-12 col-xs-12 d-flex justify-content-center'>
                <div id='c1' class='whiteKey'> <p class='whiteKeyText'>C6</p> </div>
                <div id='c2' class='blackKey'> <p class='blackKeyText'>CS6</p> </div>
                <div id='c3' class='whiteKey'> <p class='whiteKeyText'>D6</p> </div>
                <div id='c4' class='blackKey'> <p class='blackKeyText'>DS6</p> </div>
                <div id='c5' class='whiteKey'> <p class='whiteKeyText'>E6</p> </div>
                <div id='c6' class='whiteKey'> <p class='whiteKeyText'>F6</p> </div>
                <div id='c7' class='blackKey'> <p class='blackKeyText'>FS6</p> </div>
                <div id='c8' class='whiteKey'> <p class='whiteKeyText'>G6</p> </div>
                <div id='c9' class='blackKey'> <p class='blackKeyText'>GS6</p> </div>
                <div id='c10' class='whiteKey'> <p class='whiteKeyText'>A6</p> </div>
                <div id='c11' class='blackKey'> <p class='blackKeyText'>AS6</p> </div>
                <div id='c12' class='whiteKey'> <p class='whiteKeyText'>B6</p> </div>
            </div>
        </div>
    </div>
    </body>
    <script>                                      
        $('#c1').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/c_note');
            $('#c1').css('background', '#D8D5D4');
        });
         
        $('#c2').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/cs_note');
            $('#c2').css('background', '#585757');
        });
           
        $('#c3').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/d_note');
            $('#c3').css('background', '#D8D5D4');
        });
          
        $('#c4').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/ds_note');
            $('#c4').css('background', '#585757');
        });
            
        $('#c5').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/e_note');
            $('#c5').css('background', '#D8D5D4');
        });
            
        $('#c6').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/f_note');
            $('#c6').css('background', '#D8D5D4');
        });

        $('#c7').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/fs_note');
            $('#c7').css('background', '#585757');
        });
           
        $('#c8').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/g_note');
            $('#c8').css('background', '#D8D5D4');
        });
           
        $('#c9').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/gs_note');
            $('#c9').css('background', '#585757');
        });
        
        $('#c10').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/a_note');
            $('#c10').css('background', '#D8D5D4');
        });
            
        $('#c11').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('as_note');
            $('#c11').css('background', '#585757');
        });
            
        $('#c12').on('mousedown touchstart', function(e){
            e.preventDefault();
            $.ajax('/b_note');
            $('#c12').css('background', '#D8D5D4');
        });

        $('#c1,#c3,#c5,#c6,#c8,#c10,#c12').on('mouseup touchend', function(e){
            e.preventDefault();
            $.ajax('/off');
            $(this).css('background', 'white');
        });

        $('#c2,#c4,#c7,#c9,#c11').on('mouseup touchend', function(e){
            e.preventDefault();
            $.ajax('/off');
            $(this).css('background', 'black');
        });

        $('#c1,#c3,#c5,#c6,#c8,#c10,#c12').mouseout(function(){
            $(this).css('background', 'white');
            $.ajax('/off');
        });

        $('#c2,#c4,#c7,#c9,#c11').mouseout(function(){
            $(this).css('background', 'black');
            $.ajax('/off');
        });

        $('#c1').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        $('#c3').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        $('#c5').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        $('#c6').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        $('#c8').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        $('#c10').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        $('#c12').mouseover(function(){
          $(this).css('background', '#E7E0DF');
        });
        
        $('#c2').mouseover(function(){
          $(this).css('background', '#464646');
        });
        $('#c4').mouseover(function(){
          $(this).css('background', '#464646');
        });
        $('#c7').mouseover(function(){
          $(this).css('background', '#464646');
        });
        $('#c9').mouseover(function(){
          $(this).css('background', '#464646');
        });
        $('#c11').mouseover(function(){
          $(this).css('background', '#464646');
        });

        var action = true;
        $('body').on('keydown', function(e){
            if (action == true){
              action = false;
              var key = e.which;
              console.log(key);
              switch(key)
              {
                  case 90:
                      $.ajax('/c_note');
                      $('#c1').css('background', '#D8D5D4');
                      break;
                  case 83:
                      $.ajax('/cs_note');
                      $('#c2').css('background', '#585757');
                      break;
                  case 88:
                      $.ajax('/d_note');
                      $('#c3').css('background', '#D8D5D4');
                      break;
                  case 68:
                      $.ajax('/ds_note');
                      $('#c4').css('background', '#585757');
                      break;
                  case 67:
                      $.ajax('/e_note');
                      $('#c5').css('background', '#D8D5D4');
                      break;
                  case 86:
                      $.ajax('/f_note');
                      $('#c6').css('background', '#D8D5D4');
                      break;
                  case 71:
                      $.ajax('/fs_note');
                      $('#c7').css('background', '#585757');
                      break;
                  case 66:
                      $.ajax('/g_note');
                      $('#c8').css('background', '#D8D5D4');
                      break;
                  case 72:
                      $.ajax('/gs_note');
                      $('#c9').css('background', '#585757');
                      break;
                  case 78:
                      $.ajax('/a_note');
                      $('#c10').css('background', '#D8D5D4');
                      break;
                  case 74:
                      $.ajax('/as_note');
                      $('#c11').css('background', '#585757');
                      break;
                  case 77:
                      $.ajax('/b_note');
                      $('#c12').css('background', '#D8D5D4');
                      break;
              }
            }
        });

        $('body').on('keyup', function(e){
            action = true;
            var key = e.which;
            if(key==90 || key==88 || key==67 || key==86 || key==66 ||key==78 ||key==77)
            {
                $.ajax('/off');
                $('#c1,#c3,#c5,#c6,#c8,#c10,#c12').css('background', 'white');
            }

            if(key==83 || key==68 || key==71 || key==72 || key==74)
            {
                $.ajax('/off');
                $('#c2,#c4,#c7,#c9,#c11').css('background', 'black');
            }
        });
    </script>
</html>
)";

void htmlIndex() 
{
  //send the page to the user
  server.send(200, "text/html", page);
}

//this function will be triggered when the "C" 
//key of the piano will be pressed
void c_note()
{
  //play the note on the buzzer
  tone(buzzer, c6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "CS" 
//key of the piano will be pressed
void cs_note()
{
  //play a note on the buzzer
  tone(buzzer, cs6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "D" 
//key of the piano will be pressed
void d_note()
{
  //play a note on the buzzer
  tone(buzzer, d6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "DS" 
//key of the piano will be pressed
void ds_note()
{
  //play a note on the buzzer 
  tone(buzzer, ds6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "E" 
//key of the piano will be pressed
void e_note()
{
  //play a note on the buzzer
  tone(buzzer, e6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "F" 
//key of the piano will be pressed
void f_note()
{
  //play a note on the buzzer
  tone(buzzer, f6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "FS" 
//key of the piano will be pressed
void fs_note()
{
  //play a note on the buzzer
  tone(buzzer, fs6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "G" 
//key of the piano will be pressed
void g_note()
{
  //play a note on the buzzer
  tone(buzzer, g6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "GS" 
//key of the piano will be pressed
void gs_note()
{
  //play a note on the buzzer
  tone(buzzer, gs6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "A" 
//key of the piano will be pressed
void a_note()
{
  //play a note on the buzzer
  tone(buzzer, a6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "AS" 
//key of the piano will be pressed
void as_note()
{
  //play a note on the buzzer
  tone(buzzer, as6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered when the "B" 
//key of the piano will be pressed
void b_note()
{
  //play a note on the buzzer
  tone(buzzer, b6);
  delay(10);
  server.send(200,"text/html","ok");
}

//this function will be triggered and the
//buzzer will be turned off
void off()
{
  //turn off the buzzer
  noTone(buzzer);
  delay(10);
  server.send(200,"text/html","ok");
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
  server.on("/c_note", c_note);
  server.on("/cs_note", cs_note);
  server.on("/d_note", d_note);
  server.on("/ds_note", ds_note);
  server.on("/e_note", e_note);
  server.on("/f_note", f_note);
  server.on("/fs_note", fs_note);
  server.on("/g_note", g_note);
  server.on("/gs_note", gs_note);
  server.on("/a_note", a_note);
  server.on("/as_note", as_note);
  server.on("/b_note", b_note);
  server.on("/off", off);
  
  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  pinMode(buzzer, OUTPUT);

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
}

void loop()
{
  //the method below is used to manage the incoming request 
  //from the user
  server.handleClient();
}
