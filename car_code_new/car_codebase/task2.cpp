#include "LineFollowAndTurn.h"
#include "SensorControl.h"
#include "MovementControl.h"
#include "AdvancedMotorControl.h"
#include "MotorControl.h"
#include "task2.h"
#include "ColorSensor.h"
#include "Buzzer.h"

Buzzer buzzer2;
int no5=0; // Placeholder for any additional input
int pathcolor=1;
// Junction type: 1 = 4-way, 2 = T-junction, 3 = L-junction
int confirmAndClassifyJunction() {
  int junctionType = 0;
  const int targetCount = 300; // Example encoder count for confirmation

  // Reset encoders before moving forward
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // Navigate forward until reaching the target encoder count
  while (abs(leftEncoderCount) < targetCount && abs(rightEncoderCount) < targetCount) {
    moveForward(180, 180); // Move forward without PID control
    readSensors();  // Update sensor readings during navigation

    // Check for both sides detecting the line (possible 4-way or T-junction)
    if ((sensorValues[0] == 1 && sensorValues[1] == 1 ) && (sensorValues[NUM_SENSORS - 1] == 1 && sensorValues[6] == 1 )) {
      junctionType = 1;  // Mark as 4-way or T-junction
    }
  }

  // Stop the robot after reaching the target encoder count
  moveForward(0, 0);
  delay(200);

  // Take final sensor readings to classify the junction
  readSensors();

  if (junctionType == 1) {
    // Confirm 4-way or T-junction based on center sensor values
    if (sensorValues[3] == 1 && sensorValues[4] == 1) {      
      return 1;  // 4-way junction
    } 
    else {
      return 2;  // T-junction
      
    }
  } else {
    // Check for L-junction or no junction
    if (sensorValues[3] == 1 && sensorValues[4] == 1) {
      return 2;  // T-junction
    } else {
      return 3;  // L-junction
    }
  }
}
void task_2() {
    corrector();
    corrector();
    int angleInput = 0;

    while (true) {  // First while loop
        angleInput = 0;
        bool left = false;
        runForwardWithSensorPID();  // Follow the line
        readSensors();  // Update sensor readings

        // Check for corner detection
        if ((sensorValues[0] == 1 && sensorValues[1] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)) {
            if (sensorValues[0] == 1 && sensorValues[1] == 1) {
                left = true;  // Left turn detected
            } else {
                left = false;  // Right turn detected
            }
            angleInput = confirmAndClassifyJunction();  // Determine junction type
        }

        // Handle detected junctions
        if (angleInput == 2) {  // 4-way junction detected
            moveForward(0, 0);  // Stop the robot
            break;  // Exit the loop
        }

        if (angleInput == 3) {  // L-junction detected
            moveForward(0, 0);  // Stop the robot momentarily
            delay(200);

            if (left) {
                turnByAngleWithPID(-90);  // Turn left
            } else {
                turnByAngleWithPID(90);  // Turn right
            }
            delay(100);
            angleInput = 0;  // Reset for further detection
            corrector();  // Stabilize after the turn
        }
    }
    moveForward(0, 0);  // Stop the robot when exiting the first loop

//when the value is 1

    if (no5==0){
      digitalWrite(49,HIGH);
      buzzer2.playBeep();
      while (true) {  // Second while loop, similar logic to the first one
            angleInput = 0;
            bool left = false;
            runForwardWithSensorPID();  // Follow the line
            readSensors();  // Update sensor readings

            // Check for corner detection
            if ((sensorValues[0] == 1 && sensorValues[1] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)) {
                if (sensorValues[0] == 1 && sensorValues[1] == 1) {
                    left = true;  // Left turn detected
                } else {
                    left = false;  // Right turn detected
                }
                angleInput = confirmAndClassifyJunction();  // Determine junction type
            }

            // Handle detected junctions
            if (angleInput == 3) {  // 4-way junction detected
                moveForward(0, 0);  // Stop the robot
                break;  // Exit the loop
            }
        }
        digitalWrite(49,LOW);
        moveForward(0, 0);
        delay(500);
        runBackwardWithoutPID(500);
        moveForward(0, 0);
        delay(500);
        // corrector();
        // moveForward(0, 0);
        // delay(500);
        // runBackwardWithoutPID(1000);
        // delay(200);
        // corrector();
        // delay(200);
        buzzer2.playBeep();
        while (true) {  // Second while loop, similar logic to the first one
            angleInput = 0;
            bool left = false;
            runBackwardWithEncoderPID();  // Follow the line
            readSensors();  // Update sensor readings

            // Check for corner detection
            if ((sensorValues[0] == 1 && sensorValues[1] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)) {
            moveForward(0, 0); 

            turnByAngleWithPID(90);
            moveForward(0, 0); 
            break;
            }
        }
        delay(100);




    }

    if (no5 != 0) {
        while (true) {  // Second while loop, similar logic to the first one
            angleInput = 0;
            bool left = false;
            runForwardWithSensorPID();  // Follow the line
            readSensors();  // Update sensor readings

            // Check for corner detection
            if ((sensorValues[0] == 1 && sensorValues[1] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)) {
                if (sensorValues[0] == 1 && sensorValues[1] == 1) {
                    left = true;  // Left turn detected
                } else {
                    left = false;  // Right turn detected
                }
                angleInput = confirmAndClassifyJunction();  // Determine junction type
            }

            // Handle detected junctions
            if (angleInput == 1) {  // 4-way junction detected
                moveForward(0, 0);  // Stop the robot
                break;  // Exit the loop
            }

            if (angleInput == 3) {  // L-junction detected
                moveForward(0, 0);  // Stop the robot momentarily
                delay(200);

                if (left) {
                    turnByAngleWithPID(-90);  // Turn left
                    corrector();
                } else {
                    turnByAngleWithPID(90);  // Turn right
                    corrector();
                }
                delay(100);
                angleInput = 0;  // Reset for further detection
                corrector();  // Stabilize after the turn
            }
        }
        moveForward(0, 0);
        delay(1000);
        turnByAngleWithPID(-90);

        // Check for the gate (not implemented here)
    }
}
