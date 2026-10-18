//  ALL THE MOVEMENT FUNCTIONS, WHICH ARE STOP, FORWARD, AND REVERSE

void Stop() {   // sets all to low which stops robot
  digitalWrite(rightMotor, LOW);
  digitalWrite(leftMotor, LOW);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
}

void Forward(int _speed) {      // sets forward direction pins to HIGH and sets speed according to parameter
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);

  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
}

void Backward(int _speed) {     // sets backward direction pins to HIGH and sets speed according to parameter
  analogWrite(rightMotor, _speed);
  analogWrite(leftMotor, _speed);

  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);

  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
} 
