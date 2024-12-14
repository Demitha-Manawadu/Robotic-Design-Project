#include "RobotControl.h"
#include "MotorControl.h"

// Example calibration constants for the Sharp IR sensor
// Adjust these based on your sensor's calibration
static const float a = 27.86;
static const float b = 0.42;

void startRobot() {
  moveForward(200,200);

    // In actual implementation, you would start the motors here
    Serial.println("Action: Robot Moving Forward");
}

void stopRobot() {
    stopMotors();
    // In actual implementation, you would stop the motors here
    Serial.println("Action: Robot Stopped");
}

int getSharpIRDistance() {
    int sensorValue = analogRead(SHARP_IR_PIN);
    return (int)sensorValue;
}

void checkBarrier() {

        int distance = getSharpIRDistance();
        
        // If robot is moving and barrier is close, stop
        if (distance > STOP_DISTANCE) {
            stopRobot();
            Serial.println("Barrier Detected! Stopped.");
        } 
        // If robot is stopped and barrier no longer close, start
        else if (distance < STOP_DISTANCE) {
            startRobot();
            Serial.println("Barrier Cleared! Moving again.");
        }
    }