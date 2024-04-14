 /*
 * Credits: www.plusivo.com
 * 
 * Lesson 13: DHT11
 * 
 * This lesson is created for the lesson "DHT11", 
 * where you will learn how to use a DHT11
 * Temperature and Humidity sensor.
 * 
 * Do not forget to install the SimpleDHT library
 * as shown in the guide!
 * 
 * More details can be found in the guide.
 * 
 */

#include <SimpleDHT.h>

//define the digital pin used to connect the module
const int dht_pin = D7;

SimpleDHT11 dht11;

void setup() 
{
  //start the Serial communication at 115200 bits/s
  Serial.begin(115200);
}

void loop() 
{
  //declare two byte variables for temperature and humidity
  byte temperature = 0;
  byte humidity = 0;

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
  
  //wait 2 s
  delay(2000);
}
