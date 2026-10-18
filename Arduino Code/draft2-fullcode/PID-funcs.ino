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
   
}