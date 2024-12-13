#include <Arduino.h>
#include "OLED_Display.h"
#include "Barcode.h"

OLEDDisplay oledq;


// Pins for motor control
#define LEFT_MOTOR_FORWARD 48
#define LEFT_MOTOR_BACKWARD 50
#define RIGHT_MOTOR_FORWARD 46
#define RIGHT_MOTOR_BACKWARD 44
#define ENA 8
#define ENB 9

// Pins for encoders
#define LEFT_ENCODER_A 19
#define LEFT_ENCODER_B 18
#define RIGHT_ENCODER_A 2
#define RIGHT_ENCODER_B 3

// IR sensor pins
#define LEFT_SENSOR A5
#define RIGHT_SENSOR A4

long leftEncoderCountw = 0;
long rightEncoderCountw = 0;

// PID constants
float Kpw = 1.0, Kiw = 0.0, Kdw = 0.0;

// Speed control variables
int baseSpeed = 150;
int leftMotorSpeed;
int rightMotorSpeed;

// Array to store bin values
const int maxArraySize = 10;
int binArray[maxArraySize];
int arrayIndex = 0;

// Encoder count tracking for white detection
bool wasWhite = false;
long startEncoderCount = 0;

// ISR for left encoder
void leftEncoderISRw() {
  if (digitalRead(LEFT_ENCODER_B) == HIGH) {
    leftEncoderCountw++;
  } else {
    leftEncoderCountw--;
  }
}

// ISR for right encoder
void rightEncoderISRw() {
  if (digitalRead(RIGHT_ENCODER_B) == HIGH) {
    rightEncoderCountw++;
  } else {
    rightEncoderCountw--;
  }
}

void stopMotorsw() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void setuplikesetup() {
  Serial.begin (9600);
  // Set up motor control pins
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set up encoder pins
  pinMode(LEFT_ENCODER_A, INPUT);
  pinMode(LEFT_ENCODER_B, INPUT);
  pinMode(RIGHT_ENCODER_A, INPUT);
  pinMode(RIGHT_ENCODER_B, INPUT);

  // Set up IR sensor pins
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  // Attach interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_A), leftEncoderISRw, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_A), rightEncoderISRw, RISING);

  // Initialize motor speeds
  leftMotorSpeed = baseSpeed;
  rightMotorSpeed = baseSpeed;}

long binaryToDecimal(int binary[], int size) {
    long decimal = 0;
    
    for (int i = 0; i < size; i++) {
        decimal = decimal * 2 + binary[i];
    }
    
    return decimal;
}
void detection (){
while (true){
  // Calculate error between encoder counts
  long error = leftEncoderCountw - rightEncoderCountw;

  // PID control (basic proportional control for simplicity)
  int correction = Kpw * error;

  // Adjust motor speeds
  leftMotorSpeed = constrain(baseSpeed - correction, 0, 255);
  rightMotorSpeed = constrain(baseSpeed + correction, 0, 255);

  // Apply motor speeds
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);

  // Move forward
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);

  // Read IR sensor values
  bool leftWhite = analogRead(LEFT_SENSOR) > 200; // Adjust threshold as needed
  bool rightWhite = analogRead(RIGHT_SENSOR) > 200; // Adjust threshold as needed

  if ((leftWhite || rightWhite) && !wasWhite) {
    // Transition to white detected
    wasWhite = true;
    startEncoderCount = (leftEncoderCountw + rightEncoderCountw) / 2;
  } else if (!(leftWhite || rightWhite) && wasWhite) {
    // Transition to black detected
    wasWhite = false;
    long endEncoderCount = (leftEncoderCountw + rightEncoderCountw) / 2;
    long count = endEncoderCount - startEncoderCount;

    // Determine bin value
    int bin = (count > 1000) ? 1 : 0;

    // Store bin value in array
    if (arrayIndex < maxArraySize) {
      binArray[arrayIndex++] = bin;
      Serial.println(bin);
    } else {
      stopMotorsw();
      oledq.displayArray(binArray,maxArraySize);// Display the array on the OLED
      return binaryToDecimal(binArray,maxArraySize); // Halt execution
    }
  }
}
}


void detect(){
  setuplikesetup();
  oledq.printMessage("setup");
  delay(1000);
  detection();
  }
