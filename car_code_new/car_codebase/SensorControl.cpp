#include "SensorControl.h"
#include <Arduino.h>

#define NUM_SENSORS 8
const int sensorPins[NUM_SENSORS] = {A7, A6, A5, A4, A3, A2, A1, A0};
int sensorValues[NUM_SENSORS];
int calibratedMin[NUM_SENSORS];
int calibratedMax[NUM_SENSORS];

void setupSensors() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    calibratedMin[i] = 1023;
    calibratedMax[i] = 0;
  }
  calibrateSensors();
}

void calibrateSensors() {
  for (int j = 0; j < 200; j++) {
    for (int i = 0; i < NUM_SENSORS; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue < calibratedMin[i]) {
        calibratedMin[i] = sensorValue;
      }
      if (sensorValue > calibratedMax[i]) {
        calibratedMax[i] = sensorValue;
      }
    }
    delay(20);
  }
}

void readSensors() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    int sensorValue = analogRead(sensorPins[i]);
    int threshold = (calibratedMin[i] + calibratedMax[i]) / 2;
    sensorValues[i] = (sensorValue > threshold) ? 0 : 1;
  }
}

int calculatePosition() {
  long int weightedSum = 0;
  long int sum = 0;

  for (int i = 0; i < NUM_SENSORS; i++) {
    weightedSum += (long int)sensorValues[i] * (i * 1000);
    sum += sensorValues[i];
  }

  return sum > 0 ? weightedSum / sum : 3500;
}
