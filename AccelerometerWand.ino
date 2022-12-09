/* ============================================

   Notes for MPU 6050 Accelerometer connection to the Teensy
   MPU 6050     Teensy
   VCC          3.3V
   GND          GND
   SCL          pin 19
   SDA          pin 18

   Notes for Other Wires
   Top Button       pin 17
   Middle Button    pin 16
   Bottom Button    pin 15
   

============================================ */

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Bounce.h>

MPU6050 accelgyro;
unsigned long time;
int16_t ax, ay, az;
float heading;

// buttons
const int topButtonPin = 17;
const int middleButtonPin = 16;
const int bottomButtonPin = 15;

// using bounce to detect chatter from buttons and detect changes easily
Bounce topButton = Bounce(17, 10);
Bounce middleButton = Bounce(16, 10);  
Bounce bottomButton = Bounce(15, 10);

void setup() {

  // removed the while !(serial) from example code as the sketch would not run without serial monitor open
 
  // accelerometer setup
  Wire.begin();   // join I2C bus (I2Cdev library doesn't do this automatically)
  Serial.begin(115200); // Set baud rate to 115200 (figure out ways to double it)
  

  Serial.println("Initializing I2C devices...");
  delay(500);
  accelgyro.initialize();
  accelgyro.setI2CBypassEnabled(true);

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  delay(500);
  accelgyro.setFullScaleAccelRange(0);


  // button(s) setup
  pinMode(topButtonPin, INPUT);
  pinMode(middleButtonPin, INPUT);
  pinMode(bottomButtonPin, INPUT);
  
  digitalWrite(topButtonPin, LOW);
  digitalWrite(middleButtonPin, LOW);
  digitalWrite(bottomButtonPin, LOW);


}


void loop() {

  // fetches the acceleration from the accelerometer with a method from the I2Cdev library
  accelgyro.getAcceleration(&ax, &ay, &az);

  // squaring the acceleration values returned by .getAcceleration()
  float accelerationX = (ax * ax);
  float accelerationY = (ay * ay);
  float accelerationZ = (az * az);

  // calculating the total raw acceleration from the previous methods + remapping it to work with joystick axis values
  float rawAcceleration = sqrt(accelerationX + accelerationY + accelerationZ);
  float remappedAcceleration = map(rawAcceleration, 15000, 48000, 512, 1024);
  Serial.println("Raw Acceleration: "); 
  Serial.println(rawAcceleration);
  Serial.println("Remapped Acceleration: "); 
  Serial.println(remappedAcceleration);

  delay(100); // run at ~100 Hz


  // buttons

  topButton.update();
  middleButton.update();
  bottomButton.update();

// top button - controls left movement (for selection screens)
  if (topButton.fallingEdge())
  {
    Keyboard.print("a");
    Serial.println("The top button was pressed.");
    delay(20);
  }


// middle button - acts as select button
  if (middleButton.fallingEdge())
  {
    Keyboard.print("s");
    Serial.println("The middle button was pressed.");
    delay(20);
  }

// bottom button - controls right movement (for selection screens)
 if (bottomButton.fallingEdge())
  {
    Keyboard.print("d");
    Serial.println("The bottom button was pressed.");
    delay(20);
  }


   /*

   You must select Joystick from the "Tools > USB Type" menu. Use the Serial + Keyboard + Mouse + Joystick WITH the serial monitor OPEN as this is the only way I've found it to work.

   */


  Joystick.X(remappedAcceleration);
  // a brief delay, so this runs 20 times per second
  delay(50);

}









  
  
