#include "ColorSensor.h"

// Define pin configurations based on your provided setup
const int middleS0 = 24;
const int middleS1 = 25;
const int middleS2 = 26;
const int middleS3 = 27;
const int middleOutPin = 28;

const int leftS0 = 34;
const int leftS1 = 35;
const int leftS2 = 36;
const int leftS3 = 37;
const int leftOutPin = 38;

const int rightS0 = 29;
const int rightS1 = 28;
const int rightS2 = 31;
const int rightS3 = 30;
const int rightOutPin = 33;

ColorSensorHandler::ColorSensorHandler() {
  // Initialize the sensors with the pins defined above
  _middle = {middleS0, middleS1, middleS2, middleS3, middleOutPin};
  _left = {leftS0, leftS1, leftS2, leftS3, leftOutPin};
  _right = {rightS0, rightS1, rightS2, rightS3, rightOutPin};
}

void ColorSensorHandler::setupSensors() {
  pinMode(_middle.s0, OUTPUT);
  pinMode(_middle.s1, OUTPUT);
  pinMode(_middle.s2, OUTPUT);
  pinMode(_middle.s3, OUTPUT);
  pinMode(_middle.outPin, INPUT);

  pinMode(_left.s0, OUTPUT);
  pinMode(_left.s1, OUTPUT);
  pinMode(_left.s2, OUTPUT);
  pinMode(_left.s3, OUTPUT);
  pinMode(_left.outPin, INPUT);

  pinMode(_right.s0, OUTPUT);
  pinMode(_right.s1, OUTPUT);
  pinMode(_right.s2, OUTPUT);
  pinMode(_right.s3, OUTPUT);
  pinMode(_right.outPin, INPUT);
}

void ColorSensorHandler::setFilter(ColorSensor sensor, int s2State, int s3State) {
  digitalWrite(sensor.s2, s2State);
  digitalWrite(sensor.s3, s3State);
}

int ColorSensorHandler::readFrequency(ColorSensor sensor) {
  return pulseIn(sensor.outPin, LOW);
}

void ColorSensorHandler::readRGBValues(ColorSensor sensor, int &red, int &green, int &blue) {
  // Read Red value
  setFilter(sensor, LOW, LOW);
  red = readFrequency(sensor);

  // Read Green value
  setFilter(sensor, HIGH, HIGH);
  green = readFrequency(sensor);

  // Read Blue value
  setFilter(sensor, LOW, HIGH);
  blue = readFrequency(sensor);
}

void ColorSensorHandler::printAllSensorRGBValues() {
  int middleRed, middleGreen, middleBlue;
  int leftRed, leftGreen, leftBlue;
  int rightRed, rightGreen, rightBlue;

  // Read RGB values for each sensor
  readRGBValues(_middle, middleRed, middleGreen, middleBlue);
  readRGBValues(_left, leftRed, leftGreen, leftBlue);
  readRGBValues(_right, rightRed, rightGreen, rightBlue);

  // Print raw RGB values for each sensor
  Serial.print("Middle Sensor - R: ");
  Serial.print(middleRed);
  Serial.print(" G: ");
  Serial.print(middleGreen);
  Serial.print(" B: ");
  Serial.println(middleBlue);

  Serial.print("Left Sensor - R: ");
  Serial.print(leftRed);
  Serial.print(" G: ");
  Serial.print(leftGreen);
  Serial.print(" B: ");
  Serial.println(leftBlue);

  Serial.print("Right Sensor - R: ");
  Serial.print(rightRed);
  Serial.print(" G: ");
  Serial.print(rightGreen);
  Serial.print(" B: ");
  Serial.println(rightBlue);
}

String ColorSensorHandler::detectColor(int red, int green, int blue) {
  if (red >= RED_MIN && red <= RED_MAX) {
    return "Red";
  } else if (blue >= BLUE_MIN && blue <= BLUE_MAX) {
    return "Blue";
  } else if (green >= GREEN_MIN && green <= GREEN_MAX) {
    return "Green";
  } else {
    return "Unknown";
  }
}
