//  CODE FOR SENSOR READING AND SPEED ADJUSTMENT WITH PID CONTROL
//  ONLY TESTS THE PID ALGORITHM ITSELF (WITHOUT ANY MOVEMENT FUNCTIONS)

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 sensorMPU(Wire);    // initialize instance of object for sensor

float normalAngle = 0;      // this can be changed according to robots resting angle
float previousError;        // declaring variables for angles/errors

float integral;                 // declaring integral variable used for PID
unsigned long currentTime;    
unsigned long previousTime;     // declaring variables used to calculate delta time

const float Kp = 10.0;
const float Kd = 1.0;     // constants used for PID, placeholder values
const float Ki = 0.5;

void setup() {
  // initializing communications 
  Wire.begin();
  sensorMPU.begin();  
  Serial.begin(9600);

  // calibrating sensor
  Serial.println("Calibrating, please keep robot still and upright...");
  sensorMPU.calcGyroOffsets(true);
  Serial.println("Calibration complete!");

  previousTime = micros();  // initializing previousTime before loop
}

void loop() {
  sensorMPU.update();   // updates readings from sensor

  // storing angle reading from sensor
  float currentAngle = sensorMPU.getAngleY();   
  Serial.print("Angle is: "+String(currentAngle));

  float error = normalAngle - currentAngle;

  // calculating and storing PID output
  float outputSpeed = CalculatePID(error);

  if (outputSpeed > 255) {
    outputSpeed = 255;
  } 
  else if (outputSpeed < -255) {
    outputSpeed = -255;
  }

  Serial.print(" | Output speed is: "+String(outputSpeed));
  
  // if speed is negative, do backwards function with abs value of outputSpeed, 
  // otherwise do forwards function with outputSpeed

  Serial.println();

  delay(5);
}


//  DELTA TIME CALCULATING FUNCTION

float CalculateDeltaTime() {
  currentTime = micros();                 
  float _deltaTime = (currentTime - previousTime) / 1000000.0;    // calculating difference to get time between loops, converted to seconds
  previousTime = currentTime;                       // updating previousTime

  Serial.print(" | dt is: "+String(_deltaTime));
  return _deltaTime;
}


//  PID CALCULATING FUNCTION

float CalculatePID(float _error) {
  float _dt = CalculateDeltaTime();

  if (_dt <= 0) {   // to prevent dividing by zero while calculating derivative
    return 0;
  }

  integral = integral + (_error * _dt);

  if (integral > 200 || integral < -200) {  // prevents integral windup
    integral = integral - (_error * _dt);
  }

  float derivative = (_error - previousError) / _dt;

  previousError = _error;     // updating previousAngle

  float _output = (_error * Kp) + (derivative * Kd) + (integral * Ki);
  return _output;
}
