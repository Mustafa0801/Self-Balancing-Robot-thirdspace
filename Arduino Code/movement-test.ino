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
int waitTime = 1000;      // value for time between testing each function in the loop


//  ALL THE MOVEMENT FUNCTIONS

void Stop() {
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, LOW);
  digtialWrite(leftBackward, LOW);

  Serial.println("stopped...");
}

void Forward() {
  analogWrite(rightMotor, speed);
  analogWrite(leftMotor, speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
