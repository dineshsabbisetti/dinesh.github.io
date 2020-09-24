#include <Wire.h>
#include <SPI.h> 
#include <Adafruit_MCP4725.h>

int pot1 = A0;
int pot2 = A1;

int set1 = 0;
int set2 = 0;


uint32_t dac_value = 0;
uint32_t dac2_value = 0;

int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor

Adafruit_MCP4725 dac;
Adafruit_MCP4725 dac2; 



void setup()
{
  Wire.begin(1);        // Activate I2C link
  Serial.begin(9600);
  dac.begin(0x60);
  dac2.begin(0x61);
  
}


void loop()
{
  set1 = map(pot1, 0,1024, 0, 255);                    //steer 0 - 255
  set2 = map(pot2, 0,1024, 0, 255);                    //throttle 0 - 255
    
if(set1 < 131 && set1 > 120){                          //no steer
  dac_value = 2045; 
  }else{
  dac_value = map(set1, 255,0,0,4095);                 //steer amount 0 - 4095 
  dac.setVoltage(dac_value, false);
  }

if(set2 < 120){
  dac2_value = map(set2, 120,0,1600,4095);             //forwards
  dac2.setVoltage(dac2_value, false);
}
if(set2 > 130){
  dac2_value = map(set2, 131,255,1600,1059);           //reverse
  dac2.setVoltage(dac2_value, false);
}
if(set2 > 119 && set2 < 131){                          //stop
  dac2_value = 1600;  // 0-4095
  dac2.setVoltage(dac2_value, false);
}

  delay(0);


  sensorValue1 = analogRead(pot1);
  sensorValue2 = analogRead(pot2);



  Serial.print("sensor1 = ");
  Serial.print(sensorValue1);
  Serial.print(" sensor2 = ");
  Serial.println(sensorValue2);
  Serial.println("\n");






  
 }