/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPin1 = 1; // Analog output pin that the LED is attached to
const int analogInPin2 = A2;  // Analog input pin that the potentiometer is attached to
const int analogOutPin2 = 2; // Analog output pin that the LED is attached to
const int analogInPin3 = A3;  // Analog input pin that the potentiometer is attached to
const int analogOutPin3 = 3; // Analog output pin that the LED is attached to
const int analogInPin4 = A4;  // Analog input pin that the potentiometer is attached to
const int analogOutPin4 = 4; // Analog output pin that the LED is attached to

int sensorValue1 = 0;        // value read from the pot
int outputValue1 = 0;        // value output to the PWM (analog out)
int sensorValue2 = 0;        // value read from the pot
int outputValue2 = 0;        // value output to the PWM (analog out)
int sensorValue3 = 0;        // value read from the pot
int outputValue3 = 0;        // value output to the PWM (analog out)
int sensorValue4 = 0;        // value read from the pot
int outputValue4 = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);
  sensorValue3 = analogRead(analogInPin3);
  sensorValue4 = analogRead(analogInPin4);
  // map it to the range of the analog out:
  outputValue1 = map(sensorValue1, 0, 1023, 0, 255);
  outputValue2 = map(sensorValue2, 0, 1023, 0, 255);
  outputValue3 = map(sensorValue3, 0, 1023, 0, 255);
  outputValue4 = map(sensorValue4, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin1, outputValue1);
  analogWrite(analogOutPin2, outputValue2);
  analogWrite(analogOutPin3, outputValue3);
  analogWrite(analogOutPin4, outputValue4);

  // print the results to the Serial Monitor:
  Serial.print("sensor1 = ");
  Serial.print(sensorValue1);
  Serial.print("\t output1 = ");
  Serial.println(outputValue1);

  Serial.print("sensor2 = ");
  Serial.print(sensorValue2);
  Serial.print("\t output2 = ");
  Serial.println(outputValue2);

  Serial.print("sensor3 = ");
  Serial.print(sensorValue3);
  Serial.print("\t output3 = ");
  Serial.println(outputValue3);

  Serial.print("sensor4 = ");
  Serial.print(sensorValue4);
  Serial.print("\t output4 = ");
  Serial.println(outputValue4);

   Serial.print('\n');

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}