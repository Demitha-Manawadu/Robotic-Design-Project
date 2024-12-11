#include "Buzzer.h"

#define BUZZER_PIN A8  // Define the buzzer pin as a constant

Buzzer::Buzzer() {
    pinMode(BUZZER_PIN, OUTPUT);  // Set the fixed buzzer pin as output
}
void Buzzer::playBeep() {
    tone(BUZZER_PIN, 256, 200);  // Play a 200ms beep at 1000Hz frequency
    delay(250);  // Short delay between beeps
}


void Buzzer::playMelody() {
    // Define melody notes and their durations
    int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};  // C4, D4, E4, F4, G4, A4, B4, C5
    int noteDurations[] = {250, 250, 250, 250, 250, 250, 250, 250};  // Duration for each note in ms

    // Iterate through each note and play it
    for (int i = 0; i < 8; i++) {
        int noteDuration = noteDurations[i];
        tone(BUZZER_PIN, melody[i], noteDuration);  // Play the note on the fixed pin
        delay(noteDuration * 1.3);  // Wait for the note to play with a slight gap
    }
    
    noTone(BUZZER_PIN);  // Stop the buzzer after the melody
}
