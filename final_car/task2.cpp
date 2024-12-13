#define NUM_SENSORS 12
#include "task2.h"
#include "MotorControl.h"
#include <Arduino.h>
#include "SensorControl.h"
#include "PIDControl.h"
#include "Buzzer.h"
Buzzer buzzer2;
int whiteline =1;
int gate =0;
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


void goBackwardUntilJunction() {
  runBackwardWithoutPID(800);
    leftEncoderCount=0;
    rightEncoderCount=0;
    while (true) {
        // Move backward using PID
        runBackwardWithEncoderPID();

        // Check for a junction
        if (whiteline){
        readSensors();  // Update sensor values
        }
        else{readSensors();}

        int leftCount = 0, middleCount = 0, rightCount = 0;
        countSensorRegions(leftCount, middleCount, rightCount);

        // Junction detection logic: Adjust thresholds as needed
        if ( leftCount >= 4 || rightCount >= 4) {
            // Example: Junction detected if multiple sensors in all regions detect the line
            Serial.println("Junction detected. Stopping...");
            stopMotors();
            break;
        }
      
        delay(10);  // Small delay for stability
    }

    runForwardWithoutPID(400); 
}



void goForwardAndHandleJunction(char turnDirection) {
    int j =0;
    int leftCount, middleCount, rightCount;
    resetEncoders();  // Reset encoder counts
    while (true){
    // Update sensor readings
    readSensors();
    countSensorRegions(leftCount, middleCount, rightCount);

        // Run line-following PID
        
        // Check if the turn condition is met
        if (( leftCount > 0) || ( rightCount > 0)) {
            Serial.println("Potential junction detected. Moving forward for confirmation...");
            
            // Move forward a small encoder amount for junction confirmation
            resetEncoders();
            while (abs(leftEncoderCount) < 150 && abs(rightEncoderCount) < 150) {  // Adjust 50 for your robot
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
                    delay(200);
                    return;  // Exit the function after turning
            }
            
        

    runForwardWithSensorPID();

}
}
void boxdone(){
  goBackwardUntilJunction();
  turnByAngleWithPID(90); 
  corrector();
  goForwardAndHandleJunction('L');
  goForwardAndHandleJunction('L');
  goForwardAndHandleJunction('S');
  buzzer2.playBeep();
  digitalWrite(49,HIGH);
  goBackwardUntilJunction();
  goBackwardUntilJunction();
  turnByAngleWithPID(180); 
}
void task_2(int no5){
  corrector();
  goForwardAndHandleJunction('R');
  goForwardAndHandleJunction('S');
  if (no5==0){
    buzzer2.playBeep();
    digitalWrite(49,HIGH);
    goForwardAndHandleJunction('S');
    buzzer2.playBeep();
    digitalWrite(49,LOW);
    goBackwardUntilJunction();
    turnByAngleWithPID(90); 
    corrector();
    goForwardAndHandleJunction('L');
    goForwardAndHandleJunction('S');
    //check for gate 
    gate =1;
    turnByAngleWithPID(-90); 
    goForwardAndHandleJunction('S');
    buzzer2.playBeep();
    digitalWrite(49,HIGH);
    goBackwardUntilJunction();
    if (gate) {goBackwardUntilJunction();goBackwardUntilJunction();}
    digitalWrite(49,LOW);
    buzzer2.playBeep();
    goBackwardUntilJunction();
    turnByAngleWithPID(-90); 
    corrector();
    goForwardAndHandleJunction('R');
    goForwardAndHandleJunction('R');
    goForwardAndHandleJunction('S');
    digitalWrite(49,HIGH);
    buzzer2.playBeep();
    goForwardAndHandleJunction('S');
    digitalWrite(49,LOW);
    buzzer2.playBeep();
  }
  else {
    goForwardAndHandleJunction('R');
    goForwardAndHandleJunction('L');
    delay(1000);
    //check for gate 
    gate =0;
    if (!gate){
      if (no5==1){
        turnByAngleWithPID(180); 
        goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goBackwardUntilJunction();goBackwardUntilJunction();
        digitalWrite(49,LOW);
        buzzer2.playBeep();
      }
      else  if (no5==2){
        turnByAngleWithPID(90); 
        goForwardAndHandleJunction('S');goForwardAndHandleJunction('R');goForwardAndHandleJunction('R');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goForwardAndHandleJunction('S');
        digitalWrite(49,LOW);
        buzzer2.playBeep();
        boxdone();
      }
      else  if (no5==3){
        turnByAngleWithPID(90); 
        goForwardAndHandleJunction('S');
        goForwardAndHandleJunction('S');
        goForwardAndHandleJunction('R');goForwardAndHandleJunction('R');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        corrector();
        buzzer2.playBeep();
        goForwardAndHandleJunction('S');
        goForwardAndHandleJunction('S');
        digitalWrite(49,LOW);
        buzzer2.playBeep();
        boxdone();
      }
      else  if (no5==4){
        turnByAngleWithPID(90); 
        goForwardAndHandleJunction('S');
        goForwardAndHandleJunction('R');goForwardAndHandleJunction('L');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goBackwardUntilJunction();
        digitalWrite(49,LOW);
        buzzer2.playBeep();
        goBackwardUntilJunction();
        turnByAngleWithPID(-90); 
        goForwardAndHandleJunction('R');
        goForwardAndHandleJunction('S');
        goForwardAndHandleJunction('R');goForwardAndHandleJunction('R');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goForwardAndHandleJunction('S');goForwardAndHandleJunction('S');
        digitalWrite(49,LOW);
        buzzer2.playBeep();
        boxdone();

      }
    }
    if (gate){
      if(no5==1){
        turnByAngleWithPID(90);goForwardAndHandleJunction('R');
        goForwardAndHandleJunction('R');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goBackwardUntilJunction();
        goBackwardUntilJunction();
        boxdone();

      }

      else if(no5==2){
        turnByAngleWithPID(90);goForwardAndHandleJunction('S');goForwardAndHandleJunction('R');
        goForwardAndHandleJunction('R');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goBackwardUntilJunction();
        boxdone();

      }
      else if (no5==3){
        turnByAngleWithPID(90);goForwardAndHandleJunction('S');goForwardAndHandleJunction('R');
        goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goBackwardUntilJunction();goBackwardUntilJunction();
        digitalWrite(49,LOW);
        buzzer2.playBeep();
      }
      else  if (no5==2){
        turnByAngleWithPID(90); 
        goForwardAndHandleJunction('S');goForwardAndHandleJunction('R');goForwardAndHandleJunction('L');goForwardAndHandleJunction('S');
        digitalWrite(49,HIGH);
        buzzer2.playBeep();
        goBackwardUntilJunction();
        digitalWrite(49,LOW);
        buzzer2.playBeep();
        goBackwardUntilJunction();
        turnByAngleWithPID(-90); 
        goForwardAndHandleJunction('R');
        goForwardAndHandleJunction('R');
        goForwardAndHandleJunction('S');
        goBackwardUntilJunction();
        goBackwardUntilJunction();
        turnByAngleWithPID(180);
      }
  }
}
}