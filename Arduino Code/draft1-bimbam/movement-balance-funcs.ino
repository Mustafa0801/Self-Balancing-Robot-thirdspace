//  MOVEMENT FUNCTIONS

void Stop() {
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);   // all set to low, robot does not move

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
}

void Forward(int _speed) {
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);   // forward direction set to high, moves forward at set speed

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
}

void Backward(int _speed) {
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);  // backward direction set to high, moves backward at set speed

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
}


//  FUNCTION TO CHECK TILT AND BALANCE THE ROBOT

void BalanceRobot(float _currentAngle) {
  if (abs(_currentAngle) > 45.0) {    // if robot is too far tilted on either side, then stop balancing to prevent it going out of control
    Stop();
    Serial.print(" | robot has fallen...");
  }
  else if (_currentAngle > (normalAngle + deadzone)) {    // robot angle more than desired angle, move forward to compensate
    Forward(speed);
    Serial.print(" | robot is tilted forward, moving forwards...");
  }
  else if (_currentAngle < (normalAngle - deadzone)) {    // robot angle less than desired angle, move backwards to compensate
    Backward(speed);
    Serial.print(" | robot is tilted backward, moving backwards...")
  }
  



}
