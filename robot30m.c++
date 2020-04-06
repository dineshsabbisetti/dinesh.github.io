/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include <Servo.h>

// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "GmMhqkoChuJ_A1xzI6lq9isLdH_S_LWB";

// Your WiFi credentials.

// Set password to "" for open networks.

char ssid[] = "OnePlus";

char pass[] = "nopassword";


Servo servo;

BLYNK_WRITE(V0) {

servo.write(param.asInt());

}

BLYNK_WRITE(V1) {
  if (param.asInt() == 1) {
      servo.write(45);
    digitalWrite(14, HIGH); // move forward
    digitalWrite(12, LOW); // move backward
  } else {
       servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V2) {
  if (param.asInt() == 1) {
      servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, HIGH); // move backward
  } else {
      servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V3) {
  if (param.asInt() == 1) {
      servo.write(135);
    digitalWrite(14, HIGH); // move forward
    digitalWrite(12, LOW); // move backward
  } else {
       servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}


BLYNK_WRITE(V4) {
  if (param.asInt() == 1) {
      servo.write(0);
    digitalWrite(14, HIGH); // move forward
    digitalWrite(12, LOW); // move backward
  } else {
       servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V5) {
  if (param.asInt() == 1) {
      servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  } else {
      servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V6) {
  if (param.asInt() == 1) {
      servo.write(180);
    digitalWrite(14, HIGH); // move forward
    digitalWrite(12, LOW); // move backward
  } else {
       servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V7) {
  if (param.asInt() == 1) {
      servo.write(45);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, HIGH); // move backward
  } else {
      servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V8) {
  if (param.asInt() == 1) {
      servo.write(90);
    digitalWrite(14, HIGH); // move forward
    digitalWrite(12, LOW); // move backward
  } else {
       servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}

BLYNK_WRITE(V9) {
  if (param.asInt() == 1) {
      servo.write(135);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, HIGH); // move backward
  } else {
       servo.write(90);
    digitalWrite(14, LOW); // move forward
    digitalWrite(12, LOW); // move backward
  }
}




void setup() {

// Debug console Serial.begin(115200);

Blynk.begin(auth, ssid, pass);

// You can also specify server:

//Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);

//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

servo.attach(2); // 15 means D4 pin of ESP8266

}

void loop()

{

Blynk.run(); // You can inject your own code or combine it with other sketches.

}