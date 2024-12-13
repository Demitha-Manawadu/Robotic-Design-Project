#define NUM_SENSORS 12
#include "task2.h"
#include "MotorControl.h"
#include <Arduino.h>
#include "SensorControl.h"
#include "PIDControl.h"

void countSensorRegions(int &leftCount, int &middleCount, int &rightCount) {
    leftCount = 0;
    middleCount = 0;
    rightCount = 0;

    // Define regions for left, middle, and right
    int leftEnd = NUM_SENSORS / 3;
    int middleEnd = 2 * NUM_SENSORS / 3;

    for (int i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] == 1) {  // If the sensor detects the line
            if (i < leftEnd) {
                leftCount++;  // Left region
            } else if (i < middleEnd) {
                middleCount++;  // Middle region
            } else {
                rightCount++;  // Right region
            }
        }
    }
}


void goForwardAndHandleJunction(char turnDirection) {
    int j =0;
    int leftCount, middleCount, rightCount;
    resetEncoders();  // Reset encoder counts

    // Update sensor readings
    readSensors();
    countSensorRegions(leftCount, middleCount, rightCount);

        // Run line-following PID
        
        // Check if the turn condition is met
        if (( leftCount > 1) || ( rightCount > 1)) {
            Serial.println("Potential junction detected. Moving forward for confirmation...");
            
            // Move forward a small encoder amount for junction confirmation
            resetEncoders();
            while (abs(leftEncoderCount) < 150 && abs(rightEncoderCount) < 50) {  // Adjust 50 for your robot
                readSensors();
                countSensorRegions(leftCount, middleCount, rightCount);
                moveForward(150,150);
                if (( leftCount > 2 ) ||
                    ( rightCount > 2 )) {
                    Serial.println("Junction confirmed.");
                    j=1;
                    delay(100);
                    }
            }
        }
            if (j) {
                    if (turnDirection == 'L') {
                        turnByAngleWithPID(-90); // Execute left turn
                    } else if (turnDirection == 'R') {
                        turnByAngleWithPID(90); // Execute right turn
                    }
                    else if (turnDirection == 'S') {
                        stopMotors();  // Execute right turn
                    }

                    return;  // Exit the function after turning
            }
            
        

    runForwardWithSensorPID();

}

void task_2(){
  corrector();
  goForwardAndHandleJunction('L');
  goForwardAndHandleJunction('S');

}