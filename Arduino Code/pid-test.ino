//  CODE FOR SENSOR READING AND SPEED ADJUSTMENT WITH PID CONTROL
//  ONLY TESTS THE PID ALGORITHM ITSELF (WITHOUT ANY MOVEMENT FUNCTIONS)

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensorMPU(Wire);

float currentAngle;
float previousAngle;

float integral;

const float Kp = 10.0;
const float Kd = 1.0;
const float Ki = 0.5;

void setup() {
 
  Wire.begin();
  sensorMPU.begin();
  Serial.begin(9600);

  Serial.println("Calibrating, please keep robot still and upright...");
  sensorMPU.calcGyroOffsetsY(true);
  Serial.println("Calibration complete!");

}

void loop() {
  

}
