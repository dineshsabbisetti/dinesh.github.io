
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "NewPing.h"
#include "LiquidCrystal_PCF8574.h"
#include "MPU6050.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "Servo.h"


// Pin Definitions
#define DCMOTORDRIVERL298_PIN_INT1  4
#define DCMOTORDRIVERL298_PIN_ENB  3
#define DCMOTORDRIVERL298_PIN_INT2  5
#define DCMOTORDRIVERL298_PIN_ENA  2
#define DCMOTORDRIVERL298_PIN_INT3  6
#define DCMOTORDRIVERL298_PIN_INT4  7
#define HCSR04_1_PIN_TRIG  9
#define HCSR04_1_PIN_ECHO  8
#define HCSR04_2_PIN_TRIG  11
#define HCSR04_2_PIN_ECHO  10
#define HCSR04_3_PIN_TRIG  13
#define HCSR04_3_PIN_ECHO  12
#define HCSR04_4_PIN_TRIG  15
#define HCSR04_4_PIN_ECHO  14
#define SERVO360_PIN_SIG  16



// Global variables and defines
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
int16_t mpu6050Ax, mpu6050Ay, mpu6050Az;
int16_t mpu6050Gx, mpu6050Gy, mpu6050Gz;
// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
NewPing hcsr04_1(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_2(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
NewPing hcsr04_3(HCSR04_3_PIN_TRIG,HCSR04_3_PIN_ECHO);
NewPing hcsr04_4(HCSR04_4_PIN_TRIG,HCSR04_4_PIN_ECHO);
LiquidCrystal_PCF8574 lcdI2C;
MPU6050 mpu6050;
Servo servo360;


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
    
    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
    Wire.begin();
    mpu6050.initialize();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Micro DC Motors (Geared) - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2')
    {
    // Disclaimer: The Ublox NEO-6M GPS Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 #1 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_1Dist = hcsr04_1.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_1Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // Ultrasonic Sensor - HC-SR04 #2 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_2Dist = hcsr04_2.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_2Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '5') {
    // Ultrasonic Sensor - HC-SR04 #3 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_3Dist = hcsr04_3.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_3Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '6') {
    // Ultrasonic Sensor - HC-SR04 #4 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_4Dist = hcsr04_4.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_4Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '7') {
    // LCD 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '8') {
    // SparkFun MPU-6050 - Accelerometer and Gyro - Test Code
    mpu6050.getMotion6(&mpu6050Ax, &mpu6050Ay, &mpu6050Az, &mpu6050Gx, &mpu6050Gy, &mpu6050Gz);   //read accelerometer and gyroscope raw data in three axes
    double mpu6050Temp = ((double)mpu6050.getTemperature() + 12412.0) / 340.0;
    Serial.print("a/g-\t");
    Serial.print(mpu6050Ax); Serial.print("\t");
    Serial.print(mpu6050Ay); Serial.print("\t");
    Serial.print(mpu6050Az); Serial.print("\t");
    Serial.print(mpu6050Gx); Serial.print("\t");
    Serial.print(mpu6050Gy); Serial.print("\t");
    Serial.print(mpu6050Gz); Serial.print("\t");
    Serial.print(F("Temp- "));   
    Serial.println(mpu6050Temp);
    delay(100);

    }
    else if(menuOption == '9') {
    // Servo - Generic Continuous Rotation (Micro Size) - Test Code
    // The servo will rotate CW in full speed, CCW in full speed, and will stop  with an interval of 2000 milliseconds (2 seconds) 
    servo360.attach(SERVO360_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo360.write(180);  // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360.write(0);    // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360.write(90);    // 6. sending 90 stops the servo 
    delay(2000);                              // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360.detach();                    // 8. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
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
    Serial.println(F("(1) L298N Motor Driver with Dual Micro DC Motors (Geared)"));
    Serial.println(F("(2) Ublox NEO-6M GPS Module"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04 #1"));
    Serial.println(F("(4) Ultrasonic Sensor - HC-SR04 #2"));
    Serial.println(F("(5) Ultrasonic Sensor - HC-SR04 #3"));
    Serial.println(F("(6) Ultrasonic Sensor - HC-SR04 #4"));
    Serial.println(F("(7) LCD 16x2 I2C"));
    Serial.println(F("(8) SparkFun MPU-6050 - Accelerometer and Gyro"));
    Serial.println(F("(9) Servo - Generic Continuous Rotation (Micro Size)"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing L298N Motor Driver with Dual Micro DC Motors (Geared)"));
        else if(c == '2') 
          Serial.println(F("Now Testing Ublox NEO-6M GPS Module - note that this component doesn't have a test code"));
        else if(c == '3') 
          Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #1"));
        else if(c == '4') 
          Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #2"));
        else if(c == '5') 
          Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #3"));
        else if(c == '6') 
          Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #4"));
        else if(c == '7') 
          Serial.println(F("Now Testing LCD 16x2 I2C"));
        else if(c == '8') 
          Serial.println(F("Now Testing SparkFun MPU-6050 - Accelerometer and Gyro"));
        else if(c == '9') 
          Serial.println(F("Now Testing Servo - Generic Continuous Rotation (Micro Size)"));
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

