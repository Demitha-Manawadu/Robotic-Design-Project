#include "PIDControl.h"
#include "SensorControl.h"
#include "MotorControl.h"

// PID constants
float Kp = .8;  // Proportional constant
float Ki = 0.0;  // Integral constant
float Kd = 1.5;  // Derivative constant
float Kp2 = 1;  // Proportional constant
float Ki2 = 0.0;  // Integral constant
float Kd2 = 1.0;  // Derivative constant

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
void runBackwardWithEncoderPID() {
    long int weightedSum = 0;
    int sum = 0;
    digitalread() ;
    // Define exponential weights for 12 sensors
    const int weights2[NUM_SENSORS] = {-512, -256, -128, -64, 64, 128, 256, 512};

    // Calculate the position value using exponential weights
    for (int i = 0; i < NUM_SENSORS; i++) {
        weightedSum += (1-sensor2Values[i]) * weights2[i];
        sum += 1-sensor2Values[i];
    }

    int position = (sum != 0) ? (weightedSum / sum) : 0;  // Avoid division by zero

    // Calculate the error (assuming center line is at position 0)
    int error = position;

    // Compute PID values
    integral += error;
    float derivative = error - lastError;
    float output = Kp2 * error + Ki2 * integral + Kd2 * derivative;
    lastError = error;

    // Adjust motor speeds based on PID output
    int baseSpeed = 150;
    int leftSpeed = baseSpeed - output;
    int rightSpeed = baseSpeed + output;

    // Constrain motor speeds
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    // Command the motors
    moveBackward(leftSpeed, rightSpeed);
    delay(10);
}
bool isWhiteSquareDetected() {
  readSensors();
    // Assuming a 12-sensor array where all sensors return 1 when detecting white
    for (int i = 0; i < 12; i++) {
        if (sensorValues[i] != 1) {
            return false; // If any sensor does not detect white, return false
        }
    }
    return true; // All sensors detect white
}
void moveForwardUntilWhiteSquare() {
    while (!isWhiteSquareDetected()) {
       runForwardWithSensorPID();
    }
    stopMotors(); // Ensure the robot stops once the white square is detected
}