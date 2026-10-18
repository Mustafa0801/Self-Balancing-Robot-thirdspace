#include <MPU6050_tockn.h>
#include <Wire.h>
#include <AccelStepper.h>

#define rightMotor_DIR 7
#define rightMotor_STEP 6

#define leftMotor_DIR 9
#define leftMotor_STEP 8

MPU6050 sensorMPU(Wire);
AccelStepper rightMotor(AccelStepper::DRIVER, rightMotor_STEP, rightMotor_DIR);
AccelStepper leftMotor(AccelStepper::DRIVER, leftMotor_STEP, leftMotor_DIR);

const float normalAngle = 0;
float previousError = 0;

float integral;
unsigned long currentTime;
unsigned long previousTime;

const float Kp = 6.0;
const float Kd = 2.0;
const float Ki = 0.1;

void setup() {
  Wire.begin();
  sensorMPU.begin();
  Serial.begin(9600);

  rightMotor.setMaxSpeed(510);
  leftMotor.setMaxSpeed(510);

  Serial.println("Calibrating...");
  sensorMPU.calcGyroOffsets(true);
  Serial.println("Calibration complete.");

  previousTime = micros();
}

void loop() {
  sensorMPU.update();

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
