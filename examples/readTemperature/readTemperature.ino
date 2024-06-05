/*****************************************************************
File:         readTemperature.ino
Description: 
          1. Connect the probe thermocouple (default: Type K) to the wiring terminal of the BM42S3021-1
          2. Run the example. Turn on the serial monitor to view the temperature      
******************************************************************/
#include "BM42S3021-1.h"
BM42S3021_1    BM42(&Wire); //Please uncomment out this line of code if you use Wire on BMduino
//BM42S3021_1     BM42(&Wire1); //Please uncomment out this line of code if you use Wire1 on BMduino
//BM42S3021_1     BM42(&Wire2); //Please uncomment out this line of code if you use Wire2 on BMduino

void setup() 
{
  Serial.begin(9600);
  BM42.begin();
}

void loop()
{
  Serial.print("Temperature:");
  Serial.print(BM42.readTemperature());
  Serial.println("℃");
  delay(200);
}
