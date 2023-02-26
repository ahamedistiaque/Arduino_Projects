
//Modified by Istiaque Ahamed
//Mail address :istiaqueahamedaiub@gmail.com

#include <ArduinoJson.h>

#include <SoftwareSerial.h>
//SoftwareSerial mySerial(5, 6);

//Sensor Pins
#define ldrPin A1

void setup() 
{
Serial.begin(9600); // opens serial port, sets data rate 9600 bps
pinMode(ldrPin, INPUT);
}

void loop() 
{


//float ldrStatus = analogRead(ldrPin);
//
//if (ldrStatus <= 200) {
//
//
//Serial.print("Its DARK, Turn on the LED : ");
//
//Serial.println(ldrStatus);
//delay(8000);
//} else {
//
//
//Serial.print("Its BRIGHT, Turn off the LED : ");
//
//Serial.println(ldrStatus);
//delay(8000);
//
//}

 
  float ldrStatus = analogRead(ldrPin);
  
  // if you need more sensor you can  use this 
  
  float sensor2 = ldrStatus+10;// put your sensor value

  float sensor3 = ldrStatus+20;
  float sensor4 = ldrStatus+30;  
  float sensor5 = ldrStatus+40;
  float sensor6 = ldrStatus+60;

  DynamicJsonBuffer jBuffer; 
  JsonObject& root = jBuffer.createObject();

  root["value1"] = ldrStatus;
  root["value2"] = sensor2;
  root["value3"] = sensor3;
  root["value4"] = sensor4;
  root["value5"] = sensor5;
  root["value6"] = sensor6;

  
  root.prettyPrintTo(Serial);
  Serial.println("");

//Minimum delay required for ThingSpeak to update is 16 seconds 
delay(16000);
}
