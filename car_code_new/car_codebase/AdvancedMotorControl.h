#ifndef ADVANCEDMOTORCONTROL_H
#define ADVANCEDMOTORCONTROL_H
#include "task2.h"

extern volatile long leftEncoderCount;
extern volatile long rightEncoderCount;
// Declaration of functions
void runForwardWithSensorPID();  // Function to run forward using PID of the sensor array
void runBackwardWithEncoderPID();  // Function to run backward using PID of the encoders
void runForwardWithEncoderPID(int targetSpeed);;

#endif
