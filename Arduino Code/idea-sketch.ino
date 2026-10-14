// general idea/layout for the code

//  defining pin numbers, 2 for left and right speed, 4 for controlling each sides direction
//  pin number or numbers for sensor

//  PID algorithm will be used so variables for it
//  --- base speed and output speed variables
//  --- error & previous error variables 
//  --- integral, and time variables to calculate delta time
//  --- kp, ki, kd constants

//  movement functions (in a seperate tab)
//  --- forward, back and stop functions, take speed as parameter
//  --- only 1 speed parameter since left and right speed should be same to balance it

//  function to take readings from accelerometer and/or gyroscope (seperate tab)
//  --- error calculated using readings

//  functions to calculate dt, and then pid output using error (seperate tab)
//  --- pid formula is same, output = (kp*error) + (ki*integral) + (kd*derivative)
//  --- where integral += error*dt , and derivative = (error - previous error)/dt
//  --- also prevent integral windup by limiting output

void setup() {
  
  //  pin modes for everything
  //  initialize last time
  //  Serial.begin also maybe temporarily used for debugging

}

void loop() {
  
  //  store error from sensor reading function
  //  store pid output with error as paramter

  //  calculate output speed using base speed and pid output
  //  according to this decide whether to move forward or backward,
  //  --- if speed negative move backward (absolute value of speed used as parameter)
  //  --- otherwise move forward
  //  --- calculated speed must be >= -255 and <= 255 since the values that can be output to the motors are 0-255
  //  --- in other words absolute value of speed >= 0 and <= 255

}
