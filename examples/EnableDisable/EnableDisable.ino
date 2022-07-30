/* 
 * Stepper motor as a servo
 * Enabling / disabling sketch
 * Created by Liam Timpane
 * 
 */

#include "StepServo.h" // Include the stepper servo library

StepServo motor(3, 2, 4); // Create the motor object. The stepper driver has the STP pin on pin 3, DIR pin on pin 2, and ENABLE pin on pin 4.

void setup() {
  
}



void loop() {
  motor.disable(); // Disable motor (Motor will become freely rotatable)
  
  delay(5000);
  
  motor.enable(); // Enable motor (Motor will lock its position)
  
  delay(5000);
}
