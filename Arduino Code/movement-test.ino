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
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);

  Serial.println("stopped...");
}

void Forward(int _speed) {
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);

  Serial.println("moving forward...");
}

void Backward(int _speed){
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);

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

  delay(waitTime+500);
  Forward(speed);

  delay(waitTime);
  Stop();

  delay(waitTime+500);
  Backward(speed);

  delay(waitTime);
  Stop();

  delay(waitTime+500);

  Serial.println();
}
