//  FIRST DRAFT OF FINAL CODE INCLUDING EVERYTHING 
//  HOWEVER WITHOUT PID IMPLEMENTATION

#include <Wire.h>
#include <MPU6050_tockn.h>

//  motor pin definitions
#define rightMotor 6      // controls speed of right motor
#define rightForward 2    
#define rightBackward 3   // these both control direction of right motor

#define leftMotor 7       // controls speed of left motor
#define leftForward 4     
#define leftBackward 5    // these both control direction of left motor

const int speed = 150;
const float normalAngle = 0;    // constants used for balancing
const float deadzone = 0.5;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
