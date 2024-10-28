#include "AdvancedMotorControl.h"
#include "MotorControl.h"
#include "SensorControl.h"
#include <Arduino.h>
#include "OLED_Display.h"

// PID control variables for forward motion
float forwardKp = 1.0;  // Proportional gain try using 3500/180
float forwardKi = 0.0;  // Integral gain
float forwardKd = 0.7;  // Derivative gain
float forwardLastError = 0;
float forwardIntegral = 0;

// PID control variables for backward motion
float backwardKp = 1.2;  // Proportional gain
float backwardKi = 0.00;  // Integral gain
float backwardKd = 0.6;  // Derivative gain
float backwardLastError = 0;
float backwardIntegral = 0;

// Function to run forward using PID of the sensor array (without time constraint)
void runForwardWithSensorPID() {
  Serial.println("Running Forward with Sensor Array PID...");

  while (true) {  // Infinite loop to keep running until some external condition breaks the loop
    // Read and normalize sensor values
    readSensors();

    // Calculate the position value using a weighted sum
    int position = calculatePosition();

    // Compute the error
    int error = position - 3500;  // Assume line center at 3500
    Serial.println(error);

    // Compute the PID control values
    forwardIntegral += error;
    float derivative = error - forwardLastError;
    float output = forwardKp * error + forwardKi * forwardIntegral + forwardKd * derivative;
    forwardLastError = error;

    // Adjust the motor speeds based on the PID output
    int baseSpeed = 180;
    int leftSpeed = baseSpeed + output;
    int rightSpeed = baseSpeed - output;

    // Ensure motor speeds are within a valid range
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    // Move the car forward with the calculated speeds
    moveForward(leftSpeed, rightSpeed);

    // You can add a break condition here if needed
    // Example: if (someConditionMet) { break; }
  }

  // Stop the motors after forward motion
  moveForward(0, 0);
}

// Function to run backward using PID of the encoders (without time constraint)
void runBackwardWithEncoderPID() {
  // Reset encoder counts before moving backward
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  Serial.println("Running Backward with Encoder PID...");

  while (true) {  // Infinite loop to keep running until some external condition breaks the loop
    // Calculate the error using encoder counts
    long error = leftEncoderCount - rightEncoderCount;

    // Compute the PID control values
    backwardIntegral += error;
    float derivative = error - backwardLastError;
    float output = backwardKp * error + backwardKi * backwardIntegral + backwardKd * derivative;
    backwardLastError = error;

    // Adjust the motor speeds based on the PID output
    int baseSpeed = 180;
    int leftSpeed = baseSpeed - output;
    int rightSpeed = baseSpeed + output;

    // Ensure motor speeds are within a valid range
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    // Move the car backward with the calculated speeds
    moveBackward(leftSpeed, rightSpeed);

    // You can add a break condition here if needed
    // Example: if (someConditionMet) { break; }
  }

  // Stop the motors after backward motion
  moveBackward(0, 0);
}
