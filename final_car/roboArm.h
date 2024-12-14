#ifndef ROBOARM_H
#define ROBOARM_H
void task6();
void setupServo();
void lowerGripper();
void chamber();
void liftGripper();
int readSharpAnalog();
extern int gate;
extern bool bluee;
extern int whiteline;
// extern volatile long leftEncoderCount = 0;
// extern volatile long rightEncoderCount = 0;
#endif