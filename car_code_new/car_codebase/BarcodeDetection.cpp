#include "BarcodeDetection.h"
#include "AdvancedMotorControl.h"
#include "MotorControl.h"
#include <Arduino.h>

BarcodeDetection::BarcodeDetection(int threshold, int maxLines, int targetSpeed)
    : threshold(threshold), maxLines(maxLines), targetSpeed(targetSpeed), detectedLines(0), timeString("") {}

void BarcodeDetection::init() {
    display.init();  // Initialize OLED display
}

void BarcodeDetection::update() {
    if (detectedLines < maxLines) {
        runForwardWithEncoderPID(targetSpeed);  // Pass targetSpeed correctly
        detectBarcodeLine();                     // Detect lines and record times
    } else {
        moveForward(0, 0);                       // Stop motors if maxLines detected
    }
}

bool BarcodeDetection::isCompleted() {
    return detectedLines >= maxLines;  // Check if detection is complete
}

void BarcodeDetection::detectBarcodeLine() {
    int sensorValue = analogRead(A3);  // Read sensor data (example: A0 pin)

    // If the sensor value exceeds the threshold, a line is detected
    if (sensorValue > threshold) {
        unsigned long detectionTime = millis();  // Get the current time
        timeString += String(detectionTime) + ",";  // Add time to string with commas
        detectedLines++;  // Increment detected lines

        displayTimeData();  // Update OLED display with current time data

        // Stop if the max lines have been detected
        if (detectedLines >= maxLines) {
            moveForward(0, 0);  // Stop motors
        }
    }
}

void BarcodeDetection::displayTimeData() {
    display.clear();  // Clear the display before showing new data
    display.printMessage("Detection Times:");  // Show label
    display.printMessage(timeString);  // Show times on OLED
}

void BarcodeDetection::runForwardWithEncoderPID(int speed) {
    // Call the appropriate function to move forward at a constant speed
    ::runForwardWithEncoderPID(speed);  // Using scope resolution operator to call the global function
}
