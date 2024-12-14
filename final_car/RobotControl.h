#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H

#include <Arduino.h>

// Adjust these pins and constants as needed
const int SHARP_IR_PIN = A15;     // Sharp IR Sensor pin
const int STOP_DISTANCE = 50;    // Distance threshold for stopping (in cm)

// Interval for sensor reading in ms
const long INTERVAL = 200;

// Declare functions
void startRobot();
void stopRobot();
int getSharpIRDistance();
void checkBarrier();

#endif