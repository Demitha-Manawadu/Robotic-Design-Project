#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Arduino.h>

// Pin configuration for the sensors
struct ColorSensor {
  int s0, s1, s2, s3, outPin;
};

class ColorSensorHandler {
public:
  ColorSensorHandler();
  void setupSensors();
  void readRGBValues(ColorSensor sensor, int &red, int &green, int &blue);
  void printAllSensorRGBValues();
  String detectColor(int red, int green, int blue);

private:
  ColorSensor _middle;
  ColorSensor _left;
  ColorSensor _right;

  int readFrequency(ColorSensor sensor);
  void setFilter(ColorSensor sensor, int s2State, int s3State);
};

// Basic color thresholds (adjust these based on your calibration)
const int RED_MIN = 30;
const int RED_MAX = 100;
const int BLUE_MIN = 200;
const int BLUE_MAX = 300;
const int GREEN_MIN = 100;
const int GREEN_MAX = 250;

#endif
