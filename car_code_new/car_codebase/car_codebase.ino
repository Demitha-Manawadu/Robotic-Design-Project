#include "MotorControl.h"
#include "SensorControl.h"
#include "AdvancedMotorControl.h"
#include "MovementControl.h"
#include "OLED_Display.h"
#include "BarcodeDetection.h"
#include "Buzzer.h"
#include "ColorSensor.h"
#include "LineFollowAndTurn.h"
#include "task2.h"
#include "button.h"

ButtonReader myBtnReader;
Buzzer buzzer;  // Initialize the Buzzer object
ColorSensor colorSensor;

const int threshold = 500;  // Set your desired threshold for line detection
const int maxLines = 3;      // Max lines to detect before stopping
const int targetSpeed = 180; // Desired speed for moving forward

//ColorSensorHandler colorHandler;
BarcodeDetection barcodeDetector(threshold, maxLines, targetSpeed);  // Set threshold to 500, stop after 3 lines
OLEDDisplay oled;

void setup() {
    
  myBtnReader.initPins();
  // buzzer.playBeep(); 
  // buzzer.playBeep(); 
  // buzzer.playBeep(); 
  // buzzer.playBeep(); 
  // delay(500);
  oled.init();
  //oled.displayScrollingName();
  setupMotors();
  buzzer.playBeep(); 
  setupSensors();
  buzzer.playBeep();    
  setupEncoders();
  //colorSensor.initialize(); 
  //barcodeDetector.init();      // Initialize barcode detection (sensors and display)
  Serial.begin(9600);

}

void loop() {
  
  //colorSensor.detectColor();
   // Play a beep before starting line-following
  //  buzzer.playBeep();
  
  //  // color line follow 
  //  followLineAndTurnWithSquareDetection();

  //  // After detecting the white square
  //  buzzer.playBeep();
  //  buzzer.playBeep();
  //  buzzer.playBeep();
  //    // Play a beep to signal square detection
  //  oled.printMessage("White square detected. Stopping.");
   task_2();
   // Optional: Stop the robot or enter a halt state
   while (true) {
     // Keep the robot stopped or perform other actions as needed
     moveForward(0, 0);  // Ensure motors are stopped
     delay(1000);  // Prevent fast looping in halt state
   }
}
// void loop() {
//     button_t btn = myBtnReader.readButton();

//     switch(btn) {
//         case BTN_SELECT:
//             Serial.println("SELECT pressed!");
//             break;
//         case BTN_FORWARD:
//             Serial.println("FORWARD pressed!");
//             break;
//         case BTN_BACKWARD:
//             Serial.println("BACKWARD pressed!");
//             break;
//         case BTN_INTERRUPT:
//             Serial.println("INTERRUPT pressed!");
//             break;
//         case BTN_NONE:
//         default:
//             // no button pressed, chill out
//             break;
//     }

//     delay(10); // small delay to reduce serial spam
// }