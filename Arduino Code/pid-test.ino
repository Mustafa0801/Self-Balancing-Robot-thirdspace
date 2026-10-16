//  CODE FOR SENSOR READING AND SPEED ADJUSTMENT WITH PID CONTROL
//  ONLY TESTS THE PID ALGORITHM ITSELF (WITHOUT ANY MOVEMENT FUNCTIONS)

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensorMPU(Wire);

float currentAngle;
float previousAngle;

float integral;
unsigned long currentTime;
unsigned long previousTime;

const float Kp = 10.0;
const float Kd = 1.0;
const float Ki = 0.5;

void setup() {
 
  Wire.begin();
  sensorMPU.begin();
  Serial.begin(9600);

  Serial.println("Calibrating, please keep robot still and upright...");
  sensorMPU.calcGyroOffsets(true);
  Serial.println("Calibration complete!");

  previousTime = micros()/1000000.0;
}

void loop() {
  sensorMPU.update();

  currentAngle = sensorMPU.getAngleY();
  Serial.print("Angle is: "+String(currentAngle));

  float outputSpeed = CalculatePID();
  Serial.print(" | Output speed is: "+String(outputSpeed));
  
  // if speed is negative, do backwards function with abs value of outputSpeed, 
  // otherwise do forwards function with outputSpeed

  Serial.println();
  delay(5);
}


//  DELTA TIME CALCULATING FUNCTION

float CalculateDeltaTime() {
  currentTime = micros()/1000000.0;
  float _deltaTime = currentTime - previousTime;
  previousTime = currentTime;

  Serial.print(" | dt is: "+String(_deltaTime));
  return _deltaTime;
}


//  PID CALCULATING FUNCTION

float CalculatePID() {
  float _dt = CalculateDeltaTime();

  if (_dt <= 0) {
    return 0;
  }

  integral = integral + (currentAngle * _dt);
  float derivative = (currentAngle - previousAngle) / _dt;

  previousAngle = currentAngle;

  float _output = (currentAngle * Kp) + (derivative * Kd) + (integral * Ki);
  return _output;
}
