#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <Arduino.h>

// PID parameters
extern int sensorValues[12];
// Function prototypes
void runForwardWithSensorPID();
void runBackwardWithEncoderPID();
#endif
