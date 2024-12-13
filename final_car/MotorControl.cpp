#include "MotorControl.h"
#include <Arduino.h>
#include "OLED_Display.h"
#include "PIDControl.h"

const int leftMotorForward = 48;
const int leftMotorBackward = 50;
const int rightMotorForward = 46;
const int rightMotorBackward = 44;

const int enaPin = 8;
const int enbPin = 9;

// Encoder pins
const int leftEncoderA = 19;
const int leftEncoderB = 18;
const int rightEncoderA = 2;
const int rightEncoderB = 3;

// Encoder counts
volatile long leftEncoderCount = 0;
volatile long rightEncoderCount = 0;

// // Constants to map degrees to encoder counts
// const float ENCODER_COUNTS_PER_DEGREE = 11.99;  // Adjust this value based on your setup

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
void resetEncoders(){
  rightEncoderCount=0;
  leftEncoderCount=0;
} 
// Stop all motors
void stopMotors() {
  analogWrite(enbPin, 0);
  analogWrite(enaPin, 0);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
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
void turnByAngleWithPID(float targetAngle) {
  // Reset encoders
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // PID control variables
  turnIntegral = 0;
  turnLastError = 0;

  // Calculate the target encoder counts for the given angle
  long targetCounts = targetAngle * 12;

  while (true) {
    // Calculate the current position
    long averageCounts = (abs(leftEncoderCount) + abs(rightEncoderCount)) / 2;

    // Calculate the error (remaining counts to target)
    long error = targetCounts - averageCounts;

    // Break when the target is achieved (allowable error threshold)
    if (abs(error) < 10) {  // 10 counts tolerance
      break;
    }

    // Compute PID values
    turnIntegral += error;
    long derivative = error - turnLastError;
    float output = turnKp * error + turnKi * turnIntegral + turnKd * derivative;
    turnLastError = error;

    // Constrain the PID output to valid speed range
    int turnSpeed = constrain(abs(output), 50, 255);

    // Determine direction of rotation
    if (error > 0) {
      // Clockwise rotation
      analogWrite(enbPin, turnSpeed);  // Set left motor speed
      analogWrite(enaPin, turnSpeed); // Set right motor speed
      digitalWrite(leftMotorForward, HIGH);
      digitalWrite(leftMotorBackward, LOW);
      digitalWrite(rightMotorForward, LOW);
      digitalWrite(rightMotorBackward, HIGH);
    } else {
      // Counterclockwise rotation
      analogWrite(enbPin, turnSpeed);  // Set left motor speed
      analogWrite(enaPin, turnSpeed); // Set right motor speed
      digitalWrite(leftMotorForward, LOW);
      digitalWrite(leftMotorBackward, HIGH);
      digitalWrite(rightMotorForward, HIGH);
      digitalWrite(rightMotorBackward, LOW);
      
    }
  }

  // Stop the motors after turning
  stopMotors();
}

void corrector() {
  unsigned long startTime = millis();
  while (millis() - startTime < 500) {  // Run for approximately 1 second
    runForwardWithSensorPID();
  }
}
void runForwardWithoutPID(long targetCount) {
    leftEncoderCount = 0;
    rightEncoderCount = 0;

    // Keep moving forward until the encoder counts reach the target
    while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
        moveForward(120, 120);  // Move both motors at a fixed speed
    }
    // Stop the motors after reaching the target count
    moveForward(0, 0);
}
