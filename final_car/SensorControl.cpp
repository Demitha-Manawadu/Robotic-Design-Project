#include "SensorControl.h"
#include <Arduino.h>

// Define sensor pins from A0 to A7
const int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
int sensorValues[NUM_SENSORS];
int calibratedMin[NUM_SENSORS];
int calibratedMax[NUM_SENSORS];

void initializeSensors() {
    // Initialize all sensors
    for (int i = 0; i < NUM_SENSORS; i++) {
        calibratedMin[i] = 1023;  // Set initial min value (maximum possible analog reading)
        calibratedMax[i] = 0;     // Set initial max value (minimum possible analog reading)
    }
    Serial.println("Sensors initialized.");
}

void calibrateSensors() {
    Serial.println("Calibrating sensors...");

    // Reset calibration values
    for (int i = 0; i < NUM_SENSORS; i++) {
        calibratedMin[i] = 1023;
        calibratedMax[i] = 0;
    }

    // Perform calibration
    for (int j = 0; j < 200; j++) {  // Collect calibration data over 200 iterations
        for (int i = 0; i < NUM_SENSORS; i++) {
            int sensorValue = analogRead(sensorPins[i]);
            calibratedMin[i] = min(calibratedMin[i], sensorValue);  // Update min value
            calibratedMax[i] = max(calibratedMax[i], sensorValue);  // Update max value
        }
        delay(20);  // Short delay between readings
    }

    Serial.println("Calibration complete.");
    Serial.println("Calibrated Min and Max values:");
    for (int i = 0; i < NUM_SENSORS; i++) {
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(": Min = ");
        Serial.print(calibratedMin[i]);
        Serial.print(", Max = ");
        Serial.println(calibratedMax[i]);
    }
}

void readSensors() {
    // Read and normalize sensor values to binary
    for (int i = 0; i < NUM_SENSORS; i++) {
        int sensorValue = analogRead(sensorPins[i]);
        int threshold = (calibratedMin[i] + calibratedMax[i]) / 2;  // Calculate dynamic threshold
        sensorValues[i] = (sensorValue > threshold) ? 0 : 1;        // Convert to binary output
    }

    // Debugging: Print sensor values
    Serial.print("Binary Sensor Values: ");
    for (int i = 0; i < NUM_SENSORS; i++) {
        Serial.print(sensorValues[i]);
        Serial.print(" ");
    }
    Serial.println();
}


