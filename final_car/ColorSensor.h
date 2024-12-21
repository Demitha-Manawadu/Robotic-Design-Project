#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Arduino.h>

class ColorSensor {
public:
    static const int S0 = 23;
    static const int S1 = 24;
    static const int S2 = 25;
    static const int S3 = 26;
    static const int OUT = 27;
    static const int redLED = 41;  // Pin for red LED
    static const int blueLED = 49; // Pin for blue LED
    bool bluee; // Tracks if a color is detected (default true)

    ColorSensor();
    void initialize();
    void detectColor();
};

#endif