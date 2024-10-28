#include "MotorControl.h"
#include <Arduino.h>
const int leftMotorForward = 48;
const int leftMotorBackward = 50;
const int rightMotorForward = 44;
const int rightMotorBackward = 46;

const int enaPin = 8;
const int enbPin = 9;

// Encoder pins
const int leftEncoderA = 18;
const int leftEncoderB = 19;
const int rightEncoderA = 3;
const int rightEncoderB = 2;

// Encoder counts
volatile long leftEncoderCount = 0;
volatile long rightEncoderCount = 0;

// Constants to map degrees to encoder counts
const float ENCODER_COUNTS_PER_DEGREE = 11.89;  // Adjust this value based on your setup

// PID control variables for turning
float turnKp = 1.0;  // Proportional gain for turning
float turnKi = 0.0;  // Integral gain for turning
float turnKd = 0.5;  // Derivative gain for turning
float turnLastError = 0;
float turnIntegral = 0;

void setupMotors() {
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(enaPin, OUTPUT);
  pinMode(enbPin, OUTPUT);
}

void setupEncoders() {
  pinMode(leftEncoderA, INPUT);
  pinMode(leftEncoderB, INPUT);
  pinMode(rightEncoderA, INPUT);
  pinMode(rightEncoderB, INPUT);

  // Attach interrupts to encoder pins
  attachInterrupt(digitalPinToInterrupt(leftEncoderA), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderA), rightEncoderISR, CHANGE);
}

void leftEncoderISR() {
  if (digitalRead(leftEncoderA) == digitalRead(leftEncoderB)) {
    leftEncoderCount++;
  } else {
    leftEncoderCount--;
  }
}

void rightEncoderISR() {
  if (digitalRead(rightEncoderA) == digitalRead(rightEncoderB)) {
    rightEncoderCount++;
  } else {
    rightEncoderCount--;
  }
}

// Stop all motors
void stopMotors() {
  analogWrite(enbPin, 0);
  analogWrite(enaPin, 0);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

// Function to turn by a given angle (positive for right, negative for left) using PID control
void turnByAngleWithPID(int angle) {
  // Convert the angle into target encoder counts
  long encoderTarget = abs(angle) * ENCODER_COUNTS_PER_DEGREE;
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // PID control loop
  while (abs(leftEncoderCount) < encoderTarget && abs(rightEncoderCount) < encoderTarget) {
    long error = abs(leftEncoderCount) - abs(rightEncoderCount);

    // PID calculation
    turnIntegral += error;
    float derivative = error - turnLastError;
    float output = turnKp * error + turnKi * turnIntegral + turnKd * derivative;
    turnLastError = error;

    // Adjust motor speeds based on PID output
    int baseSpeed = 180;  // You can adjust this base speed as needed
    int leftSpeed = baseSpeed + output;
    int rightSpeed = baseSpeed - output;

    // Ensure motor speeds are within valid range
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    if (angle > 0) {
      // Turn right: left motor moves forward, right motor moves backward
      analogWrite(enbPin, leftSpeed);
      analogWrite(enaPin, rightSpeed);
      digitalWrite(leftMotorForward, HIGH);
      digitalWrite(leftMotorBackward, LOW);
      digitalWrite(rightMotorForward, LOW);
      digitalWrite(rightMotorBackward, HIGH);
    } else {
      // Turn left: left motor moves backward, right motor moves forward
      analogWrite(enbPin, leftSpeed);
      analogWrite(enaPin, rightSpeed);
      digitalWrite(leftMotorForward, LOW);
      digitalWrite(leftMotorBackward, HIGH);
      digitalWrite(rightMotorForward, HIGH);
      digitalWrite(rightMotorBackward, LOW);
    }
  }

  // Stop motors after reaching the target
  stopMotors();
}
void moveForward(int leftSpeed, int rightSpeed) {
  analogWrite(enbPin, leftSpeed);  // Set speed for left motor
  analogWrite(enaPin, rightSpeed); // Set speed for right motor
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}

// Move backward with specific speeds for left and right motors
void moveBackward(int leftSpeed, int rightSpeed) {
  analogWrite(enbPin, leftSpeed);  // Set speed for left motor
  analogWrite(enaPin, rightSpeed); // Set speed for right motor
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

