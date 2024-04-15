// LIBRARIES
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

// LCD
#define LCD 0

//DHT 11

#define DHT_DATA 0
#define DHTPIN 2     // Pinul digital pe care este conectat senzorul
#define DHTTYPE DHT11   // Tipul de senzor folosit

#define CHANNEL A0

ArduinoLEDMatrix matrix;
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLLUMNS, LCD_ROWS);

DHT dht(DHTPIN, DHTTYPE);

int led =  LED_BUILTIN;
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
}

void loop() 
{
  delay(10000); 

  matrix_print_text("    Hello World!    ", 50, 0);

  delay(1000);
  if(DHT_DATA)
      print_DHT_11_data();
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
