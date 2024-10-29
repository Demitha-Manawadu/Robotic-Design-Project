#ifndef LINEFOLLOWANDTURN_H
#define LINEFOLLOWANDTURN_H
#include "ColorSensor.h"
#include <Arduino.h>
#include "SensorControl.h"
// Define the number of sensors and the sensor array
#define NUM_SENSORS 8
extern int sensorValues[NUM_SENSORS];

// Function declarations
void followLineAndTurnWithSquareDetection();  // Your existing function for line-following with PID
void turnByAngleWithPID(int angle);  // Your existing function for turning with PID
void followLineAndTurn();  // Function to follow the line and turn when needed
void moveForward(int leftSpeed, int rightSpeed);
void readSensors();
void corrector();
#endif
