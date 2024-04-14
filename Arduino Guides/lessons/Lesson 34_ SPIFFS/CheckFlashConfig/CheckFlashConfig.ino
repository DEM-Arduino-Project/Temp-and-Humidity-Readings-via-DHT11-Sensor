/* 
 *  Credits: www.plusivo.com
 *  
 *  Lesson 34: SPIFFS
 *  
 *  In this code we will read the real flash size
 *  of the development board and we will compare it with 
 *  the size set from the Arduino IDE
 */

void setup() 
{
  //start the Serial communication at 115200 bits/s
  Serial.begin(115200);
}

void loop() 
{
  //read the real size of the chip
  //and also get the size set from Arduino the IDE
  //they shoulr match
  uint32_t real = ESP.getFlashChipRealSize();
  uint32_t ide = ESP.getFlashChipSize();

  //display in Serial Monitor the real size
  Serial.printf("Flash real size: %u\n", real);

  //display in Serial Monitor the size set from Arduino IDE
  Serial.printf("Flash ide  size: %u\n\n", ide);

  //wait 5 s
  delay(5000);
}
