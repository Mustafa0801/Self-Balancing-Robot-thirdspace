//  THIS IS CODE FOR WOKWI EMULATOR
//  PURPOSE IS TO TEST CODE SINCE I DON'T PHYSICALLY HAVE THE ROBOT

//  SENSOR RELATED CODE AND PID STUFF IS ESSENTIALLY THE SAME
//  HOWEVER CODE FOR MOTORS IS VASTLY DIFFERENT SINCE STEPPER MOTORS ARE USED
//  CUZ WOKWI DOESNT HAVE DC MOTORS AVAILABLE :( 
//  THE ACTUAL FINAL CODE WILL BE WRITTEN FOR DC MOTORS THOUGH

//  libraries
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <AccelStepper.h>

//  pin numbers for the direction and step pins of motor drivers
#define rightMotor_DIR 7
#define rightMotor_STEP 6

#define leftMotor_DIR 9
#define leftMotor_STEP 8

//  initializing object for sensor
MPU6050 sensorMPU(Wire);

//  initializing an object for each motor and defining its behaviour
AccelStepper rightMotor(AccelStepper::DRIVER, rightMotor_STEP, rightMotor_DIR);
AccelStepper leftMotor(AccelStepper::DRIVER, leftMotor_STEP, leftMotor_DIR);

const float normalAngle = 0;  
float previousError = 0;     // used to calculate error i.e the tilt of the robot

float integral;              // used for PID
unsigned long currentTime;   
unsigned long previousTime;  // used for delta time calculations

const float Kp = 6.0;
const float Kd = 2.0;   // constants for PID
const float Ki = 0.1;   // unfortunately can't really be finetuned just through the emulator

void setup() {
  Wire.begin();
  sensorMPU.begin();    // initializing communications
  Serial.begin(9600);

  rightMotor.setMaxSpeed(510);   // sets max speed for each motor
  leftMotor.setMaxSpeed(510);

  // calibrating sensor
  Serial.println("Calibrating...");
  sensorMPU.calcGyroOffsets(true);
  Serial.println("Calibration complete.");

  previousTime = micros();    // initializes previousTime
}

void loop() {
  sensorMPU.update();   // updates readings from sensor

  float currentAngle = sensorMPU.getAngleY();
  Serial.print("Angle is: ");
  Serial.print(currentAngle);

  float error = normalAngle - currentAngle;
  float speed = CalcPID(error);
  
  speed = constrain(speed, -510.0, 510.0);

  MoveRobot(speed);

  Serial.println();
}


float DeltaTime() {
  currentTime = micros();
  float _dt = (currentTime - previousTime) / 1000000.0;
  previousTime = currentTime;

  Serial.print(" | dt is: "+String(_dt));
  return _dt;
}

float CalcPID(float _error) {
  float dt = DeltaTime();

  integral += _error * dt;
  integral = constrain(integral, -200.0, 200.0);
  float derivative = (_error - previousError) / dt;

  float _output = (_error * Kp) + (integral * Ki) + (derivative * Kd);

  previousError = _error;
  return _output;
}

void MoveRobot(float _speed) {
  int _stepSpeed = round(_speed) * -1;

  Serial.print(" | speed is: "+String(_stepSpeed));

  rightMotor.setSpeed(_stepSpeed);
  leftMotor.setSpeed(_stepSpeed);

  rightMotor.runSpeed();
  leftMotor.runSpeed();
}
