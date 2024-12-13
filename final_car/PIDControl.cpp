#include "PIDControl.h"
#include "SensorControl.h"
#include "MotorControl.h"

// PID constants
float Kp = .6;  // Proportional constant
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

    int position = (sum != 0) ? (weightedSum / sum) : 0;  // Avoid division by zero

    // Calculate the error (assuming center line is at position 0)
    int error = position;

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
void runForwardWithSensorPIDw(){
    long int weightedSum = 0;
    int sum = 0;
    readSensorsw() ;
    // Define exponential weights for 12 sensors
    const int weights[NUM_SENSORS] = {-2048, -1024, -512, -256, -128, -64, 64, 128, 256, 512, 1024, 2048};

    // Calculate the position value using exponential weights
    for (int i = 0; i < NUM_SENSORS; i++) {
        weightedSum += sensorValues[i] * weights[i];
        sum += sensorValues[i];
    }

    int position = (sum != 0) ? (weightedSum / sum) : 0;  // Avoid division by zero

    // Calculate the error (assuming center line is at position 0)
    int error = position;

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
// PID constants for backward motion
float backwardKp = 1;  // Proportional gain
float backwardKi = 0.00;  // Integral gain
float backwardKd = 1.5;  // Derivative gain
float backwardLastError = 0;
float backwardIntegral = 0;

void runBackwardWithEncoderPID() {
    Serial.println("Running Backward with Encoder and Sensor Feedback PID...");

    // Calculate the error using encoder counts
    long encoderError = leftEncoderCount - rightEncoderCount;

    // Sensor-based correction using weighted sensor array
    int sensorWeightedSum = 0;
    int activeSensors = 0;
    readSensors() ;
    // Define weights for 12 sensors
    const int weights[NUM_SENSORS] = {256, 512, -512, -256, -128, -64, 64, 128, 256, 512, -512,-256 };

    // Calculate position error from the sensor array
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] == 1) {  // Line detected
            sensorWeightedSum += weights[i];
            activeSensors++;
        }
    }

    // Determine the sensor-based error
    int sensorError = (activeSensors > 0) ? (sensorWeightedSum / activeSensors) : 0;

    // Combine encoder and sensor error for correction
    long combinedError = encoderError + sensorError * 2;  // Weight sensor error relative to encoder error

    // Compute PID control values
    backwardIntegral += combinedError;
    float derivative = combinedError - backwardLastError;
    float output = backwardKp * combinedError + backwardKi * backwardIntegral + backwardKd * derivative;
    backwardLastError = combinedError;

    // Adjust motor speeds based on combined PID output
    int baseSpeed = 150;
    int leftSpeed = baseSpeed - output;
    int rightSpeed = baseSpeed + output;

    // Constrain motor speeds to valid ranges
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    // Move the robot backward
    moveBackward(leftSpeed, rightSpeed);

    // Debugging: Print encoder and sensor error
    Serial.print("Encoder Error: ");
    Serial.println(encoderError);
    Serial.print("Sensor Error: ");
    Serial.println(sensorError);
    Serial.print("Left Speed: ");
    Serial.print(leftSpeed);
    Serial.print(" Right Speed: ");
    Serial.println(rightSpeed);

    delay(10);  // Small delay for stability
}
void runForwardWithSensorPIDr(){
    long int weightedSum = 0;
    int sum = 0;
    readSensorsw() ;
    // Define exponential weights for 12 sensors
    const int weights[NUM_SENSORS] = {-2048, -1024, -512, -256, -128, -64, 64, 128, 256, 512, 1024, 2048};

    // Calculate the position value using exponential weights
    for (int i = 3; i < NUM_SENSORS-3; i++) {
        weightedSum += sensorValues[i] * weights[i];
        sum += sensorValues[i];
    }

    int position = (sum != 0) ? (weightedSum / sum) : 0;  // Avoid division by zero

    // Calculate the error (assuming center line is at position 0)
    int error = position;

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