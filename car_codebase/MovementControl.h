#ifndef MOVEMENTCONTROL_H
#define MOVEMENTCONTROL_H

// Function to run forward for given encoder counts using PID
void runForwardWithEncoderPID(long targetCount);

// Function to run forward for given encoder counts without PID (fixed speed of 180)
void runForwardWithoutPID(long targetCount);

// Function to run backward for given encoder counts using PID
void runBackwardWithEncoderPID(long targetCount);

// Function to run backward for given encoder counts without PID (fixed speed of 180)
void runBackwardWithoutPID(long targetCount);

#endif
