// TESTING SENSOR AND ITS READINGS, THIS IS ASSUMING WE USE MPU6050
// library "MPU6050_tockn" needs to be installed

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensor(Wire);   // creates instance of object

const float normalAngle = 0;  //  this is the angle at which robot is straight
const float deadzone = 0.5;   //  basically the wiggle room for the robot to be considered balanced
                              //  if its tilt is less than or equal to 0.5 degrees from the normal then we will not move the robot
                            
void setup() {
  Wire.begin();
  Serial.begin(9600);
  sensor.begin();

  //  calibration of robot, it must be kept still and upright during this
  Serial.println("Calbrating...");
  sensor.calcGyroOffsets(true);
  Serial.println("Calbration complete.");

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
