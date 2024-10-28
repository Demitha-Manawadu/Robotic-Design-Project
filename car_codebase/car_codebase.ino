#include "MotorControl.h"
#include "SensorControl.h"
#include "AdvancedMotorControl.h"
#include "MovementControl.h"
#include "OLED_Display.h"
#include "SensorMotorControl.h"

OLEDDisplay oled;

void setup() {
  oled.init();
  //oled.printMessage("Hello, World!");
  setupMotors();
  setupSensors();
  setupEncoders();
  Serial.begin(9600);
}

void loop() {
   // handleBlackDetectionAndDisplay();
  turnByAngleWithPID(90);
  delay(1000);
  // Example: running the task for box position 0

}