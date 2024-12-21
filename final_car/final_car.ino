#include <Arduino.h>
#include "PIDControl.h"
#include "SensorControl.h"
#include "MotorControl.h"
#include "Buzzer.h"
#include "ColorSensor.h"
#include "LineFollowAndTurn.h"
#include "task2.h"
#include "button.h"
#include "menu.h"
#include "OLED_Display.h"
#include "roboArm.h"
ButtonReader myBtnReader;
Buzzer buzzer;
//ColorSensor colorSensor;
OLEDDisplay oled; // single OLED object
#include "coindrop.h"
#include "Barcode.h"
void setup() {
  void setuplikesetup();
  setupsen() ;
  setupServo();
  Serial.begin(9600);
  myBtnReader.initPins();
  oled.init(); 
  initializeSensors();
  //calibrateSensors();
  setupEncoders();
  setupMotors();
  menu_init();
  digitalWrite(53,LOW);
  digitalWrite(51,LOW);
  digitalWrite(49,LOW);
  // put your setup code here, to run once:

}

void loop() {
    button_t btn = myBtnReader.readButton();
  if (btn != BTN_NONE) {
    menu_update(btn); // update menu logic
  }
  menu_draw(); // draw current menu state
  delay(10);
  // put your main code here, to run repeatedly:

}
