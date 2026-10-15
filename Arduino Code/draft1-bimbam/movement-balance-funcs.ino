//  MOVEMENT FUNCTIONS

void Stop() {
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);   // all set to low, robot does not move

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
}

void Forward() {
  analogWrite(rightMotor, speed);
  analogWrite(leftMotor, speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);   // forward direction set to high, moves forward at set speed

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
}

void Backward() {
  analogWrite(rightMotor, speed);
  analogWrite(leftMotor, speed);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);  // backward direction set to high, moves backward at set speed

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
}


//  FUNCTION TO CHECK TILT AND BALANCE THE ROBOT

void BalanceRobot(float _currentAngle) {




  
}
