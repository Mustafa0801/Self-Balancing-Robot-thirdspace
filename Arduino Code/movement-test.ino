//  test for movement functions, 
//  only tests the movement periodically, movement does not depend on readings and is not expected to balance the robot

//  pin numbers for motor
#define rightMotor 6      // controls speed of right motor
#define rightForward 2    // these both control direction of right motor
#define rightBackward 3

#define leftMotor 7       // controls speed of left motor
#define leftForward 4     // these both control direction of left motor
#define leftBackward 5

int speed = 150;          // placeholder value for speed
int waitTime = 500;      // value for time between testing each function in the loop


//  ALL THE MOVEMENT FUNCTIONS

void Stop() {
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);     // set all to LOW, making robot stop moving

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);

  Serial.println("stopped...");
}

void Forward(int _speed) {
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);     // move both motors in forward direction at set speed

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);

  Serial.println("moving forward...");
}

void Backward(int _speed){
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);    // move both motors in backward direction at set speed

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);

  Serial.println("moving backward...");
}


// MAIN PROGRAM

void setup() {
  // pin modes 

  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // movement testing loop

  delay(waitTime+500);  // waits 1 second
  Forward(speed);

  delay(waitTime);      // waits 0.5 seconds, so that the robot moves for short time and is stopped for longer time
  Stop();               // ensuring robot does not go out of control when testing it

  delay(waitTime+500);
  Backward(speed);

  delay(waitTime);
  Stop();

  delay(waitTime+500);

  Serial.println();
}
