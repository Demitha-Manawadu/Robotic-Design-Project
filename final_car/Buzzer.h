#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>  // Necessary for Arduino functions

class Buzzer {
public:
    Buzzer();          // Constructor without pin argument
    void playMelody(); // Function to play a melody
    void playBeep(); 
};

#endif
