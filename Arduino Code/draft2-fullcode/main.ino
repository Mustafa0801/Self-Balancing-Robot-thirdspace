// THIS WOULD BE THE FINAL CODE FOR THE ROBOT
// DON'T HAVE THE ACTUAL ROBOT SO IT CAN'T BE TESTED PROPERLY
// WILL BE TESTED A BIT WITH EMULATOR, BUT PID CONSTANTS AND OTHER VALUES CAN'T BE FINETUNED

// libraries to be used: 
#include <Wire.h>
#include <MPU6050_tockn.h>

// defining pin numbers for motors
#define rightMotor 6
#define rightForward 2
#define rightBackward 3

#define leftMotor 5
#define leftForward 4
#define leftBackward 7

MPU6050 sensorMPU(Wire);  // initializing sensor object

float previousError;  
float integral;           // variables for PID

const float Kp = 10.0;
const float Kd = 1.0;     // PID constansts
const float Ki = 0.5;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
