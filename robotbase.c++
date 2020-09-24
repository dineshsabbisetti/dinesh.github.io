/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can send/receive any data using WidgetTerminal object.

  App project setup:
    Terminal widget attached to Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "DTNWpoZYzrSHtRyE84Upt3nDtJFIqi2-";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Neelima";
char pass[] = "neelima121";

#include <Arduino.h>

#define DAC1 25
#define DAC2 26

int Value = 0;
int Value2 = 0;

int set1 = 0;
int set2 = 0;

BLYNK_WRITE(V11) {
  if (param.asInt() == 1) {

    Serial.println("FL");
  int Value = 190;  //255= 3.3V 128=1.65V
  int Value2 = 105; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V12) {
  if (param.asInt() == 1) {

    Serial.println("F");
  int Value = 128;  //255= 3.3V 128=1.65V
  int Value2 = 110; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V13) {
  if (param.asInt() == 1) {

    Serial.println("FR");
  int Value = 65;  //255= 3.3V 128=1.65V
  int Value2 = 105; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V14) {
  if (param.asInt() == 1) {

    Serial.println("L");
  int Value = 190;  //255= 3.3V 128=1.65V
  int Value2 = 90; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V15) {
  if (param.asInt() == 1) {

    Serial.println("S");
  int Value = 128;  //255= 3.3V 128=1.65V
  int Value2 = 128; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V16) {
  if (param.asInt() == 1) {

    Serial.println("R");
  int Value = 65;  //255= 3.3V 128=1.65V
  int Value2 = 90; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V17) {
  if (param.asInt() == 1) {

    Serial.println("BR");
  int Value = 170; //255= 3.3V 128=1.65V
  int Value2 = 75; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V18) {
  if (param.asInt() == 1) {

    Serial.println("B");
  int Value = 120;  //255= 3.3V 128=1.65V
  int Value2 = 65; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}

BLYNK_WRITE(V19) {
  if (param.asInt() == 1) {

    Serial.println("BR");
  int Value = 85; //255= 3.3V 128=1.65V
  int Value2 = 75; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);

  Serial.println("vlaue1"); 
  Serial.println(Value);
  Serial.println("vlaue2"); 
  Serial.println(Value2);
  
  } else {
  Serial.println("0");
  int Value = 0;  //255= 3.3V 128=1.65V
  int Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  }
}



BLYNK_WRITE(V2) {
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

{
  set1 = map(x, 0,1024, 0, 255);                    //steer 0 - 255
  set2 = map(y, 0,1024, 0, 255);                    //throttle 0 - 255
    
if(set1 < 131 && set1 > 120){                          //no steer
  int Value = 128;  //255= 3.3V 128=1.65V
  
  //dac_value = 2045; 
  Serial.println("nosteer");
  Serial.println("vlaue1"); 
  Serial.println(Value); 
  }else{
    Value = map(set1, 255,0,65,190);                 //steer amount 0 - 4095   
  //Value = map(set1, 255,0,0,255);                 //steer amount 0 - 4095 
  dacWrite(DAC1, Value);
  
  //dac_value = map(set1, 255,0,0,4095);                 //steer amount 0 - 4095 
  //dac.setVoltage(dac_value, false);
  Serial.println("steer"); 
  Serial.println("vlaue1"); 
  Serial.println(Value); 
  }

if(set2 < 120){
  
    Value2 = map(set2, 120,0,100,120);                       //forwards
  //Value2 = map(set2, 120,0,100,255);                     //forwards
  dacWrite(DAC2, Value2);
     
  //dac2_value = map(set2, 120,0,1600,4095);             //forwards
  //dac2.setVoltage(dac2_value, false);
  Serial.println("forward");
  Serial.println("vlaue2"); 
  Serial.println(Value2);     
}
if(set2 > 130){
  Value2 = map(set2, 131,255,100,66);                    //reverse
  dacWrite(DAC2, Value2);
  
  //dac2_value = map(set2, 131,255,1600,1059);           //reverse
  //dac2.setVoltage(dac2_value, false);
  Serial.println("reverse");
  Serial.println("vlaue2"); 
  Serial.println(Value2); 
}
if(set2 > 119 && set2 < 131){                          //stop
  Value2 = 96;                 
  dacWrite(DAC2, Value2);
  
  //dac2_value = 1600;  // 0-4095 
  //dac2.setVoltage(dac2_value, false);

  Serial.println("stop");
  Serial.println("vlaue2"); 
  Serial.println(Value2); 
}

  delay(0);

  
 }
  
}

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V1);

// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V1)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
    Serial.println("You said: 'Marco'");
    Serial.println("I said: 'Polo'");
  } else {

    // Send it back
    
    terminal.print("You said:");
    Serial.print("You said:");
    Serial.println(param.asStr());
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

void setup()
{
  // Debug console
  Value = 0;  //255= 3.3V 128=1.65V
  Value2 = 0; //255= 3.3V 128=1.65V
  
  dacWrite(DAC1, Value);
  dacWrite(DAC2, Value2);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Clear the terminal content
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();
}

void loop()
{
  Blynk.run();
}