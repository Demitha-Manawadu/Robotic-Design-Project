#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Define OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class OLEDDisplay {
public:
    OLEDDisplay();
    void init();
    void clear();
    void printMessage(String message);
    void printSensorData(int sensorValue);
    void displayScrollingName();

    // Newly added UI methods for menu
    void drawTitleBar(const char *title);
    void drawHighlightedItem(int x, int y, const char *text);
    void drawNormalItem(int x, int y, const char *text);
    void drawMenu(const char *title, const char* items[], int numItems, int currentIndex, int itemsPerPage);
    void drawTaskScreen(const char *taskName, const char *taskMessage);

private:
    Adafruit_SSD1306 display;
};

#endif
