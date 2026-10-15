//  FIRST DRAFT OF FINAL CODE INCLUDING EVERYTHING 
//  HOWEVER WITHOUT PID IMPLEMENTATION

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensorMPU(Wire);  // creates instance of object

//  motor pin definitions
#define rightMotor 6      // controls speed of right motor
#define rightForward 2    
#define rightBackward 3   // these both control direction of right motor

#define leftMotor 7       // controls speed of left motor
#define leftForward 4     
#define leftBackward 5    // these both control direction of left motor

int speed = 130;
const float normalAngle = 0;    // constants used for balancing
const float deadzone = 0.5;

void setup() {
  // initializing communication:
  Wire.begin();
  sensorMPU.begin();
  Serial.begin(9600);

  // pin modes for motors:
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);

  // calibration of sensor:
  Serial.println("Calibrating, keep robot still and upright.");
  sensorMPU.calcGyroOffsets(true);
  Serial.println("Calibration complete.");

}

void loop() {
  
  sensorMPU.update();   // getting reading from sensor

  float currentAngle = sensorMPU.getAngleY();   // stores tilt of robot i.e the angle in y-axis
  Serial.print("Current angle of robot is: "+String(currentAngle));

  if (abs(currentAngle) >= 20) {      // basic way of having some speed adjustment without pid, just for better performance of this draft code
    speed = 160;
  }
  else if (abs(currentAngle) >= 35) {
    speed = 190;
  }
  else {
    speed = 130;
  }

  BalanceRobot(currentAngle);   // function which checks tilt and moves robot accordingly

  Serial.println();

  delay(5);   // short delay to limit loops per second so robot does not violently shake
}
