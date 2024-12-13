#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#define NUM_SENSORS 12  // Total number of sensors (A0 to A9)
void initializeSensors();
void readSensorsw() ;
// Function to set up sensors and initialize values
void readSensors();  // Function to read sensor values and store them
void calibrateSensors(); // Function to calibrate sensors

#endif
