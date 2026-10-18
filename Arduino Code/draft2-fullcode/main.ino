// THIS WOULD BE THE FINAL CODE FOR THE ROBOT
// DON'T HAVE THE ACTUAL ROBOT SO IT CAN'T BE TESTED PROPERLY
// WILL BE TESTED A BIT WITH EMULATOR, BUT PID CONSTANTS AND OTHER VALUES CAN'T BE FINETUNED

// NOTE: the serial messages are mostly used for debugging, 
// when code is finalised then serial stuff can be removed to prevent it from slowing down the loop

// libraries to be used: 
#include <Wire.h>
#include <MPU6050_tockn.h>

// defining pin numbers for motors

#define rightMotor 6      // controls right motor speed
#define rightForward 2
#define rightBackward 3   // these both control respective directions of right motor

#define leftMotor 5       // controls left motor speed
#define leftForward 4
#define leftBackward 7    // these both control respective directions of left motor


MPU6050 sensorMPU(Wire);  // initializing sensor object

const float normalAngle = 0;  // constant used to calculate error, can be adjusted according to robot resting angle
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

  float currentAngle = sensorMPU.getAngleY();   // stores the tilt, which is angle in y axis
  Serial.print("Angle is: ");
  Serial.print(currentAngle);

  float currentError = currentAngle - normalAngle;

  float outputPID = CalculatePID(currentError);       // calculates and stores speed
  outputPID = constrain(outputPID, -255.0, 255.0);    // limits speed to valid PWM ranges
                                                      // will use absolute value later so negative values till -255 are allowed here

  Serial.print(" | speed is: ");
  Serial.print(outputPID);


  // moving robot according to speed 

  if (abs(currentError) > 45) {    // if robot tilted too far on either direction
    Stop();                        // then emergency stop
  }
  else {    // if angle isnt too far then robot will move according to speed
    int outputSpeed = round(abs(outputPID));  // abs value since PWM range is 0-255, and round since speed needs to be int

    if (outputPID > 0) {    // if pid output positive then move forward
      Forward(outputSpeed);
    }
    else if (outputPID < 0) {   // if pid output negative then move backward
      Backward(outputSpeed);
    }
    else {    // when pid output is zero then robot is balanced
      Stop();
    }
  }

  Serial.println();
  delay(5);
}
