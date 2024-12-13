#include "PIDControl.h"
#include "SensorControl.h"
#include "MotorControl.h"

// PID constants
float Kp = .2;  // Proportional constant
float Ki = 0.0;  // Integral constant
float Kd = 1.0;  // Derivative constant

// PID variables
float integral = 0;
float lastError = 0;

void runForwardWithSensorPID(){
    long int weightedSum = 0;
    int sum = 0;
    readSensors() ;
    // Define exponential weights for 12 sensors
    const int weights[NUM_SENSORS] = {-2048, -1024, -512, -256, -128, -64, 64, 128, 256, 512, 1024, 2048};

    // Calculate the position value using exponential weights
    for (int i = 0; i < NUM_SENSORS; i++) {
        weightedSum += sensorValues[i] * weights[i];
        sum += sensorValues[i];
    }

    //int position = (sum != 0) ? (weightedSum / sum) : 0;  // Avoid division by zero

    // Calculate the error (assuming center line is at position 0)
    int error = weightedSum;

    // Compute PID values
    integral += error;
    float derivative = error - lastError;
    float output = Kp * error + Ki * integral + Kd * derivative;
    lastError = error;

    // Adjust motor speeds based on PID output
    int baseSpeed = 150;
    int leftSpeed = baseSpeed - output;
    int rightSpeed = baseSpeed + output;

    // Constrain motor speeds
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    // Command the motors
    moveForward(leftSpeed, rightSpeed);
    delay(10);
}
