// OLED_Display.cpp
#include "OLED_Display.h"

OLEDDisplay::OLEDDisplay() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void OLEDDisplay::init() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // I2C address may vary
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
}

void OLEDDisplay::clear() {
  display.clearDisplay();
  display.display();
}

void OLEDDisplay::printMessage(String message) {
  display.clearDisplay();
  display.setCursor(5, 10);
  display.print(message);
  display.display();
}

void OLEDDisplay::printSensorData(int sensorValue) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Sensor Value: ");
  display.print(sensorValue);
  display.display();
}
