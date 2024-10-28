#ifndef BARCODE_DETECTION_H
#define BARCODE_DETECTION_H

#include <Arduino.h>  // Include for using Arduino String class
#include "OLED_Display.h"  // Include OLED display class

class BarcodeDetection {
public:
    BarcodeDetection(int threshold, int maxLines, int targetSpeed);  // Constructor
    void init();                 // Initialize the sensors/motors
    void update();               // Main logic to detect barcodes
    bool isCompleted();          // Check if barcode detection is complete
    String getTimeString();      // Retrieve the detection times as a comma-separated string
    int getDetectedLines();      // Get the number of detected lines

private:
    int threshold;               // Threshold for detecting white lines
    int maxLines;                // Number of lines to detect before stopping
    int targetSpeed;             // Desired target speed for forward motion
    unsigned long detectionTime; // Time for detecting white/black
    String timeString;           // String to store detection times (comma-separated)
    int detectedLines;           // Count of detected lines
    unsigned long startTime;     // Time when detection started
    OLEDDisplay display;          // OLED display object
    void detectBarcodeLine();     // Function to detect a barcode line
    void displayTimeData();       // Function to display time data on OLED
    void runForwardWithEncoderPID(int speed);  // Correct declaration for the function
};

#endif
