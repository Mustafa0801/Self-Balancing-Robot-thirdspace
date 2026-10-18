//  ALL THE MOVEMENT FUNCTIONS, WHICH ARE STOP, FORWARD, AND REVERSE

void Stop() {   // sets all to low which stops robot
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
}