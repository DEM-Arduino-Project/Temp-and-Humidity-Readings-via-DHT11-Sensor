// LIBRARIES
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "Arduino_Wifi_Connect.h"
#include <WiFiS3.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include "arduinoFFT.h"


// DEBUG SWITCH
#define WIFI_DEBUG 0

// FULL SERVER DATA SWITCH
#define SHOW_SERVER_DATA 0

// LCD
#define LCD 0

//DHT 11

#define DHT_DATA 0


#define DHTPIN 2     // Pinul digital pe care este conectat senzorul
#define DHTTYPE DHT11   // Tipul de senzor folosit

// FOR FFT
#define FFT_is_used 1

#define CHANNEL A0

const uint16_t samples = 8; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 100; //Hz, must be less than 10000 due to ADC


double vReal[samples];
double vImag[samples];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);


ArduinoLEDMatrix matrix;
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLLUMNS, LCD_ROWS);

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifi_client;

String http_string;
String json_buffer;
StaticJsonDocument<200> json_doc;
DeserializationError err;

int led =  LED_BUILTIN;
int wifi_status = WL_IDLE_STATUS;
int loop_counter = 0;

void setup() 
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // init the LED matrix
  init_matrix("UNO", 1000);

  //initializeaza DHT

  dht.begin();

  while (!Serial); // wait for serial port to connect. Needed for native USB port only
  

  if(LCD)
  {
    init_lcd();

    lcd.setCursor(0, 0);
    lcd.print("Hello World!");

    lcd.setCursor(0, 1);
    lcd.print("Initialising...");

    lcd.clear();
  }
  
  // init wifi and check connection
  setup_wifi_connection();
}

void loop() 
{
  delay(10000); 

  matrix_print_text("    Hello World!    ", 50, 0);

  delay(1000);
  if(DHT_DATA)
    {
      //print sensor data
      print_DHT_11_data();
    }

  if(SHOW_SERVER_DATA == 0)
  {
    wifi_client.stop();
    return;
  }

  // initialize server connection
  setup_http_connection();

  // get data
  parse_json_buffer();

   

  // verify api key

  if(get_api_code() != 200)
  {
    Serial.println("Invalid API KEY!");

    if(LCD)
    {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Invalid Key");

      lcd.setCursor(0, 1);
      lcd.print("Code 404");
    }

    return;
  }

  if(FFT_is_used){
    for(int i = 0; i < samples; i++){
      int sensorRead = analogRead(CHANNEL);
      vReal[i] = (sensorRead + 0.5) * (5.0 / 1023.0);
      vImag[i] = 0;
      Serial.println(vReal[i]);
    }


    FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
    FFT.compute(FFTDirection::Forward);
    FFT.complexToMagnitude();

    // Find dominant frequency
    double dominantFrequency = FFT.majorPeak();

    Serial.print("Dominant Frequency: ");
    Serial.print(dominantFrequency);
    Serial.println(" Hz");
  }

  // show api data
  print_api_data();

  Serial.println();
  
  // reset connection
  wifi_client.stop();
}


void init_lcd()
{
  //initialize lcd screen
  lcd.begin(LCD_COLLUMNS, LCD_ROWS);
  lcd.init();
  lcd.clear();
  // turn on the backlight
  lcd.backlight();
}

void print_DHT_11_data()
{
  delay(2000);  // Pauza între citiri

  // Citire umiditate
  float umiditate = dht.readHumidity();
  // Citire temperatura în grade Celsius
  float temperatura = dht.readTemperature();

  // Verifică dacă citirea a eșuat
  
  if (isnan(temperatura) || isnan(umiditate)) {
    Serial.println("Eroare la citirea senzorului DHT!");
    return;
  }

  // Afiseaza datele
  Serial.print("Umiditate: ");
  Serial.print(umiditate);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  //si pe led
// Convertirea float-urilor în șiruri de caractere
  char tempStr[10]; // Buffer pentru temperatura
  char humiStr[10]; // Buffer pentru umiditate
  dtostrf(temperatura, 4, 2, tempStr); // Convertire temperatura în șir de caractere
  dtostrf(umiditate, 4, 2, humiStr);   // Convertire umiditate în șir de caractere

  // Afișarea pe LED matrix
  matrix_print_text("Temp: " + String(tempStr) + "C", 50, 0);
  matrix_print_text("Humidity: " + String(humiStr) + "%", 50, 0);
}


void print_api_data()
{
  String country = "Country : " + get_country();
  String city = "City : " + get_city();

  String longitude = "Longitude : " + String(get_longitude());
  String latitude = "Latitude : " + String(get_latitude());

  String temp = "Temp: " + String(get_temp()) + "C";
  String temp_max = "Max Temperature : " + String(get_temp_max()) + "C";
  String temp_min = "Min Temperature : " + String(get_temp_min()) + "C";
  String temp_feels_like = "Feels Like : " + String(get_temp_feels_like()) + "C";

  String humidity = "Humid: " + String(get_humidity()) + "%";
  String clouds = "Cloud Coverage : " + String(get_clouds()) + "%";
  String wind_speed = "Wind Speed : " + String(get_wind_speed()) + " m/s";

  Serial.println(country);
  Serial.println(city);

  Serial.println(longitude);
  Serial.println(latitude);

  Serial.println(temp);
  Serial.println(temp_max);
  Serial.println(temp_min);
  Serial.println(temp_feels_like);

  Serial.println(humidity);
  Serial.println(clouds);
  Serial.println(wind_speed);

  if(LCD)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(temp);

    lcd.setCursor(0, 1);
    lcd.print(humidity);
  }

  matrix_print_text("    " + temp, 50, 0);
  matrix_print_text("    " + humidity, 50, 0);
}

void parse_json_buffer()
{
  // get the api key data
  http_string = get_json();

  // get the standalone json string
  json_buffer = http_string.substring(http_string.indexOf('{'));

  if (SHOW_SERVER_DATA == 1)
    Serial.println(json_buffer);
  
  // check for json parse error
  err = deserializeJson(json_doc, json_buffer);

  if(err)
  {
    Serial.println("Error parsing JSON");
    Serial.println(err.f_str());
    return;
  }

  Serial.println("Data read successfully");
  Serial.println();
}

int get_api_code()
{
  return int(json_doc["cod"]);
}

String get_country()
{
  return json_doc["sys"]["country"];
}

String get_city()
{
  return json_doc["name"];
}

float get_longitude()
{
  return float(json_doc["coord"]["lon"]);
}

float get_latitude()
{
  return float(json_doc["coord"]["lat"]);
}

float get_temp()
{
  return float(json_doc["main"]["temp"]) - 273.15;
}

float get_temp_min()
{
  return float(json_doc["main"]["temp_min"]) - 273.15;
}

float get_temp_max()
{
  return float(json_doc["main"]["temp_max"]) - 273.15;
}

float get_temp_feels_like()
{
  return float(json_doc["main"]["feels_like"]) - 273.15;
}

float get_wind_speed()
{
  return float(json_doc["wind"]["speed"]);
}

float get_clouds()
{
  return int(json_doc["clouds"]["all"]);
}

String get_weather()
{
  return json_doc["weather"]["main"];
}

float get_humidity()
{
  return (json_doc["main"]["humidity"]);
}

void setup_http_connection()
{
  Serial.println("Attempting to connect to " + String(HOST_NAME));

  if(LCD)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecting");
    lcd.setCursor(0, 1);
    lcd.print("to server...");
  }

  // connect to web server on port 80:
  if (wifi_client.connect(HOST_NAME, HTTP_PORT)) 
  {
    // if connected:
    Serial.println("Connected to server succesfully.\n");

    if(LCD)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Success!");
      lcd.setCursor(0, 1);
      lcd.print("Requesting data.");
    }
    
    // make a HTTP request:
    // send HTTP header
    wifi_client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
    wifi_client.println("Host: " + String(HOST_NAME));
    wifi_client.println("Connection: close");
    wifi_client.println();  // end HTTP header
    
  } 
  else 
  {  
    // if not connected:
    Serial.println("Connection to server failed.");

    if(LCD)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Connection");
      lcd.setCursor(0, 1);
      lcd.print("failed.");
    }
  }
}

String get_json()
{
  String buffer;
  while (wifi_client.connected()) 
  {
    if (wifi_client.available()) 
    {
      // read an incoming byte from the server and print it to serial monitor:
      buffer = wifi_client.readString();
    }
  }

  return buffer;
}

void setup_wifi_connection()
{
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) 
  {
    if(LCD)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WiFi Module");
      lcd.setCursor(0, 1);
      lcd.print("failure");
    }

    Serial.print("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) 
  {
    if(LCD)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Firmware error");
    }

    Serial.print("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (wifi_status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");

    if(LCD)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Connecting...");
    }

    Serial.println(WIFI_SSID);

    // Connect to WPA/WPA2 network:
    wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASS);

    // wait 5 seconds for connection:
    delay(5000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network!");

  if(LCD)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Connected");

    lcd.setCursor(0, 1);
    lcd.print("to network!");
  }
  

  if(WIFI_DEBUG == 1)
    print_initial_wifi_status();

  Serial.println();
}

void init_matrix(String text, unsigned long delay_ms)
{
  matrix.begin();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  // add some static text
  // will only show "UNO" (not enough space on the display)
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();

  matrix.endDraw();

  delay(delay_ms);
}

void matrix_print_text(String text, unsigned long speed, unsigned long delay_ms)
{
  // Make it scroll!
  matrix.beginDraw();

  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(speed);

  // add the text
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);

  matrix.endDraw();
  delay(delay_ms);
}

void print_loop_counter()
{
  Serial.println("Loop: " + String(loop_counter++));
}

void print_initial_wifi_status() 
{
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  print_mac_address(mac);
  Serial.println();
}

void print_current_wifi_status() 
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  print_mac_address(bssid);
  Serial.println();
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void print_mac_address(byte mac[]) 
{
  for (int i = 0; i < 6; i++) {
    if (i > 0) {
      Serial.print(":");
    }
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
  }
}
