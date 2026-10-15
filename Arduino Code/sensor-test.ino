// TESTING SENSOR AND ITS READINGS, THIS IS ASSUMING WE USE MPU6050
// library "MPU6050_tockn" needs to be installed

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensor(Wire);   // creates instance of object

const float normalAngle = 0;  //  this is the angle at which robot is straight
const float deadzone = 0.5;   //  basically the wiggle room for the robot to be considered balanced
                              //  if its tilt is less than or equal to 0.5 degrees from the normal then we will not move the robot
                            
//  no need for pin numbers of sensor, its SDA and SCL will be connected to A4 and A5 pins respectively, which Arduino will recognize automatically

void CheckTilt(float _currentAngle) {
  //  function to check the angle and print according movement
  
  if (_currentAngle > (normalAngle + deadzone)) {
    Serial.print(" | robot is tilted too far forward, moving backwards...");
  } 
  else if (_currentAngle < (normalAngle - deadzone)) {
    Serial.print(" | robot is tilted too far backward, moving forward...");
  }
}                

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
  // for now we will just be taking readings and printing in serial to test the functionality of the sensors and the code

  sensor.update();
  float currentAngle = sensor.getAngleY();
  Serial.print("Angle of robot is: "+String(currentAngle));

}
