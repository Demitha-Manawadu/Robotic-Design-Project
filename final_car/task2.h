#ifndef TASK2_H
#define TASK2_H

extern int sensorValues[12];
void task_2(int no5);

void goBackwardUntilJunction();
void goForwardAndHandleJunction(char turnDirection);
// extern volatile long leftEncoderCount = 0;
// extern volatile long rightEncoderCount = 0;
#endif