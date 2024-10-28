#include "SensorMotorControl.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SensorControl.h"  // Include the existing sensor control
#include "MovementControl.h"

// Define the OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Create the display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Speed and control variables for black detection
unsigned long blackStartTime = 0;  // Start time of black detection
unsigned long blackDurations[30];  // Array to store durations of black detections
int index = 0;  // Index to keep track of the blackDurations array
bool isBlackDetected = false;  // Flag to check if black was detected

// Initialize OLED and display system initialization message
void initializeOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }
  display.display();
  delay(2000);  // Pause for 2 seconds

  display.clearDisplay();
  display.setTextSize(1);             // Set text size
  display.setTextColor(SSD1306_WHITE);// Set text color
  display.setCursor(0, 0);            // Set cursor to top-left corner
  display.println("System Init");
  display.display();
  delay(1000);
}

// Function to handle black detection and display on OLED
void handleBlackDetectionAndDisplay() {
  // Read the value of the middle IR sensor (assuming A3 is used for black detection)
  int middleSensorValue = analogRead(A3);

  // Check if the middle sensor detects black
  if (middleSensorValue > 300) {  // Assuming black gives a lower value, adjust as per your sensor
    if (!isBlackDetected) {
      blackStartTime = millis();  // Record the start time when black is first detected
      isBlackDetected = true;
    }
  } else {
    // If black was detected and now it's white
    if (isBlackDetected) {
      unsigned long blackEndTime = millis();  // Record the end time when black detection stops
      unsigned long duration = blackEndTime - blackStartTime;  // Calculate duration of black detection

      // Store the duration in the array
      blackDurations[index++] = duration;

      // Check if the array is full, if so reset the index
      if (index >= 20) {
        index = 0;  // Reset index to overwrite old data
      }

      isBlackDetected = false;  // Reset the flag
    }
  }

  // Display the durations on the OLED
  displayDurationsOnOLED();
  delay(100);  // Small delay to prevent overwhelming the loop
}

// Function to display the durations of black detection on the OLED
void displayDurationsOnOLED() {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("Black Durations:");
  
  // Display the durations from the blackDurations array
  for (int i = 0; i < index; i++) {
    display.print(blackDurations[i]);
    display.print(" ms ||");

    // Ensure text fits on the screen, break lines accordingly
    if ((i + 1) % 2 == 0) {
      display.println();
    }
  }

  display.display();
}
