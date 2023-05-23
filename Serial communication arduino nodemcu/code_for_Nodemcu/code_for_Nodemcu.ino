
//Modified by Istiaque Ahamed
//Mail address :istiaqueahamedaiub@gmail.com

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "ThingSpeak.h"


SoftwareSerial mySerial(D1,D2);       //connect  arduino Tx to Nodemcu D2 ,arduino Rx to Nodemcu D1
WiFiClient client; // Creating WiFiClient Object

//ThingSpeak Channel's API Keys
unsigned long myChannelNumber = 145290;
const char * myWriteAPIKey = "JMHGU4FUPOTHLDPT";

//Add your WiFi credentials here
#define WIFI_SSID "Ahamed Net"
#define WIFI_PASSWORD "123456789"


void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Serial.println("\nConnected.");
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {
  // Check WiFi Status
  while (mySerial.available())
  {
    //To understand this section better, refer to the author: https://arduinojson.org/
    const size_t capacity = JSON_OBJECT_SIZE(7) + 100;
    DynamicJsonBuffer jsonBuffer(capacity);
    JsonObject& root = jsonBuffer.parseObject(mySerial);
    if (!root.success()) {
      //Serial.println("parseObject() failed");
      return;
    }

    float ldrStatus = root["value1"];
    float sensor2 = root["value2"];
    float sensor3 = root["value3"];
    float sensor4 = root["value4"];
    float sensor5 = root["value5"];
    float sensor6 = root["value6"];
    
    String msg= mySerial.readStringUntil('\r');
//   Serial.println(msg);
   
    Serial.print(ldrStatus, 5);  Serial.print(",");
    Serial.print(sensor2, 5);  Serial.print(",");
    Serial.print(sensor3, 5);  Serial.print(",");
    Serial.print(sensor4, 5);  Serial.print(",");
    Serial.print(sensor5, 5);  Serial.print(",");
    Serial.print(sensor6, 5); Serial.print(",");

//Sending Gas Data to ThingSpeak
    ThingSpeak.setField(1, ldrStatus);
    ThingSpeak.setField(2, sensor2);
    ThingSpeak.setField(3, sensor3);
    ThingSpeak.setField(4, sensor4);
    ThingSpeak.setField(5, sensor5);
    ThingSpeak.setField(6, sensor6);

    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
    delay(16000); // Wait  16 seconds to update the channel again

  }

}
