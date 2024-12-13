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
const int leftEncoderB = 18;
const int leftEncoderA = 19;
const int rightEncoderB = 3;
const int rightEncoderA = 2;

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
  delay(10);
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
void turnByAngleWithPID(int angle) {
  // Convert the angle into target encoder counts
  long encoderTarget = abs(angle) * 11.7;
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
    leftSpeed = constrain(leftSpeed, 150, 250);
    rightSpeed = constrain(rightSpeed, 150, 250);

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
    stopMotors();
}
void runBackwardWithoutPID(long targetCount) {
    leftEncoderCount = 0;
    rightEncoderCount = 0;

    // Keep moving forward until the encoder counts reach the target
    while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
        moveBackward(150, 150);  // Move both motors at a fixed speed
    }
    // Stop the motors after reaching the target count
    stopMotors();
}

void runForwardWithoutPID_1(long targetCount) {
    leftEncoderCount = 0;
    rightEncoderCount = 0;

    // Keep moving forward until the encoder counts reach the target
    while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
        runForwardWithSensorPIDw();  // Move both motors at a fixed speed
    }
}
    // Stop the motors after reaching the target count
   