/*
 * Credits: www.plusivo.com
 * 
 * Lesson 25: Piano with 7 octaves
 * 
 * The code below is created for the lesson "Piano with 7 octaves"
 * where you will learn how to create a piano style, with seven octaves,
 * in HTML and using JavaScript we will call special functions that
 * will play a specific note on the buzzer when any key of the piano 
 * is pressed.
 * 
 * Make sure you connected the buzzer correctly, according to the guide.
 * 
 * More information can be found in the guide.
 */
 
//declare variables that will hold the frequencies of the 
//notes for all 7 octaves
const int c1 = 33;
const int cs1 = 35;
const int d1 = 37;
const int ds1 = 39;
const int e1 = 41;
const int f1 = 44;
const int fs1 = 46;
const int g1 = 49;
const int gs1 = 52;
const int a1 = 55;
const int as1 = 58;
const int b1 = 62;
const int c2 = 65;
const int cs2 = 69;
const int d2 = 73;
const int ds2 = 78;
const int e2 = 82;
const int f2 = 87;
const int fs2 = 93;
const int g2 = 98;
const int gs2 = 104;
const int a2 = 110;
const int as2 = 117;
const int b2 = 123;
const int c3 = 131;
const int cs3 = 139;
const int d3 = 147;
const int ds3 = 156;
const int e3 = 165;
const int f3 = 175;
const int fs3 = 185;
const int g3 = 196;
const int gs3 = 208;
const int a3 = 220;
const int as3 = 233;
const int b3 = 247;
const int c4 = 262;
const int cs4 = 277;
const int d4 = 294;
const int ds4 = 311;
const int e4 = 330;
const int f4 = 349;
const int fs4 = 370;
const int g4 = 392;
const int gs4 = 415;
const int a4 = 440;
const int as4 = 466;
const int b4 = 494;
const int c5 = 523;
const int cs5 = 554;
const int d5 = 587;
const int ds5 = 622;
const int e5 = 659;
const int f5 = 698;
const int fs5 = 740;
const int g5 = 784;
const int gs5 = 831;
const int a5 = 880;
const int as5 = 932;
const int b5 = 988;
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
const int c7 = 2093;
const int cs7 = 2217;
const int d7 = 2349;
const int ds7 = 2489;
const int e7 = 2637;
const int f7 = 2794;
const int fs7 = 2960;
const int g7 = 3136;
const int gs7 = 3322;
const int a7 = 3520;
const int as7 = 3729;
const int b7 = 3951;

#include <ESP8266WebServer.h>

//declare the credentials of the wireless network
const char* ssid = ".............";
const char* password = ".........";

//declare the pin used by the buzzer
const int buzzer = D6;

//declare a variable that will store the current octave
int octave = 1;

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
            
            button
            {
              font-size: 2vh !important;   
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
                    <div id='c1' class='whiteKey'><p id='k1' class='whiteKeyText'></p></div>
                    <div id='c2' class='blackKey'><p id='k2' class='blackKeyText'></p></div>
                    <div id='c3' class='whiteKey'><p id='k3' class='whiteKeyText'></p></div>
                    <div id='c4' class='blackKey'><p id='k4' class='blackKeyText'></p></div>
                    <div id='c5' class='whiteKey'><p id='k5' class='whiteKeyText'></p></div>
                    <div id='c6' class='whiteKey'><p id='k6' class='whiteKeyText'></p></div>
                    <div id='c7' class='blackKey'><p id='k7' class='blackKeyText'></p></div>
                    <div id='c8' class='whiteKey'><p id='k8' class='whiteKeyText'></p></div>
                    <div id='c9' class='blackKey'><p id='k9' class='blackKeyText'></p></div>
                    <div id='c10' class='whiteKey'><p id='k10' class='whiteKeyText'></p></div>
                    <div id='c11' class='blackKey'><p id='k11' class='blackKeyText'></p></div>
                    <div id='c12' class='whiteKey'><p id='k12' class='whiteKeyText'></p></div>
            </div>
        </div>
        <br/>
        <div class='row'>
            <div class='col-sm-12 col-xs-12 text-center' style='font-size: 5vh'>
                <p>Select the octave:</p>
            </div>
        </div>
        <div class='row'>
            <div class='col-sm-12 col-xs-12 text-center'>
                <button id='1' type='button' class='btn btn-outline-primary'>First</button>
                <button id='2' type='button' class='btn btn-outline-primary'>Second</button>
                <button id='3' type='button' class='btn btn-outline-primary'>Third</button>
                <button id='4' type='button' class='btn btn-outline-primary'>Fourth</button>
                <button id='5' type='button' class='btn btn-outline-primary'>Fifth</button>
                <button id='6' type='button' class='btn btn-outline-primary'>Sixth</button>
                <button id='7' type='button' class='btn btn-outline-primary'>Seventh</button>
            </div>
        </div>
    </div>
    </body>
    
    <script>
        var octave;

        function change_octave(){
          $.ajax({
            url: '/set_octave',
            type: 'POST',
            data: {octave: octave},
          });
        }
        
        function keys_text(octave)
        {
            $('#k1').html('C' + octave);
            $('#k2').html('CS' + octave);
            $('#k3').html('D' + octave);
            $('#k4').html('DS' + octave);
            $('#k5').html('E' + octave);
            $('#k6').html('F' + octave);
            $('#k7').html('FS' + octave);
            $('#k8').html('G' + octave);
            $('#k9').html('GS' + octave);
            $('#k10').html('A' + octave);
            $('#k11').html('AS' + octave);
            $('#k12').html('B' + octave);
        };

        $(document).ready(function(){
            $.get('/refresh', function(octave){
               keys_text(octave);
            });
        });

        $('button').on('click', function(){
            octave = this.id;
            keys_text(octave);
            change_octave();
        });
                      
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

        $('#c1,#c3,#c5,#c6,#c8,#c10,#c12').mouseout(function(){
            $(this).css('background', 'white');
            $.ajax('/off');
        });

        $('#c2,#c4,#c7,#c9,#c11').mouseout(function(){
            $(this).css('background', 'black');
            $.ajax('/off');
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

//create arrays with the notes for each octave (in order)
int octave1[] = {c1, cs1, d1, ds1, e1, f1, fs1, g1, gs1, a1, as1, b1};
int octave2[] = {c2, cs2, d2, ds2, e2, f2, fs2, g2, gs2, a2, as2, b2};
int octave3[] = {c3, cs3, d3, ds3, e3, f3, fs3, g3, gs3, a3, as3, b3};
int octave4[] = {c4, cs4, d4, ds4, e4, f4, fs4, g4, gs4, a4, as4, b4};
int octave5[] = {c5, cs5, d5, ds5, e5, f5, fs5, g5, gs5, a5, as5, b5};
int octave6[] = {c6, cs6, d6, ds6, e6, f6, fs6, g6, gs6, a6, as6, b6};
int octave7[] = {c7, cs7, d7, ds7, e7, f7, fs7, g7, gs7, a7, as7, b7};

/*
#we have included the octave arrays in another array. 
#this way we have created a matrix in which we can call the frequency by octave and
#note number as described in the next "illustration"
#
# |   |   | |   |   |   |   | |   | |   |   |
# |   |   | |   |   |   |   | |   | |   |   |
# |   |   | |   |   |   |   | |   | |   |   |
# |   |C S| |D S|   |   |F S| |G S| |A S|   |
# |   | 1 | | 3 |   |   | 6 | | 8 | |10 |   |
# |   |___| |___|   |   |___| |___| |___|   |
# |     |     |     |     |     |     |     |
# |  C  |  D  |  E  |  F  |  G  |  A  |  B  |
# |  0  |  2  |  4  |  5  |  7  |  9  |  11 |
# -------------------------------------------
*/

int *octave_array[] = {octave1, octave2, octave3, octave4, octave5, octave6, octave7};

void c_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][0]);
  Serial.println(octave_array[octave-1][0]);
  delay(10);
  server.send(200,"text/html","ok");
}

void cs_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][1]);
  Serial.println(octave_array[octave-1][1]);
  delay(10);
  server.send(200,"text/html","ok");
}

void d_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][2]);
  Serial.println(octave_array[octave-1][2]);
  delay(10);
  server.send(200,"text/html","ok");
}

void ds_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][3]);
  Serial.println(octave_array[octave-1][3]);
  delay(10);
  server.send(200,"text/html","ok");
}

void e_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][4]);
  Serial.println(octave_array[octave-1][4]);
  delay(10);
  server.send(200,"text/html","ok");
}

void f_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][5]);
  Serial.println(octave_array[octave-1][5]);
  delay(10);
  server.send(200,"text/html","ok");
}

void fs_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][6]);
  Serial.println(octave_array[octave-1][6]);
  delay(10);
  server.send(200,"text/html","ok");
}

void g_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][7]);
  Serial.println(octave_array[octave-1][7]);
  delay(10);
  server.send(200,"text/html","ok");
}

void gs_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][8]);
  Serial.println(octave_array[octave-1][8]);
  delay(10);
  server.send(200,"text/html","ok");
}

void a_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][9]);
  Serial.println(octave_array[octave-1][9]);
  delay(10);
  server.send(200,"text/html","ok");
}

void as_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][10]);
  Serial.println(octave_array[octave-1][10]);
  delay(10);
  server.send(200,"text/html","ok");
}

void b_note()
{
  //play a note on the buzzer
  tone(buzzer, octave_array[octave-1][11]);
  Serial.println(octave_array[octave-1][11]);
  delay(10);
  server.send(200,"text/html","ok");
}

void off()
{
  //turn off the buzzer
  noTone(buzzer);
  Serial.println("stop");
  delay(10);
  server.send(200,"text/html","ok");
}

void set_octave()
{
  //store the current octave 
  octave = server.arg("octave").toInt();
  Serial.println(octave);
  server.send(200,"text/html","ok");
}

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

void refresh_function()
{
  //send the last known octave to the user
  //we will use this so that even if we will
  //refresh the page, the content will not
  //change
  char c = octave + '0';
  String a = String(c);
  server.send(200, "application/javascript", a);
}

//setupServer() function is used to set up and organise
//the website
void setupServer()
{ 
  //the method "server.on()" is to call a function when
  //the user access the location
  //the default location is "/"
  server.on("/", htmlIndex);
  server.on("/refresh", refresh_function);
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
  server.on("/set_octave", set_octave);
  
  //start the server
  server.begin();
  
  //print in Serial Monitor that the HTTP server is started
  Serial.println("HTTP server started");
}

void setup() 
{
  pinMode(buzzer, OUTPUT);

  //start the Serial communication at the baudrates 115200
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
