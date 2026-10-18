// THIS WOULD BE THE FINAL CODE FOR THE ROBOT
// DON'T HAVE THE ACTUAL ROBOT SO IT CAN'T BE TESTED PROPERLY
// WILL BE TESTED A BIT WITH EMULATOR, BUT PID CONSTANTS AND OTHER VALUES CAN'T BE FINETUNED

// NOTE: the serial messages are mostly used for debugging, 
// when code is finalised then serial stuff can be removed to prevent it from slowing down the loop

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

unsigned long currentTime;
unsigned long previousTime;   // variables for calculating delta time 

void setup() {
  
  // initializing communications
  Wire.begin();
  sensorMPU.begin();
  Serial.begin(9600);

  // pin modes for motors
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);

  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);

  // calibrating sensor
  Serial.println("Calibrating, keep robot still and upright...");
  sensorMPU.calcGyroOffsets(true);
  Serial.println("Calibration complete.");

  // initializing previous time
  previousTime = micros(); 
}

void loop() {
  sensorMPU.update();   // updates readings from sensor

  float angleError = sensorMPU.getAngleY();   // stores the tilt, which is angle in y axis
  Serial.print("Angle is: ");
  Serial.print(angleError);

  float outputPID = CalculatePID(angleError);   // calculates and stores speed
  constrain(outputPID, -255.0, 255.0);          // limits speed to valid PWM ranges
                                            // will use absolute value later so negative values till -255 are allowed here

  Serial.print(" | speed is: ");
  Serial.print(outputPID);

}
