#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// For OTA:
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

ADC_MODE(ADC_VCC);  // For monitoring of internal voltage levels

// Setup L298N Motor Controller Input Pins:
int IN1 = D6;  // Motor 2
int IN2 = D5;  // Motor 2
int IN3 = D2;  // Motor 1
int IN4 = D1;  // Motor 1
int servoPin = 0;
int Flag = 1;
char incomingByte;

//Setup WiFi:
char auth[] = "xxxxx";
char ssid[] = "xxxxx";
char pass[] = "xxxxx";
char server[] = "blynk-cloud.com";
int port = 8080;

BlynkTimer timer;

Servo myservo;



void setup()
{
  // setup L298N Motor Controller Input Pins:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(2, OUTPUT);

  // Set to LOW gear:
  myservo.attach(servoPin);
  myservo.write(0);
  timer.setInterval(1000L, StopServo);

  Blynk.begin(auth, ssid, pass, server, port);  // Set for Local Server

  timer.setInterval(1000L, VCCInput);  // Battery Check timer

  // For OTA:
  ArduinoOTA.setHostname("Gunnerator - Wemos D1 Mini Pro");
  ArduinoOTA.begin();
}



// Servo controlled gearing:
BLYNK_WRITE(V8) {
  if (param.asInt() == 1) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    myservo.attach(servoPin);
    myservo.write(175); // High gear
    timer.setTimeout(1500L, StopServo);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    myservo.attach(servoPin);
    myservo.write(0);  // Low gear
    timer.setTimeout(1500L, StopServo);
  }
}



// Headlamp Control:
BLYNK_WRITE(V9) {
  if (param.asInt() == 1) {
    digitalWrite(2, HIGH); // Headlamp ON
  } else {
    digitalWrite(2, LOW); // Headlamp OFF
  }
}



void StopServo() {
  myservo.detach();
}



// Joystick Widget Input:
BLYNK_WRITE(V6)
{
  Flag = 1;
  int y = param[1].asInt();
  int x = param[0].asInt();
  if (y > 750 && Flag == 1) {  // Forward
    Flag = 0;
    incomingByte = '1';
    ControlOutput();
  }
  if (y < 250 && Flag == 1) {  // Backward
    Flag = 0;
    incomingByte = '2';
    ControlOutput();
  }
  if (x < 250 && Flag == 1) {  // Left
    Flag = 0;
    incomingByte = '3';
    ControlOutput();
  }
  if (x > 750 && Flag == 1) {  // Right
    Flag = 0;
    incomingByte = '4';
    ControlOutput();
  }
  if (y == 512 && y == 512) {  // Full Stop
    incomingByte = '0';
    ControlOutput();
  }
}



// Button Widgets Input:
BLYNK_WRITE(V2) {  // Forward
  if (param.asInt() == 1) {
    incomingByte = '1';
  } else {
    incomingByte = '0';
  }
  Blynk.virtualWrite(V7, "Forward");
  ControlOutput();
}

BLYNK_WRITE(V3) {  // Backward
  if (param.asInt() == 1) {
    incomingByte = '2';
  } else {
    incomingByte = '0';
  }
  Blynk.virtualWrite(V7, "Backward");
  ControlOutput();
}

BLYNK_WRITE(V4) {  // Left
  if (param.asInt() == 1) {
    incomingByte = '3';
  } else {
    incomingByte = '0';
  }
  Blynk.virtualWrite(V7, "Spin Left");
  ControlOutput();
}

BLYNK_WRITE(V5) {  // Right
  if (param.asInt() == 1) {
    incomingByte = '4';
  } else {
    incomingByte = '0';
  }

  Blynk.virtualWrite(V7, "Spin Right");
  ControlOutput();
}



//  Take inputs and direct motor control functions:
void ControlOutput() {
  switch (incomingByte) {
    case '1': {
        motor1Forward();
        motor2Forward();
        Blynk.virtualWrite(V1, "Forward");
      }
      break;
    case '2': {
        motor1Backwards();
        motor2Backwards();
        Blynk.virtualWrite(V1, "Backward");

      }
      break;
    case '3': {
        motor1Backwards();
        motor2Forward();
        Blynk.virtualWrite(V1, "Spin Left");
      }
      break;
    case '4': {
        motor1Forward();
        motor2Backwards();
        Blynk.virtualWrite(V1, "Spin Right");
      }
      break;
    default: {
        Blynk.virtualWrite(V1, "Full Stop");
        Blynk.virtualWrite(V7, "Full Stop");
        motor1Stop();
        motor2Stop();
        Flag = 1;
      }
      break;
  }
}



// Functions to control L298N Motor Controller Input Pins:
void motor1Forward() {
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
}
void motor1Backwards() {
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
}
void motor1Stop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void motor2Forward() {
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
}
void motor2Backwards() {
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
}
void motor2Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}



// Simple monitoring of internal voltage levels:
void VCCInput() {
  Blynk.virtualWrite(V0, ESP.getVcc() * 0.001);
}



void loop()
{
  Blynk.run();
  timer.run();
  ArduinoOTA.handle();  // For OTA
}