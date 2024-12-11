#include "LineFollowAndTurn.h"
#include "SensorControl.h"
#include "MovementControl.h"
#include "AdvancedMotorControl.h"
#include "MotorControl.h"

// Define the sensor array and detection flags
bool cornerDetected = false;
bool squareDetected = false;  // New flag to detect the black square

void followLineAndTurnWithSquareDetection() {
  cornerDetected = false;

  // Loop for line-following with PID, handling junctions, corners, and square detection
  while (!cornerDetected && !squareDetected) {
    runForwardWithSensorPID();  // Follow the line

    readSensors();  // Update sensor values

    // Check if all sensors detect black (indicating a black square)
    bool allSensorsDetectBlack = true;
    for (int i = 0; i < NUM_SENSORS; i++) {
      if (sensorValues[i] != 0) {  // If any sensor does not detect black, break
        allSensorsDetectBlack = false;
        break;
      }
    }

    if (allSensorsDetectBlack) {
      // Confirm the square detection by maintaining the condition for 200 ms
      unsigned long squareDetectionStart = millis();
      while (millis() - squareDetectionStart < 200) {  // Confirmation period
        readSensors();
        allSensorsDetectBlack = true;
        for (int i = 0; i < NUM_SENSORS; i++) {
          if (sensorValues[i] != 0) {  // Any sensor not detecting black cancels the detection
            allSensorsDetectBlack = false;
            break;
          }
        }
        if (!allSensorsDetectBlack) {
          break;  // Exit if the condition isn't met
        }
      }

      if (allSensorsDetectBlack) {
        squareDetected = true;
        moveForward(0, 0);  // Stop the robot
        Serial.println("Black square detected. Stopping.");
        return;  // Exit the function upon square detection
      }
    }

    // Existing corner and 4-way junction logic here
    // Check for a 4-way junction: both left and right detect the line briefly
    if (sensorValues[0] == 1 && sensorValues[1] == 1 && 
        sensorValues[NUM_SENSORS - 1] == 1 && sensorValues[NUM_SENSORS - 2] == 1) {
      // Detected a 4-way junction, continue forward without turning
      runForwardWithoutPID(250);
      delay(200);  // Brief delay to pass the junction
      continue;  // Continue with PID line following
    }

    // Check for persistent left corner detection
    bool leftCornerConfirmed = sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1;
    unsigned long leftDetectionTime = millis();

    if (leftCornerConfirmed) {
      moveForward(0, 0);
      // Wait to confirm the corner by checking for persistent detection
      while ((millis() - leftDetectionTime) < 150) {  // 150 ms confirmation window
        moveForward(180, 180);
        readSensors();
        if ((sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1)) {
          leftCornerConfirmed = false;
          moveForward(0, 0);
          break;  // Exit if the corner is not persistent
        }
      }

      if (leftCornerConfirmed) {
        moveForward(0, 0);  // Stop briefly
        //delay(400);
        runForwardWithoutPID(200);  // Stabilize with forward motion
        delay(400);
        turnByAngleWithPID(-90);  // Turn 90 degrees left
        cornerDetected = false;  // Reset corner detection for further turns
        corrector();
      }
    }

    // Check for persistent right corner detection
    bool rightCornerConfirmed = sensorValues[NUM_SENSORS - 1] == 1 && sensorValues[NUM_SENSORS - 2] == 1 && sensorValues[NUM_SENSORS - 3] == 1 && sensorValues[NUM_SENSORS - 4] == 1;
    unsigned long rightDetectionTime = millis();

    if (rightCornerConfirmed) {
      moveForward(0, 0);
      // Wait to confirm the corner by checking for persistent detection
      while ((millis() - rightDetectionTime) < 150) {  // 150 ms confirmation window
        moveForward(180, 180);
        readSensors();
        if ((sensorValues[NUM_SENSORS - 1] == 1 && sensorValues[NUM_SENSORS - 2] == 1 && sensorValues[0] == 1 && sensorValues[1] == 1)) {
          rightCornerConfirmed = false;
          moveForward(0, 0);
          break;  // Exit if the corner is not persistent
        }
      }

      if (rightCornerConfirmed) {
        moveForward(0, 0);  // Stop briefly
        //delay(400);
        runForwardWithoutPID(200);  // Stabilize with forward motion
        delay(400);
        turnByAngleWithPID(90);  // Turn 90 degrees right
        cornerDetected = false;  // Reset corner detection for further turns
        corrector();
      }
    }
  }
}

// Corrector function for PID adjustments after turns
void corrector() {
  unsigned long startTime = millis();
  while (millis() - startTime < 400) {  // Run for approximately 1 second
    runForwardWithSensorPID();
  }
}
