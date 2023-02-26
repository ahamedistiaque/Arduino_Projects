//#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);
int DS18S20_Pin = 7; //DS18S20 Signal pin on digital A0

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin A0
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(void) {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  Serial.begin(9600);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
  lcd.print("hellow");      
                                                                                                                                                                                                                                                                                                                                                                                       
  
}

void loop(void) {
  float temperature = getTemp();
  if(temperature==-1000)
  {
    lcd.clear();
    lcd.print("Error keno");
  }
  else{
  lcd.clear();  
  lcd.print("**Temperature**");   
  float farenhiet=temperature+32;
  Serial.println(temperature);
  lcd.setCursor(0,1);
  lcd.print(temperature);//Show the temperature in LCD
  lcd.print((char)223);// command for printing ° sign in LCD Ref:http://forum.arduino.cc/index.php?topic=19002.0
  lcd.print("C");// C for Celcius 
  lcd.setCursor(9,1);
  lcd.print(farenhiet);//Show the temperature in LCD
  lcd.print((char)223);// command for printing ° sign in LCD Ref:http://forum.arduino.cc/index.php?topic=19002.0
  lcd.print("F");// C for Celcius 

Serial.print(" ready");
  Serial.print("  Temperature = ");
  Serial.print(temperature);
  Serial.print(" temperature, ");
  Serial.print(farenhiet);
  Serial.println(" Fahrenheit");
 delay(1000); //just here to slow down the output so it is easier to read
  } 
}


float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
      
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
     
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
    
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
