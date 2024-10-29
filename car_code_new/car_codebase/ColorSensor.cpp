#include "ColorSensor.h"

ColorSensor::ColorSensor(int redMin, int redMax, int blueMin, int blueMax)
    : redMinThreshold(redMin), redMaxThreshold(redMax), blueMinThreshold(blueMin), blueMaxThreshold(blueMax) {}

void ColorSensor::initialize() {
    // Set pin modes
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OE, OUTPUT);
    pinMode(OUT, INPUT);  // OUT is an input to Arduino
    pinMode(redLED, OUTPUT);
    pinMode(blueLED, OUTPUT);

    // Enable output from sensor
    digitalWrite(OE, LOW);

    // Set frequency scaling to 20% for stable readings
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
}

void ColorSensor::detectColor() {
    // Detect red frequency
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    delay(100);
    int redFrequency = pulseIn(OUT, LOW);

    // Detect blue frequency
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    delay(100);
    int blueFrequency = pulseIn(OUT, LOW);

    // Determine color based on thresholds and light corresponding LED
    if (redFrequency >= redMinThreshold && redFrequency <= redMaxThreshold) {
        // Light up red LED for red color
        digitalWrite(redLED, HIGH);
        digitalWrite(blueLED, LOW);
    } else if (blueFrequency >= blueMinThreshold && blueFrequency <= blueMaxThreshold) {
        // Light up blue LED for blue color
        digitalWrite(blueLED, HIGH);
        digitalWrite(redLED, LOW);
    } else {
        // Turn off both LEDs if no target color detected
        digitalWrite(redLED, LOW);
        digitalWrite(blueLED, LOW);
    }
}
