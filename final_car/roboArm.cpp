#include <Servo.h>
#include <Arduino.h>
#include "SensorControl.h"
#include "PIDControl.h"
#include "task2.h"
#include "MotorControl.h"
#include "roboArm.h"
int length=1550;
// Create servo objects for two servos
Servo myServo;       // Servo for grabbing/dropping the box
Servo liftServo;     // Servo for lifting/lowering the gripper

const int sensorPin = A15; // Analog pin connected to Sharp IR sensor output
int boxHeight;
int boxHeight2;
int boxHeight3;
// Function to read the analog value from the Sharp IR sensor
int readSharpAnalog() {
  return analogRead(sensorPin); // Return the analog reading
}

// Function to move a servo smoothly to a target angle
void smoothMove(Servo &servo, int startAngle, int endAngle, int delayTime) {
  if (startAngle < endAngle) {
    for (int pos = startAngle; pos <= endAngle; pos++) {
      servo.write(pos);
      delay(delayTime); // Smooth transition
    }
  } else {
    for (int pos = startAngle; pos >= endAngle; pos--) {
      servo.write(pos);
      delay(delayTime); // Smooth transition 
    }
  }
}

// Function to grab the box (servo on pin 6)
void grabBox() {
  smoothMove(myServo, 180, 0, 15); // Smoothly move from 180 to 0 degrees
  delay(500); // Hold the box for 2 seconds
}

// Function to drop the box (move gradually and release)
void dropBox() {
  smoothMove(myServo, 0, 180, 15);  // Smoothly move to 90 degrees
  delay(500); 
  runBackwardWithoutPID(300);                    // Pause for the box to start releasing                  // Wait for 2 seconds
}

// Function to lift the gripper (servo on pin 9)
void liftGripper() {
  smoothMove(liftServo, 0, 180, 15); // Move from 90° (down) to 0° (up)
  delay(500);                      // Hold the position for 1 second
}

// Function to lower the gripper (servo on pin 9)
void lowerGripper() {
  smoothMove(liftServo, 180, 0, 15); // Move from 0° (up) to 90° (down)
  delay(500);                      // Hold the position for 1 second
}

// Function to determine the height of the box
int detectBoxHeight() {
  // Move to 7 cm position (7cm position is mapped to the 0 degrees position/ starting position)
  liftServo.write(0);

  // Take sensor reading at the starting point
  int sensorValue = readSharpAnalog();
  bool detectedAt7cm = sensorValue > 100; // Threshold for detection (adjust as needed)
  delay(500);
  if (!detectedAt7cm) {
    return 5; // Box height is 5 cm
  }

  // Move to 13 cm position (is mapped to the 180 degrees position)
  smoothMove(liftServo, 0, 180, 15);
  delay(500);

  sensorValue = readSharpAnalog();
  bool detectedAt13cm = sensorValue > 100; // Threshold for detection
  delay(500);
  if (detectedAt7cm && !detectedAt13cm) {
    return 10; // Box height is 10 cm
  }
  if (detectedAt7cm && detectedAt13cm) {
    return 15; // Box height is 15 cm
  }

  return -1; // Error case (should not reach here)
}

void setupServo() {
  Serial.begin(9600); // Initialize Serial communication

  // Attach the servos to their respective pins
  myServo.attach(11);      // Gripper servo on pin 6
  liftServo.attach(12);    // Lifting servo on pin 9

  // Initialize both servos to their starting positions
  myServo.write(180);      // Gripper open position
  liftServo.write(0);   // Gripper down position
  delay(1000);            // Wait for servos to initialize
}

void task6() {

  bluee=1-gate;
  whiteline=false;
  if (bluee){
    goForwardAndHandleJunction('L');
    runForwardWithoutPID_1(length);
    int boxHeight = detectBoxHeight();
    Serial.print("Box Height: ");
    Serial.println(boxHeight);
    lowerGripper();
    delay(500);
    grabBox();        // Close the gripper to grab the box
    delay(500); 
    liftGripper(); //move the gripper up
    delay(500);
    turnByAngleWithPID(-180);
      if (boxHeight==5){
        goForwardAndHandleJunction('S');
        runForwardWithoutPID_1(length);
        lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
      }
      else if (boxHeight==10){
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('S');
          runForwardWithoutPID_1(length);
      }
      else {
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
      }
    int boxHeight2 = detectBoxHeight();
    Serial.print("Box Height: ");
    Serial.println(boxHeight2);
    lowerGripper();
    delay(500);
    grabBox();        // Close the gripper to grab the box
    delay(500); 
    liftGripper(); //move the gripper up
    delay(1000);
    turnByAngleWithPID(-180);
      if (boxHeight2==10){
        goForwardAndHandleJunction('S');
        runForwardWithoutPID_1(length);
        lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
      }
      else if (boxHeight2==5){
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
      }
      else {
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('S');
          runForwardWithoutPID_1(length);
      }
    int boxHeight3 = detectBoxHeight();
    Serial.print("Box Height: ");
   // Serial.println(boxHeight3);
    lowerGripper();
    delay(500);
    grabBox();        // Close the gripper to grab the box
    delay(500); 
    liftGripper(); //move the gripper up
    delay(1000);
    turnByAngleWithPID(-180);   
      if (boxHeight3==15){
        goForwardAndHandleJunction('S');
        runForwardWithoutPID_1(length);
        lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          
      }
      else if (boxHeight3==10){
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
      }    
      else {
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('S');
          
      }
  }
  else{
    goForwardAndHandleJunction('L');
    runForwardWithoutPID_1(length);
    int boxHeight = detectBoxHeight();
    Serial.print("Box Height: ");
    Serial.println(boxHeight3);
    lowerGripper();
    delay(500);
    grabBox();        // Close the gripper to grab the box
    delay(500); 
    liftGripper(); //move the gripper up
    delay(1000);
    turnByAngleWithPID(-180);
      if (boxHeight==15){
        goForwardAndHandleJunction('S');
        runForwardWithoutPID_1(length);
        lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
      }
      else if (boxHeight==10){
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('S');
          runForwardWithoutPID_1(length);
      }
      else {
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
      }
    int boxHeight2 = detectBoxHeight();
    Serial.print("Box Height: ");
    Serial.println(boxHeight2);
    lowerGripper();
    delay(500);
    grabBox();        // Close the gripper to grab the box
    delay(500); 
    liftGripper(); //move the gripper up
    delay(1000);
    turnByAngleWithPID(-180);
      if (boxHeight2==10){
        goForwardAndHandleJunction('S');
        runForwardWithoutPID_1(length);
        lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
      }
      else if (boxHeight2==15){
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
      }
      else {
          goForwardAndHandleJunction('L');
          goForwardAndHandleJunction('R');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('S');
          runForwardWithoutPID_1(length);
      }
    int boxHeight3 = detectBoxHeight();
    Serial.print("Box Height: ");
    Serial.println(boxHeight3);
    lowerGripper();
    delay(500);
    grabBox();        // Close the gripper to grab the box
    delay(500); 
    liftGripper(); //move the gripper up
    delay(1000);
    turnByAngleWithPID(-180);   
      if (boxHeight3==5){
        goForwardAndHandleJunction('S');
        runForwardWithoutPID_1(length);
        lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          
      }
      else if (boxHeight3==10){
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
      }  
      else {
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('L');
          runForwardWithoutPID_1(length);
          lowerGripper();   // Move the gripper down
          delay(500);      // Wait 1 second
          dropBox();        // Open the gripper to release the box
          delay(500);

          turnByAngleWithPID(-180);
          goForwardAndHandleJunction('R');
          goForwardAndHandleJunction('S');
          goForwardAndHandleJunction('S');
          
      }

      }
    goForwardAndHandleJunction('S');
    runForwardWithoutPID(300);
    turnByAngleWithPID(-90);
    runForwardWithoutPID(600);
    // goForwardAndHandleJunction('L');
    // goForwardAndHandleJunction('S');
    // lowerGripper();
    // delay(500);
    // grabBox();        // Close the gripper to grab the box
    // delay(500); 
    // liftGripper(); //move the gripper up
    // delay(1000);
    // turnByAngleWithPID(-180);
    // goForwardAndHandleJunction('L');
}
void chamber() {
  whiteline=false;
  // int sensorValue = readSharpAnalog();
  // if (sensorValue > 100) {
  //   stopRobot(); // Stop the robot if the sensor value exceeds the threshold
  // }

goForwardAndHandleJunction('L');
goForwardAndHandleJunction('S');
lowerGripper();
delay(500);
grabBox();        // Close the gripper to grab the box
delay(500); 
liftGripper(); //move the gripper up
delay(500);
turnByAngleWithPID(-180);
goForwardAndHandleJunction('L');

goForwardAndHandleJunction('S');
goForwardAndHandleJunction('R');
lowerGripper(); 
runForwardWithoutPID_1(2300); 
// while (true){
//   int count=0;
//   readSensorsw();
// for (int i = 0; i < NUM_SENSORS; i++) {
//       if (sensorValues[i] == 0) {
//         count+=1;
//         }  // If the sensor detects the line
//       runForwardWithSensorPIDw();
//       if (count==12){
//         stopMotors();
//         break;} 
//       }
// }
liftGripper();

turnByAngleWithPID(-190);
goForwardAndHandleJunction('R');
// HIDDEN TASK
goForwardAndHandleJunction('S');
runForwardWithoutPID_1(700); 
lowerGripper();   // Move the gripper down
delay(500);      // Wait 1 second
dropBox(); 
runBackwardWithoutPID(500);       // Open the gripper to release the box
delay(500);
grabBox();
runForwardWithoutPID(500);
turnByAngleWithPID(-180);
goForwardAndHandleJunction('R');goForwardAndHandleJunction('S');
runForwardWithoutPID(2000);
turnByAngleWithPID(90);
liftGripper();
}