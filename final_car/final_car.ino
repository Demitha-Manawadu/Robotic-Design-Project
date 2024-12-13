#include <Arduino.h>
#include "PIDControl.h"
#include "SensorControl.h"
#include "MotorControl.h"
void setup() {
  Serial.begin(9600);
  initializeSensors();
  calibrateSensors();
 setupEncoders();
  setupMotors();
  // put your setup code here, to run once:

}

void loop() {
  runForwardWithSensorPID() ;
  // put your main code here, to run repeatedly:

}
