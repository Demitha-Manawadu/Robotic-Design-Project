#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#include "MotorControl.h"
// Motor control setup functions
void setupMotors();
void setupEncoders();
extern volatile long leftEncoderCount;
extern volatile long rightEncoderCount;
// Motor movement functions
void moveForward(int leftSpeed, int rightSpeed);
void moveBackward(int leftSpeed, int rightSpeed);
void stopMotors();

// Function to turn based on angle using PID control
void turnByAngleWithPID(int angle);  // Turns based on positive or negative angle
void displayEncoderCounts();
void resetEncoders();
// Encoder functions
void runBackwardWithoutPID(long targetCount);
void runForwardWithoutPID(long targetCount);
void leftEncoderISR();
void rightEncoderISR();
void readEncoders();
void corrector();
#endif
