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

//  function to take readings from accelerometer and/or gyroscope
//  --- error calculated using readings

//  functions to calculate dt, and then pid output using error
//  --- pid formula is same, output = (kp*error) + (ki*integral) + (kd*derivative)
//  --- where integral += error*dt , and derivative = (error - previous error)/dt


void setup() {
  

}

void loop() {
  

}
