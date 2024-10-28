#include "MotorControl.h"
#include "SensorControl.h"
#include "AdvancedMotorControl.h"
#include "MovementControl.h"
#include "OLED_Display.h"
#include "BarcodeDetection.h"
#include "Buzzer.h"
#include "ColorSensor.h"


Buzzer buzzer;  // Initialize the Buzzer object


const int threshold = 500;  // Set your desired threshold for line detection
const int maxLines = 3;      // Max lines to detect before stopping
const int targetSpeed = 180; // Desired speed for moving forward


ColorSensorHandler colorHandler;
BarcodeDetection barcodeDetector(threshold, maxLines, targetSpeed);  // Set threshold to 500, stop after 3 lines
OLEDDisplay oled;

void setup() {
  oled.init();
  oled.printMessage("<<<< WE ARE VIRO VENTURES >>>>");
  setupMotors();
  setupSensors();
  setupEncoders();
  barcodeDetector.init();      // Initialize barcode detection (sensors and display)
  Serial.begin(9600);
}

void loop() {
   // handleBlackDetectionAndDisplay();
    colorHandler.printAllSensorRGBValues();
  delay(4000);
   }
  //runForwardWithSensorPID();
  // Example: running the task for box position 0


//  barcodeDetector.update();     // Run the entire detection process
//     if (barcodeDetector.isCompleted()) {
//         // Optionally, do something when detection is complete
//         oled.printMessage("Barcode detection completed.");
//         while (true); // Stop the loop or perform other actions

//     }}
