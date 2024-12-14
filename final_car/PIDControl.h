#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <Arduino.h>

// PID parameters
extern int sensorValues[12];
extern int sensor2Values[8];
// Function prototypes
void moveForwardUntilWhiteSquare();
void runForwardWithSensorPIDw();
void runForwardWithSensorPIDr();
void runForwardWithSensorPID();
void runBackwardWithEncoderPID();
#endif
