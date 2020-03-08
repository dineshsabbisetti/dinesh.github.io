/************************************************************** 
 * IoT Temperature Monitor with Blynk
 * Developed by Dinesh - 10 February 2020
 ***************************************************************/
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "nP1VeHsG85f_BjJLsm2ODMFsDeaHFy71";
char ssid[] = "OnePlus";
char pass[] = "nopassword";
/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;                                                   
/* DS18B20 Temperature Sensor */
#include <OneWire.h>

#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;

float Sensor_1;
float Sensor_2;
float Sensor_3;
float Sensor_4;
float Sensor_5;
float Sensor_6;
float Sensor_7;
float Sensor_8;

int Pin_D5 = 14; //14 is a Gpio pin number label as D5
int Pin_D6 = 12; //12 is a Gpio pin number label as D6
int Pin_D7 = 13; //13 is a Gpio pin number label as D7

void setup() 
{
  Serial.begin(115200);
  pinMode(Pin_D5,OUTPUT);
  pinMode(Pin_D6,OUTPUT);
  pinMode(Pin_D7,OUTPUT);
  pinMode(A0,INPUT);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  timer.setInterval(1000L, getSendData);
}

void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
  
  //Repeat for Sensor_1
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, LOW);     //Turn D5 off
  digitalWrite(Pin_D7, LOW);     //Turn D5 Off
  delay(100);                     //Wait for sensor
  Sensor_1 = analogRead(0);       //Read Analog pin as SENSOR4
  //Repeat for Sensor_2
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, LOW);     //Turn D5 Off
  digitalWrite(Pin_D7, HIGH);     //Turn D5 On
  delay(100);                     //Wait for sensor
  Sensor_2 = analogRead(0);       //Read Analog pin as SENSOR1
  //Repeat for Sensor_3
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, HIGH);     //Turn D5 On
  digitalWrite(Pin_D7, LOW);     //Turn D5 Off
  delay(100);                     //Wait for sensor
  Sensor_3 = analogRead(0);       //Read Analog pin as SENSOR2
  //Repeat for Sensor_4
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, HIGH);     //Turn D5 On
  digitalWrite(Pin_D7, HIGH);     //Turn D5 On
  delay(100);                     //Wait for sensor
  Sensor_4 = analogRead(0);       //Read Analog pin as SENSOR3
  //Repeat for Sensor_5
  digitalWrite(Pin_D5, HIGH);     //Turn D5 On
  digitalWrite(Pin_D6, LOW);     //Turn D5 Off
  digitalWrite(Pin_D7, LOW);     //Turn D5 Off
  delay(100);                     //Wait for sensor
  Sensor_5 = analogRead(0);       //Read Analog pin as SENSOR5
  //Repeat for Sensor_6
  digitalWrite(Pin_D5, HIGH);     //Turn D5 On
  digitalWrite(Pin_D6, LOW);     //Turn D5 Off
  digitalWrite(Pin_D7, HIGH);     //Turn D5 On
  delay(100);                     //Wait for sensor
  Sensor_6 = analogRead(0);       //Read Analog pin as SENSOR6
  //Repeat for Sensor_7
  digitalWrite(Pin_D5, HIGH);     //Turn D5 On
  digitalWrite(Pin_D6, HIGH);     //Turn D5 On
  digitalWrite(Pin_D7, LOW);     //Turn D5 Off
  delay(100);                     //Wait for sensor
  Sensor_7 = analogRead(0);       //Read Analog pin as SENSOR7
  //Repeat for Sensor_8
  digitalWrite(Pin_D5, HIGH);     //Turn D5 On
  digitalWrite(Pin_D6, HIGH);     //Turn D5 On
  digitalWrite(Pin_D7, HIGH);     //Turn D5 On
  delay(100);                     //Wait for sensor
  Sensor_8 = analogRead(0);       //Read Analog pin as SENSOR8



  //Print the results to the serial monitor
  
  Serial.print(" \n Sensor1=");   
  Serial.print(Sensor_1);
  Serial.print(" \n Sensor2=");   
  Serial.print(Sensor_2);
  Serial.print(" \n Sensor3=");   
  Serial.print(Sensor_3);
  Serial.print(" \n Sensor4=");   
  Serial.print(Sensor_4);
  Serial.print(" \n Sensor5=");   
  Serial.print(Sensor_5);
  Serial.print(" \n Sensor6=");   
  Serial.print(Sensor_6);
  Serial.print(" \n Sensor7=");   
  Serial.print(Sensor_7);
  Serial.print(" \n Sensor8=");   
  Serial.print(Sensor_8);
  

//  Serial.print(" / D6 = ");   
//  Serial.println(Value_D6);
//  Serial.print(" / D7 = ");   
//  Serial.print(Value_D7);
//  Serial.print(" / D8 = ");   
//  Serial.println(Value_D8);

  Blynk.virtualWrite(V18, Sensor_1);  //Write values to Blynk server
  Blynk.virtualWrite(V19, Sensor_2);  //Write values to Blynk server
  Blynk.virtualWrite(V20, Sensor_3);  //Write values to Blynk server
  Blynk.virtualWrite(V21, Sensor_4);  //Write values to Blynk server
  Blynk.virtualWrite(V22, Sensor_5);  //Write values to Blynk server
  Blynk.virtualWrite(V23, Sensor_6);  //Write values to Blynk server
  Blynk.virtualWrite(V24, Sensor_7);  //Write values to Blynk server
  Blynk.virtualWrite(V25, Sensor_8);  //Write values to Blynk server
  
//  Blynk.virtualWrite(V19, Sensor_2);  //Write values to Blynk server
//  Blynk.virtualWrite(V20, Value_D7);  //Write values to Blynk server
//  Blynk.virtualWrite(V21, Value_D8);  //Write values to Blynk server
  
}

/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  Serial.println(temp);
  Blynk.virtualWrite(10, temp); //virtual pin V10
}