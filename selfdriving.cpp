
// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "ESP8266.h"
#include "NewPing.h"
#include "HMC5883L.h"
#include "LiquidCrystal_PCF8574.h"
#include "RFID.h"
#include "Servo.h"


// Pin Definitions
#define DCMOTORDRIVERL298_PIN_INT1	4
#define DCMOTORDRIVERL298_PIN_ENB	3
#define DCMOTORDRIVERL298_PIN_INT2	5
#define DCMOTORDRIVERL298_PIN_ENA	2
#define DCMOTORDRIVERL298_PIN_INT3	6
#define DCMOTORDRIVERL298_PIN_INT4	7
#define HCSR04_1_PIN_TRIG	9
#define HCSR04_1_PIN_ECHO	8
#define HCSR04_2_PIN_TRIG	11
#define HCSR04_2_PIN_ECHO	10
#define HCSR04_3_PIN_TRIG	13
#define HCSR04_3_PIN_ECHO	12
#define HCSR04_4_PIN_TRIG	15
#define HCSR04_4_PIN_ECHO	14
#define IROBJAVOID_1_PIN_OUT	22
#define IROBJAVOID_2_PIN_OUT	23
#define IROBJAVOID_3_PIN_OUT	24
#define RFID_PIN_RST	25
#define RFID_PIN_SDA	53
#define SERVOMD_PIN_SIG	27



// Global variables and defines
// ====================================================================
// vvvvvvvvvvvvvvvvvvvv ENTER YOUR WI-FI SETTINGS  vvvvvvvvvvvvvvvvvvvv
//
const char *SSID     = "WIFI-SSID"; // Enter your Wi-Fi name 
const char *PASSWORD = "PASSWORD" ; // Enter your Wi-Fi password
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ====================================================================
char* const host = "www.google.com";
int hostPort = 80;
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints. 
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
const int servoMDRestPosition   = 20;  //Starting position
const int servoMDTargetPosition = 150; //Position when event is detected
// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
ESP8266 wifi;
NewPing hcsr04_1(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_2(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
NewPing hcsr04_3(HCSR04_3_PIN_TRIG,HCSR04_3_PIN_ECHO);
NewPing hcsr04_4(HCSR04_4_PIN_TRIG,HCSR04_4_PIN_ECHO);
HMC5883L compass;
LiquidCrystal_PCF8574 lcdI2C;
RFID rfid(RFID_PIN_SDA,RFID_PIN_RST);
Servo servoMD;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    wifi.init(SSID, PASSWORD);
    // Set declination angle on your location and fix heading
    // You can find your declination on: http://magnetic-declination.com/
    // (+) Positive or (-) for negative
    // For declination angle 4'36E (positive)
    compass.begin(+4,36);
    pinMode(IROBJAVOID_1_PIN_OUT, INPUT);
    pinMode(IROBJAVOID_2_PIN_OUT, INPUT);
    pinMode(IROBJAVOID_3_PIN_OUT, INPUT);
    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
    //initialize RFID module
    rfid.init();
    servoMD.attach(SERVOMD_PIN_SIG);
    servoMD.write(servoMDRestPosition);
    delay(100);
    servoMD.detach();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Hobby DC motors - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // Logic Level Converter - Bi-Directional - Test Code
    //Send request for www.google.com at port 80
    wifi.httpGet(host, hostPort);
    // get response buffer. Note that it is set to 250 bytes due to the Arduino low memory
    char* wifiBuf = wifi.getBuffer();
    //Comment out to print the buffer to Serial Monitor
    //for(int i=0; i< MAX_BUFFER_SIZE ; i++)
    //  Serial.print(wifiBuf[i]);
    //search buffer for the date and time and print it to the serial monitor. This is GMT time!
    char *wifiDateIdx = strstr (wifiBuf, "Date");
    for (int i = 0; wifiDateIdx[i] != '\n' ; i++)
    Serial.print(wifiDateIdx[i]);

    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Ublox NEO-6M GPS Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '4') {
    // Ultrasonic Sensor - HC-SR04 #1 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_1Dist = hcsr04_1.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_1Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '5') {
    // Ultrasonic Sensor - HC-SR04 #2 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_2Dist = hcsr04_2.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_2Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '6') {
    // Ultrasonic Sensor - HC-SR04 #3 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_3Dist = hcsr04_3.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_3Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '7') {
    // Ultrasonic Sensor - HC-SR04 #4 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_4Dist = hcsr04_4.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_4Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '8') {
    // HMC5883L - Magnetometer (Compass) - Test Code
    //Read heading value from compass
    float compassHeading = compass.getHeadingDeg();
    Serial.print(F("Heading: ")); Serial.print(compassHeading); Serial.println(F("[°]"));

    }
    else if(menuOption == '9') {
    // IR Obstacle Avoidance Sensor #1 - Test Code
    //Read IR obstacle Sensor. irObjAvoid_1Var will be '1' if an Obstacle was detected
    //Use the onboard trimmer to set the distance of alert
    bool irObjAvoid_1Var = !digitalRead(IROBJAVOID_1_PIN_OUT);
    Serial.print(F("ObjAvoid: ")); Serial.println(irObjAvoid_1Var);

    }
    else if(menuOption == '10') {
    // IR Obstacle Avoidance Sensor #2 - Test Code
    //Read IR obstacle Sensor. irObjAvoid_2Var will be '1' if an Obstacle was detected
    //Use the onboard trimmer to set the distance of alert
    bool irObjAvoid_2Var = !digitalRead(IROBJAVOID_2_PIN_OUT);
    Serial.print(F("ObjAvoid: ")); Serial.println(irObjAvoid_2Var);

    }
    else if(menuOption == '11') {
    // IR Obstacle Avoidance Sensor #3 - Test Code
    //Read IR obstacle Sensor. irObjAvoid_3Var will be '1' if an Obstacle was detected
    //Use the onboard trimmer to set the distance of alert
    bool irObjAvoid_3Var = !digitalRead(IROBJAVOID_3_PIN_OUT);
    Serial.print(F("ObjAvoid: ")); Serial.println(irObjAvoid_3Var);

    }
    else if(menuOption == '12') {
    // LCD 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '13') {
    // RFID Card Reader - RC522 - Test Code
    //Read RFID tag if present
    String rfidtag = rfid.readTag();
    //print the tag to serial monitor if one was discovered
    rfid.printTag(rfidtag);

    }
    else if(menuOption == '14') {
    // Standard Size - High Torque - Metal Gear Servo - MG995 - Test Code
    // The servo will rotate to target position and back to resting position with an interval of 500 milliseconds (0.5 seconds) 
    servoMD.attach(SERVOMD_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servoMD.write(servoMDTargetPosition);  // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoMD.write(servoMDRestPosition);    // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    delay(500);                              // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoMD.detach();                    // 6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Hobby DC motors"));
    Serial.println(F("(2) Logic Level Converter - Bi-Directional"));
    Serial.println(F("(3) Ublox NEO-6M GPS Module"));
    Serial.println(F("(4) Ultrasonic Sensor - HC-SR04 #1"));
    Serial.println(F("(5) Ultrasonic Sensor - HC-SR04 #2"));
    Serial.println(F("(6) Ultrasonic Sensor - HC-SR04 #3"));
    Serial.println(F("(7) Ultrasonic Sensor - HC-SR04 #4"));
    Serial.println(F("(8) HMC5883L - Magnetometer (Compass)"));
    Serial.println(F("(9) IR Obstacle Avoidance Sensor #1"));
    Serial.println(F("(10) IR Obstacle Avoidance Sensor #2"));
    Serial.println(F("(11) IR Obstacle Avoidance Sensor #3"));
    Serial.println(F("(12) LCD 16x2 I2C"));
    Serial.println(F("(13) RFID Card Reader - RC522"));
    Serial.println(F("(14) Standard Size - High Torque - Metal Gear Servo - MG995"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Logic Level Converter - Bi-Directional"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Ublox NEO-6M GPS Module - note that this component doesn't have a test code"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #1"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #2"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #3"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #4"));
    		else if(c == '8') 
    			Serial.println(F("Now Testing HMC5883L - Magnetometer (Compass)"));
    		else if(c == '9') 
    			Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #1"));
    		else if(c == '10') 
    			Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #2"));
    		else if(c == '11') 
    			Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #3"));
    		else if(c == '12') 
    			Serial.println(F("Now Testing LCD 16x2 I2C"));
    		else if(c == '13') 
    			Serial.println(F("Now Testing RFID Card Reader - RC522"));
    		else if(c == '14') 
    			Serial.println(F("Now Testing Standard Size - High Torque - Metal Gear Servo - MG995"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/