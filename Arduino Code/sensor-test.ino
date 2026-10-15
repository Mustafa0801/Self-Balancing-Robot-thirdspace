//  TESTING SENSOR AND ITS READINGS, THIS IS ASSUMING WE USE MPU6050
//  library "MPU6050_tockn" needs to be installed
//  also this is testing WITHOUT PID IMPLEMENTATION

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensor(Wire);   // creates instance of object

const float normalAngle = 0;  //  this is the angle at which robot is straight
const float deadzone = 0.5;   //  basically the wiggle room for the robot to be considered balanced
                              //  if its tilt is less than or equal to 0.5 degrees from the normal then we will not move the robot
                            
//  no need for pin numbers of sensor, its SDA and SCL will be connected to A4 and A5 pins respectively, which Arduino will recognize automatically

void CheckTilt(float _currentAngle) {
  //  function to check the angle and print in serial according movement
  
  if (_currentAngle > (normalAngle + deadzone)) {
    //  backward moving function
    Serial.print(" | robot is tilted too far forward, moving backwards...");
  } 
  else if (_currentAngle < (normalAngle - deadzone)) {
    //  forward moving function
    Serial.print(" | robot is tilted too far backward, moving forward...");
  }
  else {
    //  stopping function
    Serial.print(" | robot is balanced, stopping...");
  }
}                

void setup() {
  Wire.begin();
  sensor.begin();

  Serial.begin(9600);

  //  calibration of robot, it must be kept still and upright during this
  Serial.println("Calbrating...");
  sensor.calcGyroOffsets(true);
  Serial.println("Calbration complete.");

}

void loop() {
  // for now we will just be taking readings and printing in serial to test the functionality of the sensors and the code

  sensor.update();    // updates readings from sensor
  float currentAngle = sensor.getAngleY();    // stores the tilt of the robot i.e the angle in y axis
  Serial.print("Angle of robot is: "+String(currentAngle));

  CheckTilt(currentAngle);    // prints the according movement function in serial according to angle

  Serial.println();
  delay(5);   // delay to ensure a set number of loops per second, so that movement of robot is not too quick or shaky
}
