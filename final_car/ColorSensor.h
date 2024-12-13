#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Arduino.h>

class ColorSensor {
public:
    // Constructor to initialize threshold values (optional)
    ColorSensor(int redMin = 20, int redMax = 80, int blueMin = 30, int blueMax = 70);

    // Initialization function to set up pins and settings
    void initialize();

    // Function to detect color and light up corresponding LED
    void detectColor();

private:
    // Pin definitions
    const int S0 = 24, S1 = 25, S2 = 26, S3 = 27, OE = 29, OUT = 28;
    const int redLED = 51, blueLED = 53;

    // Threshold values for color detection
    int redMinThreshold, redMaxThreshold;
    int blueMinThreshold, blueMaxThreshold;
};

#endif
