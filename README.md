# Stepper-Servo
An Arduino library to control a stepper motor as you would a servo.

**This library is still in development, so please report any issues, and I'll do my best to fix them as soon as I see them.**

## EXAMPLE CIRCUIT AND CODE


![Sketch2](https://user-images.githubusercontent.com/62073336/182627705-b19bb305-1a0f-4cd7-832f-45f257f7430f.jpg)


```
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
```

## DOCUMENTATION


### Methods
`StepServo motor( < step pin >, < dir pin >, < enable pin > )`- The class used by this library. In this case, the name is `motor`, but can be anything you like.


`motor.enable()` - This will enable the motor. It will lock in place and move when commanded to. Motor is enabled by default.

`motor.disable()` - This will disable the motor. It can be turned freely, and will not respond to commands. Motor is enabled by default.

`motor.setRPM( < RPM > )` - This sets the motor's speed, in Rotations Per Minute. 60 by default.

`motor.setEndStops( < Endstop 1 >, < Endstop 2 > )` - This sets the lower and upper endstops, in degrees. This prevents the motor from turning too far in your specific project. The motor will stop moving once it hits this point. If told to move to a position beyond this point, the motor will move to the nearest stop instead. Defaults are 0 and 360.

`motor.setStepAngle( < step angle in degrees > )` - This sets how many degrees the motor moves by per step. 1.8 by default (compatible with most NEMA stepper motors)

`motor.setMicrosteps( < Microstepping value as a decimal > )` - This sets the microstepping multiplier, as a decimal. For example, for 1/4 microsteps, use a value of 0.25. Defaults to no microstepping (value of 1)

`motor.useBlockingMode( < true / false > )` - This enables or disables blocking mode. In blocking mode, the program waits until the motor has finished moving before proceeding. In non-blocking mode, the program can move the motor while doing other tasks, but needs extra code to do so. Defaults to `true` (blocking mode ON).
**NOTE: In blocking mode, you can only move one motor at a time, whereas in non-blocking mode, you can move multiple at once.**

`motor.zero()` - Returns step count to zero.
**IMPORTANT: BE SURE TO ZERO BEFORE ENABLING, IF MOTOR HAS PREVIOUSLY BEEN DISABLED!** Otherwise the motor will rotate to an unexpected position.
**Always zero after changing microstep settings, or the motor may move to a random position.**

`motor.moveTo( < angle > )` - This moves the motor to the absolute specified angle, much like a servo motor. In blocking mode, this will immediately move the motor and hold the program until the motor has finished moving. In non-blocking mode, this will only work if `motor.run()` is being repeatedly called.

`motor.moveBy( < angle > )` - This moves the motor relatively, meaning that a value of 90 will advance the motor by 90 degrees, and a value of -90 will move it backwards by 90 degrees. In blocking mode, this will immediately move the motor and hold the program until the motor has finished moving. In non-blocking mode, this will only work if `motor.run()` is being repeatedly called.

`motor.run()` - Required for motor to move in non-blocking mode. Place in a loop where it will be continuously called.

### Variables and defaults

`motor.endStop1` - double - Lower end stop, in degrees. Defaults to 0.

`motor.endStop2` - double - Upper end stop, in degrees. Defaults to 360.

`motor.RPM` - double - Speed of the motor, in Rotations Per Minute. Defaults to 60.

`motor.microSteps` - double - Microstepping setting. For 1/4 microstepping, it will be 0.25, etc. Defaults to 1 (no microstepping).

`motor.stepAngle` - double - The number of degrees per step of the motor. Defaults to 1.8 (Compatible with most NEMA steppers)

`motor.endStopCollision` - bool - `true` if the motor touched an end stop on its most recent movement, `false` otherwise.

`motor.enabled` - bool - Whether the motor is enabled (`true`) or not (`false`). Defaults to `true`.

`motor.blocking` - bool - If blocking mode is enabled on this motor (`true`) or not (`false`). Defaults to `true`.

`motor.currentAngle` - double - The motor's current virtual angle. Defaults to 0.
**NOTE: This does not account for skips in the motor, any forceful movement while the motor is enabled, or any movement at all when the motor is disabled.**

`motor.currentSteps` - long - The number of steps the motor has moved. See the note above. Defaults to 0.

`motor.demandSteps` - long - The number of steps the motor is heading for. This is the number that the motor follows. Defaults to 0.

`motor.debug` - bool - enable non-helpful debug messages in the Serial Monitor. Note: call `Serial.begin` before using this.
