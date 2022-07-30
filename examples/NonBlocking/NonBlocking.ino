/*
 * Stepper motor as a servo
 * Non-blocking motion example sketch
 * Created by Liam Timpane
 * 
 * The default mode for this library is blocking, meaning that every call to "moveTo" will stop code execution until the move is complete. Enabling non-blocking mode allows the motor to move while the microcontroller does other tasks.
 * 
 */

#include "StepServo.h" // Include the stepper servo library

StepServo motor(3, 2, 4); // Create the motor object. The stepper driver has the STP pin on pin 3, DIR pin on pin 2, and ENABLE pin on pin 4.

unsigned long prevMillis = 0;

void setup() {
  
  motor.setMicrosteps(0.25); // Set the motor to use quarter microsteps
  
  motor.debug = true; // Allow printing to serial monitor

  motor.setRPM(60); // Set motor speed to 60 RPM (1 rotation per second)

  motor.useBlockingMode(false); // Turn off blocking mode
  
  Serial.begin(9600);

  prevMillis = millis();
}



void loop() {

  if(millis() - prevMillis >= 2000 and millis() - prevMillis < 4000) {
    motor.moveTo(270);
  } else if (millis() - prevMillis >= 4000) {
    prevMillis = millis();
  } else {
    motor.moveTo(90);
  }
  
  motor.run(); // <-- This must be called continuously for the motion to work correctly. May add up to ~3ms or so delay to loops.
}
