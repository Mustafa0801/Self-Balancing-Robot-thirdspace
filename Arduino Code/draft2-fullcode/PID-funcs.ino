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
  integral = constrain(integral, -100, 100);   // prevents integral windup 

  float derivative = (_error - previousError) / deltaTime; 

  previousError = _error;     // updates previous error

  float _output = (_error * Kp) + (derivative * Kd) + (integral * Ki);
  return _output;
}
