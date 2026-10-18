#include <MPU6050_tockn.h>
#include <Wire.h>
#include <AccelStepper.h>

#define directionPin 7
#define stepPin 6

MPU6050 sensorMPU(Wire);
AccelStepper motor1(AccelStepper::DRIVER, stepPin, directionPin);

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

  motor1.setMaxSpeed(255);

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
  
  speed = constrain(speed, -255, 255);
  
  Serial.print(" | speed is"+String(speed));

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
  float derivative = (_error - previousError) / dt;

  float _output = (_error * Kp) + (integral * Ki) + (derivative * Kd);

  previousError = _error;
  return _output;
}

void MoveRobot(float _speed) {
  int _stepSpeed = int(_speed);

  motor1.setSpeed(_stepSpeed);

  motor1.runSpeed();
}
