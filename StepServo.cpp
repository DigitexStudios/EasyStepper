/*
    EasyStepper.h - Library for simplified stepper control
    Created by Liam Timpane, June 30, 2022
    Copyright (c) Liam Timpane, 2022. All rights reserved.
*/

#include "Arduino.h"
#include "EasyStepper.h"

EasyStepper::EasyStepper(int stepPin, int dirPin, int enPin)
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enPin, OUTPUT);
    digitalWrite(enPin, LOW);
    stepPinNumber = stepPin;
    dirPinNumber = dirPin;
    enPinNumber = enPin;
    microSteps = 1;
    endStop1 = 0;
    endStop2 = 360;
    RPM = 60;
    stepAngle = 1.8;
    currentSteps = 0;
    demandSteps = 0;
    blocking = true;
    enabled = true;
    debug = false;
}

void EasyStepper::setEndStops(double startDeg, double endDeg)
{
    endStop1 = startDeg;
    endStop2 = endDeg;
}

void EasyStepper::setRPM(double speed)
{
    RPM = speed;
    delayTime = ((stepAngle) / (RPM * 6)) * 1000000 * microSteps;
}

void EasyStepper::useBlockingMode(bool state)
{
    blocking = state;
}

void EasyStepper::setStepAngle(double angle)
{
    stepAngle = angle;
}

void EasyStepper::setMicrosteps(double microstps)
{
    microSteps = microstps;
    delayTime = ((stepAngle) / (RPM * 6)) * 1000000 * microSteps;
}

void EasyStepper::enable()
{
    digitalWrite(enPinNumber, LOW);
    enabled = true;
}

void EasyStepper::disable()
{
    digitalWrite(enPinNumber, HIGH);
    enabled = false;
}

void EasyStepper::moveTo(double deg)
{
    delayTime = ((stepAngle) / (RPM * 6)) * 1000000 * microSteps;
    demandSteps = (deg / (stepAngle * microSteps));
    if (blocking == true)
    {
        while (demandSteps != currentSteps)
        {

            if (currentSteps < demandSteps)
            {
                endStopCollision = false;
                currentSteps += 1;
                digitalWrite(dirPinNumber, LOW);
                digitalWrite(stepPinNumber, HIGH);
                delayMicroseconds(20);
                digitalWrite(stepPinNumber, LOW);
                delayMicroseconds(delayTime);
            }
            if (currentSteps > demandSteps)
            {
                endStopCollision = false;
                currentSteps -= 1;
                digitalWrite(dirPinNumber, HIGH);
                digitalWrite(stepPinNumber, HIGH);
                delayMicroseconds(20);
                digitalWrite(stepPinNumber, LOW);
                delayMicroseconds(delayTime);
            }
            currentAngle = currentSteps * (stepAngle * microSteps);
            if (currentSteps == (endStop1 / (stepAngle * microSteps)) or currentSteps == (endStop2 / (stepAngle * microSteps)))
            {
                endStopCollision = true;
                if (debug)
                {
                    Serial.println("Collided with end stop!");
                }
                break;
            }
        }
    }
}

void EasyStepper::moveBy(double deg)
{
    delayTime = ((stepAngle) / (RPM * 6)) * 1000000 * microSteps;
    demandSteps += (deg / (stepAngle * microSteps));
    if (blocking == true)
    {
        while (demandSteps != currentSteps)
        {

            if (currentSteps < demandSteps)
            {
                endStopCollision = false;
                currentSteps += 1;
                digitalWrite(dirPinNumber, LOW);
                digitalWrite(stepPinNumber, HIGH);
                delayMicroseconds(20);
                digitalWrite(stepPinNumber, LOW);
                delayMicroseconds(delayTime);
            }
            if (currentSteps > demandSteps)
            {
                endStopCollision = false;
                currentSteps -= 1;
                digitalWrite(dirPinNumber, HIGH);
                digitalWrite(stepPinNumber, HIGH);
                delayMicroseconds(20);
                digitalWrite(stepPinNumber, LOW);
                delayMicroseconds(delayTime);
            }
            currentAngle = currentSteps * (stepAngle * microSteps);
            if (currentSteps == (endStop1 / (stepAngle * microSteps)) or currentSteps == (endStop2 / (stepAngle * microSteps)))
            {
                endStopCollision = true;
                if (debug)
                {
                    Serial.println("Collided with end stop!");
                }
                break;
            }
        }
    }
}

void EasyStepper::run()
{

    if (currentSteps < demandSteps)
    {
        endStopCollision = false;
        currentSteps += 1;
        digitalWrite(dirPinNumber, LOW);
        digitalWrite(stepPinNumber, HIGH);
        delayMicroseconds(20);
        digitalWrite(stepPinNumber, LOW);
        delayMicroseconds(delayTime);
    }
    if (currentSteps > demandSteps)
    {
        endStopCollision = false;
        currentSteps -= 1;
        digitalWrite(dirPinNumber, HIGH);
        digitalWrite(stepPinNumber, HIGH);
        delayMicroseconds(20);
        digitalWrite(stepPinNumber, LOW);
        delayMicroseconds(delayTime);
    }
    currentAngle = currentSteps * (stepAngle * microSteps);
    if (currentSteps == (endStop1 / (stepAngle * microSteps)) or currentSteps == (endStop2 / (stepAngle * microSteps)))
    {
        endStopCollision = true;
        if (debug)
        {
            Serial.println("Collided with end stop!");
        }
    }
}

void EasyStepper::zero() {
    currentSteps = 0;
}
