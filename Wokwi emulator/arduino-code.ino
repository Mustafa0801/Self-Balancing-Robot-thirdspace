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

  float currentAngle = sensorMPU.getAngleY();   // stores angle in y axis, i.e the tilt
  Serial.print("Angle is: ");
  Serial.print(currentAngle);

  float error = normalAngle - currentAngle;   
  float speed = CalcPID(error);   // stores output from pid algorithm as speed 
  
  // max and min value for speed, 
  // since stepper motors are being used the 255 limit for PWM doesnt apply
  // much higher speeds can be set but decided to stick with double of the usual values
  speed = constrain(speed, -510.0, 510.0);  

  MoveRobot(speed);   // moves motors in the according direction and speed

  Serial.println();
}

// function to calculate dt
float DeltaTime() {         
  currentTime = micros();
  float _dt = (currentTime - previousTime) / 1000000.0;   // the time between loops in seconds
  previousTime = currentTime;   // updates previous time

  Serial.print(" | dt is: "+String(_dt));
  return _dt;
}

// function to calculate pid
float CalcPID(float _error) {     
  float dt = DeltaTime();

  integral += _error * dt;
  integral = constrain(integral, -200.0, 200.0);      // preventing integral windup
  float derivative = (_error - previousError) / dt;

  float _output = (_error * Kp) + (integral * Ki) + (derivative * Kd);    // this output will be speed

  previousError = _error;   // updates previous error
  return _output;
}

// function which moves the motors according to pid output i.e speed
void MoveRobot(float _speed) {          
  
  // storing integer value for speed since we need integer paramater 
  // also inverts the sign (positive/negative) for the desired direction
  // a positive angle would calculate negative speed so sign is flipped so robot moves in correct direction
  int _stepSpeed = round(_speed) * -1;

  Serial.print(" | speed is: "+String(_stepSpeed));

  // setting speed for both motors
  rightMotor.setSpeed(_stepSpeed);  
  leftMotor.setSpeed(_stepSpeed);

  // and then running the motors at that speed
  rightMotor.runSpeed();
  leftMotor.runSpeed();
}
