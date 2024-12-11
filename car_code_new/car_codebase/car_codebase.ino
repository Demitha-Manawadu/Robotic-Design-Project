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
#include "menu.h"

ButtonReader myBtnReader;
Buzzer buzzer;
ColorSensor colorSensor;
OLEDDisplay oled; // single OLED object

const int threshold = 500;
const int maxLines = 3;    
const int targetSpeed = 180;
BarcodeDetection barcodeDetector(threshold, maxLines, targetSpeed);

void setup() {
  Serial.begin(9600);
  myBtnReader.initPins();
  oled.init();  // initialize OLED
  setupMotors();
  buzzer.playBeep(); 
  setupSensors();
  buzzer.playBeep();    
  setupEncoders();

  menu_init(); // initialize menu
}

void loop() {
  button_t btn = myBtnReader.readButton();
  if (btn != BTN_NONE) {
    menu_update(btn); // update menu logic
  }
  menu_draw(); // draw current menu state
  delay(10);
}

