#include "ColorSensor.h"

const int redThreshold = 300;
const int blueThreshold = 200;
bool bluee = false;
ColorSensor::ColorSensor() : bluee(true) {}

void ColorSensor::initialize() {
    // Set pin modes
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);
    pinMode(redLED, OUTPUT);
    pinMode(blueLED, OUTPUT);

    // Set frequency scaling to 20%
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

    bluee = true; // Default state

    // Determine color and control LEDs
    if (redFrequency < redThreshold && blueFrequency > blueThreshold) {
        digitalWrite(redLED, HIGH);
        digitalWrite(blueLED, LOW);
        bluee = false;
    } else if (blueFrequency < blueThreshold && redFrequency > redThreshold) {
        digitalWrite(blueLED, HIGH);
        digitalWrite(redLED, LOW);
        bluee = false;
    } else {
        digitalWrite(redLED, LOW);
        digitalWrite(blueLED, LOW);
    }
}