        
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int trigPin=8;
int echoPin=9;
long duration,cm,inches;
/// nije leklam  //smart biofloc er jonno leka code 6.9.2021

int set_val=12;
int percentage;
////
void setup()
{
lcd.begin(16, 2);
Serial.begin(9600);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);  
}
void loop() 
{
 digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(4);
 digitalWrite(trigPin,LOW);
 pinMode(echoPin,INPUT);
 duration=pulseIn(echoPin,HIGH);
 cm=(duration/2)/29.1;//MEASUREMENT IN CM
 inches=(duration/2)/74;//MEASUREMENT IN INCHES
 delay(250);
 percentage=(set_val-cm)*100/set_val;
 Serial.print(percentage);
 Serial.print("%");
   if (cm>=2.4)//CHANGE THIS VALUES ACCORDING TO THE SIZE OF THE CONTAINER
   {
 {
   lcd.setCursor(1, 0);
   lcd.print("  OVERFLOW   ");
 }
  if (cm>=3.6)
  {
 {
   lcd.setCursor(1, 0);
   lcd.print("  TANK FULL  ");
 }
  if (cm>=4.8)
 {
  {
   lcd.setCursor(1, 0);
   lcd.print("  HALF FILLED  ");
 }
 if (cm>=6)
 {
  {
   lcd.setCursor(1, 0);
   lcd.print("    FILLING    ");
 }
 if(cm>7.2)
 {
  {
   lcd.setCursor(1, 0);
   lcd.print("  TANK EMPTY   ");
  }
 }}}}}
 delay(1000);
}

 
