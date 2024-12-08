#include "LineFollowAndTurn.h"
#include "SensorControl.h"
#include "MovementControl.h"
#include "AdvancedMotorControl.h"
#include "MotorControl.h"
#include "task2.h"


int no5; // Placeholder for any additional input

// Junction type: 1 = 4-way, 2 = T-junction, 3 = L-junction
int confirmAndClassifyJunction() {
  int junctionType = 0;
  const int targetCount = 200; // Example encoder count for confirmation

  // Reset encoders before moving forward
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // Navigate forward until reaching the target encoder count
  while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
    runForwardWithoutPID(200);  // Move forward without PID control
    readSensors();  // Update sensor readings during navigation

    // Check for both sides detecting the line (possible 4-way or T-junction)
    if ((sensorValues[0] == pathcolor && sensorValues[1] == pathcolor) &&
        (sensorValues[NUM_SENSORS - 1] == pathcolor && sensorValues[NUM_SENSORS - 2] == pathcolor)) {
      junctionType = 1;  // Mark as 4-way or T-junction
    }
  }

  // Stop the robot after reaching the target encoder count
  moveForward(0, 0);

  // Take final sensor readings to classify the junction
  readSensors();

  if (junctionType == 1) {
    // Confirm 4-way or T-junction based on center sensor values
    if (sensorValues[3] == pathcolor && sensorValues[4] == pathcolor) {
      return 1;  // 4-way junction
    } else {
      return 2;  // T-junction
    }
  } else {
    // Check for L-junction or no junction
    if (sensorValues[3] == pathcolor && sensorValues[4] == pathcolor) {
      return 2;  // T-junction
    } else {
      return 3;  // L-junction
    }
  }
}

// if (no5!=0){
  
// }

