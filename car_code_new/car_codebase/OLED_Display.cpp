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
  display.setTextSize(2); 
  display.setCursor(5, 10);
  display.setTextColor(SSD1306_WHITE);
  display.print(message);
  display.display();
}

void OLEDDisplay::printSensorData(int sensorValue) {
  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Sensor Value: ");
  display.print(sensorValue);
  display.display();
}

void OLEDDisplay::displayScrollingName() {
  String name = "Viro Ventures";
  int textWidth = name.length() * 12;  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  for (int x = SCREEN_WIDTH; x > -textWidth; x -= 4) {
    display.clearDisplay();
    display.setCursor(x, 20);
    display.print(name);
    display.display();
    delay(10);
  }
}

// UI Methods

void OLEDDisplay::drawTitleBar(const char *title) {
  // Invert top bar
  display.fillRect(0, 0, SCREEN_WIDTH, 16, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print(title);
  display.setTextColor(SSD1306_WHITE);
}

void OLEDDisplay::drawHighlightedItem(int x, int y, const char *text) {
  display.fillRect(x, y, SCREEN_WIDTH, 16, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(x+2, y+2);
  display.print(text);
  display.setTextColor(SSD1306_WHITE);
}

void OLEDDisplay::drawNormalItem(int x, int y, const char *text) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x+2, y+2);
  display.print(text);
}

void OLEDDisplay::drawMenu(const char *title, const char* items[], int numItems, int currentIndex, int itemsPerPage) {
  display.clearDisplay();
  drawTitleBar(title);

  int pageStart = (currentIndex / itemsPerPage) * itemsPerPage;
  int itemHeight = 16;
  int itemsYStart = 16; // below title

  for (int i = 0; i < itemsPerPage; i++) {
    int idx = pageStart + i;
    if (idx >= numItems) break;
    int yPos = itemsYStart + i*itemHeight;

    if (idx == currentIndex) {
      drawHighlightedItem(0, yPos, items[idx]);
    } else {
      drawNormalItem(0, yPos, items[idx]);
    }
  }

  display.display();
}

void OLEDDisplay::drawTaskScreen(const char *taskName, const char *taskMessage) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Running:\n");

  // Highlight task name
  display.fillRect(0,16,SCREEN_WIDTH,16,SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(2, 18);
  display.print(taskName);

  // Print task message
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 34);
  display.print(taskMessage);

  display.setCursor(0, 50);
  display.print("INTERRUPT to menu");

  display.display();
}
