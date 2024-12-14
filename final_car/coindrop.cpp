#include <Servo.h> // Include the Servo library
#include "coindrop.h"
Servo coinServo;
#include "SensorControl.h"
#include "PIDControl.h"
#include "task2.h"
#include "MotorControl.h"
#include "Buzzer.h"
#include "roboArm.h" // Define servo for coin-dropping mechanism
Buzzer buzzer3;
// Pin definitions
const int ultrasonicTrig = 34;  // Trig pin for ultrasonic sensor
const int ultrasonicEcho = 36; // Echo pin for ultrasonic sensor    // Line sensor pin
const int servoPin = 10;       // Servo pin for coin-dropping mechanism

void setupsen() {
  // Initialize pins
  pinMode(ultrasonicTrig, OUTPUT);
  pinMode(ultrasonicEcho, INPUT);

  // Attach the servo to the pin
  coinServo.attach(servoPin);
  coinServo.write(0); // Set servo to the initial position

  // Add any other initialization if needed
}
float readUltrasonicDistance() {
    // Trigger the ultrasonic sensor
    digitalWrite(ultrasonicTrig, LOW); 
    delayMicroseconds(2);
    digitalWrite(ultrasonicTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrig, LOW);

    // Measure the duration of the echo pulse
    long duration = pulseIn(ultrasonicEcho, HIGH);

    // Calculate distance in centimeters (Speed of sound: 343 m/s or 0.0343 cm/µs)
    float distance = duration * 0.0343 / 2;

    // Return the measured distance
    return distance;
}

void navigateTerrain() {
    long distance = readUltrasonicDistance(); // Use the pre-defined sensor reading function
    if (distance < 20) { // Stop when close to the X-mark
      stopMotors();
      turnByAngleWithPID(90); // Stop motors (assume stopMotors() is pre-defined or use analogWrite to stop motors)
    }
    moveBackward(150,150); // Use the pre-defined backward motion function
    delay(50);
    stopMotors(); // Delay for smooth motion
}
void dropCoin() {
  coinServo.write(25); // Move servo to drop position
  delay(1000);         // Wait for the coin to drop
  coinServo.write(0);  // Return servo to the initial position
}

void looping() {
  while (true){
    readSensorsw();  
  // Navigate through the uneven terrain using the pre-defined backward motion function
    navigateTerrain();

  // Detect black line and drop the coin
    for (int i = 0; i < 12; i++) {
        if (sensorValues[i]==1){
          buzzer3.playBeep();
          dropCoin();break;}
    }
}
}
// Function to navigate the terrain using backward motion and ultrasonic sensor




// Function to drop the coin
