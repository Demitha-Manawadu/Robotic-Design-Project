// OLED_Display.h
#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin (or -1 if sharing Arduino reset pin)

class OLEDDisplay {
  private:
    Adafruit_SSD1306 display;

  public:
    OLEDDisplay();
    void init();
    void clear();
    void printMessage(String message);
    void printSensorData(int sensorValue);
};

#endif
// OLED_Display.h
#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin (or -1 if sharing Arduino reset pin)

class OLEDDisplay {
  private:
    Adafruit_SSD1306 display;

  public:
    OLEDDisplay();
    void init();
    void clear();
    void printMessage(String message);
    void printSensorData(int sensorValue);
};

#endif
