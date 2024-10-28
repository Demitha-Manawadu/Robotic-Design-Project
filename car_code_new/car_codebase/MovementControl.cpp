#include "MovementControl.h"
#include "MotorControl.h"
#include "AdvancedMotorControl.h"  // Include to access predefined PID functions
#include <Arduino.h>

// Function to run forward for a given encoder count using PID


// Function to run forward for a given encoder count without PID (fixed speed of 180)
void runForwardWithoutPID(long targetCount) {
    leftEncoderCount = 0;
    rightEncoderCount = 0;

    // Keep moving forward until the encoder counts reach the target
    while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
        moveForward(180, 180);  // Move both motors at a fixed speed
    }

    // Stop the motors after reaching the target count
    moveForward(0, 0);
}

// Function to run backward for a given encoder count using PID


// Function to run backward for a given encoder count without PID (fixed speed of 180)
void runBackwardWithoutPID(long targetCount) {
    leftEncoderCount = 0;
    rightEncoderCount = 0;

    // Keep moving backward until the encoder counts reach the target
    while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
        moveBackward(180, 180);  // Move both motors at a fixed speed
    }

    // Stop the motors after reaching the target count
    moveBackward(0, 0);
}
