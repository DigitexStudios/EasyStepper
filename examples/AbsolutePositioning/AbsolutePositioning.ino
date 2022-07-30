/*
 * Stepper motor as a servo
 * Basic motion example sketch
 * Created by Liam Timpane
 */



#include "StepServo.h" // Include the stepper servo library

StepServo motor(3, 2, 4); // Create the motor object. The stepper driver has the STP pin on pin 3, DIR pin on pin 2, and ENABLE pin on pin 4.

void setup() {
  
  motor.setMicrosteps(0.25); // Set the motor to use quarter microsteps
  
  motor.debug = true; // Allow printing to serial monitor
  
  Serial.begin(9600);
}

void loop() {
  
  motor.setRPM(30); // Set the motor to 60 RPM (1 rotation per 2 seconds)
  motor.moveTo(360); // Rotate to 360 degrees
  
  Serial.println(motor.currentAngle);
  delay(1000);

  motor.setRPM(60); // Set the motor to 60 RPM (1 rotation per second)
  motor.moveTo(0); // Rotate to zero degrees
  
  Serial.println(motor.currentAngle);
  delay(1000);
  
}
