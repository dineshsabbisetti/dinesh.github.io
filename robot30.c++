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

BLYNK_WRITE(V6) {

servo.write(param.asInt());

}

BLYNK_WRITE(V7) {
  int y = param.asInt();
  
  if (y>3)
  {
     digitalWrite(14, HIGH);
     digitalWrite(12, LOW);
  }
  if (y<3)
  {
     digitalWrite(14, LOW);
     digitalWrite(12, HIGH);
  }
  if (y=3)
  {
     digitalWrite(14, LOW);
     digitalWrite(12, LOW);
  }
}
void setup() {

// Debug console Serial.begin(115200);

Blynk.begin(auth, ssid, pass);

// You can also specify server:

//Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);

//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  servo.attach(2); // 15 means D4 pin of ESP8266
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
}

void loop()

{

Blynk.run(); // You can inject your own code or combine it with other sketches.

}