/* ============================================

   Notes for connection to the Teensy
   MPU 6050     Teensy
   Vcc          3.3V
   GND          GND
   SCL          pin A5
   SDA          pin A4
   XDA          NC  (no connection)
   XCL          NC  (no connection)
   ADO          NC
   INT          pin 2

============================================ */

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;
unsigned long time;
int16_t ax, ay, az;
float heading;



void setup() {

  // accelerometer setup
  Wire.begin();   // join I2C bus (I2Cdev library doesn't do this automatically)
  Serial.begin(115200); // Set baud rate to 115200 (figure out ways to double it)
  while (!Serial);

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
  
}


void loop() {
  // these methods (and a few others) are also available
  accelgyro.getAcceleration(&ax, &ay, &az);
  
  float accelerationX = (ax * ax);
  float accelerationY = (ay * ay);
  float accelerationZ = (az * az);

  float rawAcceleration = sqrt(accelerationX + accelerationY + accelerationZ);
  float remappedAcceleration = map(rawAcceleration, 15000, 48000, 512, 1024);
  Serial.println("Raw Acceleration: "); 
  Serial.println(rawAcceleration);
  Serial.println("Remapped Acceleration: "); 
  Serial.println(remappedAcceleration);

  delay(100); // run at ~100 Hz


   /* Basic USB Joystick Example
   Teensy becomes a USB joystick

   You must select Joystick from the "Tools > USB Type" menu

   */


  Joystick.X(remappedAcceleration);
  // a brief delay, so this runs 20 times per second
  delay(50);

}









  
  
