// CODE FOR TESTING WITH EMULATOR (THIS IS THE DRAFT2 CODE), SINCE DC MOTORS ARENT AVAILABLE LEDS ARE USED INSTEAD
// SPEED OUTPUT CAN ONLY BE SEEN IN SERIAL AND NOT PHYSICALLY, THE LEDS ONLY SHOW WHICH DIRECTION IS ON
// SO CODE RELATED TO MOTOR SPEED PINS HAS BEEN REMOVED (I PUT DOUBLE SLASH NEXT TO IT)

// led colors: red - rightForward, yellow - rightBackward, blue - leftForward, green - leftBackward

// NOTE: the serial messages are mostly used for debugging, 
// when code is finalised then serial stuff can be removed to prevent it from slowing down the loop

// libraries to be used: 
#include <Wire.h>
#include <MPU6050_tockn.h>

// defining pin numbers for motors

//#define rightMotor 6      // controls right motor speed
#define rightForward 2
#define rightBackward 3   // these both control respective directions of right motor

//#define leftMotor 5       // controls left motor speed
#define leftForward 4
#define leftBackward 7    // these both control respective directions of left motor


MPU6050 sensorMPU(Wire);  // initializing sensor object

const float normalAngle = 0;  // constant used to calculate error, can be adjusted according to robot resting angle
float previousError;  
float integral;           // variables for PID

const float Kp = 5.0;
const float Kd = 0.5;     // PID constansts
const float Ki = 0.1;

unsigned long currentTime;
unsigned long previousTime;   // variables for calculating delta time 

void setup() {
  
  // initializing communications
  Wire.begin();
  sensorMPU.begin();
  Serial.begin(9600);

  // pin modes for motors
  //pinMode(rightMotor, OUTPUT);
  //pinMode(leftMotor, OUTPUT);

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
  delay(2);         // short delay to prevent too many loops per second, allowing for less rapid movement while balancing
}

//  DELTA TIME CALCULATOR FUNCTION:

float CalculateDeltaTime() {
  currentTime = micros();
  float _dt = (currentTime - previousTime) / 1000000.0;   // delta time converted to seconds
  previousTime = currentTime;   // updates previous time

  Serial.print(" | dt is: ");
  Serial.print(_dt);

  return _dt;
}

//  PID CALCULATING FUNCTION:

float CalculatePID(float _error) {
  float deltaTime = CalculateDeltaTime();

  if (deltaTime == 0) {   // prevents dividing by zero if dt = 0
    return 0;
  }

  integral += _error * deltaTime;
  integral = constrain(integral, -100.0, 100.0);   // prevents integral windup 

  float derivative = (_error - previousError) / deltaTime; 

  previousError = _error;     // updates previous error

  float _output = (_error * Kp) + (derivative * Kd) + (integral * Ki);
  return _output;
}

//  ALL THE MOVEMENT FUNCTIONS, WHICH ARE STOP, FORWARD, AND REVERSE

void Stop() {   // sets all to low which stops robot
  //digitalWrite(rightMotor, LOW);
  //digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
}

void Forward(int _speed) {      // sets forward direction pins to HIGH and sets speed according to parameter
  //analogWrite(rightMotor, _speed);
  //analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
}

void Backward(int _speed) {     // sets backward direction pins to HIGH and sets speed according to parameter
  //analogWrite(rightMotor, _speed);
  //analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
} 
