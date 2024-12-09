#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <stdint.h>

// Define your pins here. Change these to match your wiring.
#define PIN_SELECT    2
#define PIN_FORWARD   3
#define PIN_BACKWARD  4
#define PIN_INTERRUPT 5

// same button enum as before
typedef enum {
    BTN_NONE,
    BTN_SELECT,
    BTN_FORWARD,
    BTN_BACKWARD,
    BTN_INTERRUPT
} button_t;

class ButtonReader {
public:
    ButtonReader();
    void initPins();
    // read and return which button is pressed (or BTN_NONE)
    button_t readButton();

private:
    // We'll store pin numbers in an array for convenience
    // though we defined them as macros, we can still do this:
    int _pins[4];

    // track last stable state of each button
    // 0 = pressed, 1 = not pressed (assuming INPUT_PULLUP)
    int _lastStableState[4];

    // track last read (raw) state of each button
    int _lastReading[4];

    // time when we last changed reading
    unsigned long _lastChangeTime[4];

    // stable and raw reading differ, waiting for debounce
    bool _debouncing[4];

    // how long we wait for debounce
    static const unsigned long DEBOUNCE_DELAY = 50; // ms

    // map index to button_t
    button_t indexToButton(int idx);
};

#endif
