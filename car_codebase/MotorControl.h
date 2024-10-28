#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// Motor control setup functions
void setupMotors();
void setupEncoders();

// Motor movement functions
void moveForward(int leftSpeed, int rightSpeed);
void moveBackward(int leftSpeed, int rightSpeed);
void stopMotors();

// Function to turn based on angle using PID control
void turnByAngleWithPID(int angle);  // Turns based on positive or negative angle

// Encoder functions
void leftEncoderISR();
void rightEncoderISR();
void readEncoders();

#endif
