//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
//----------------------------------------Include the ThingSpeak Library, Download here : https://github.com/mathworks/thingspeak-arduino
#include "ThingSpeak.h"

#define ON_Board_LED D4  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define LIGHT D1 //--> Defining LIGHT/Relay Port

//----------------------------------------SSID and Password of your WiFi router/hotspot
const char* ssid     = "DESKTOP-9ND061I 1074";
const char* password = "123456789";

//----------------------------------------Channel ID on ThingSpeak
unsigned long channel = 1083417;

//----------------------------------------Declaration field1, I use field1 for light / relay, if you use many fields, add field1, field2, and so on.
unsigned int field1 = 1;

WiFiClient  client;

//----------------------------------------SETUP
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(ON_Board_LED, OUTPUT);  //--> On Board LED port Direction output
  pinMode(LIGHT, OUTPUT); //--> LIGHT/Relay port Direction output
  
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board. Led On Board use active low.
  digitalWrite(LIGHT, LOW); //--> Turn off LIGHT. LIGHT/Relay use active high, some relay modules may be different.

  //----------------------------------------Wait for connection
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  //----------------------------------------ThingSpeak.begin(client)
  ThingSpeak.begin(client);
}

void loop() {
  int statusCode = 0;
  
  int last_light_state = ThingSpeak.readFloatField(channel, field1);  //--> get the latest data from the fields on ThingSpeak

  statusCode = ThingSpeak.getLastReadStatus();  //--> Check the status of the read operation to see if it was successful
  if(statusCode == 200){
    if(last_light_state == 1){
      digitalWrite(LIGHT, HIGH);
      Serial.println("LIGHT is On");
    }
    else if(last_light_state == 0){
      digitalWrite(LIGHT, LOW);
      Serial.println("LIGHT is Off");
    }
    Serial.print("The latest data from Field1 on ThingSpeak is : ");
    Serial.println(last_light_state);    
  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }
  delay(15000);
}
