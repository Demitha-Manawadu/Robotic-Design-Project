#include "button.h"

// Constructor
ButtonReader::ButtonReader() {
    // order: SELECT, FORWARD, BACKWARD, INTERRUPT
    _pins[0] = PIN_SELECT;
    _pins[1] = PIN_FORWARD;
    _pins[2] = PIN_BACKWARD;
    _pins[3] = PIN_INTERRUPT;

    for (int i = 0; i < 4; i++) {
        _lastStableState[i] = HIGH; // assume not pressed at start
        _lastReading[i] = HIGH;
        _lastChangeTime[i] = 0;
        _debouncing[i] = false;
    }
}

void ButtonReader::initPins() {
    // set pins as input pullup so buttons read LOW when pressed
    for (int i = 0; i < 4; i++) {
        pinMode(_pins[i], INPUT_PULLUP);
    }
}

button_t ButtonReader::readButton() {
    // We read all buttons, apply debouncing, return the first pressed we find
    // If multiple pressed, priority is SELECT > FORWARD > BACKWARD > INTERRUPT
    // (just like before, or adjust as needed)

    // read raw states
    for (int i = 0; i < 4; i++) {
        int reading = digitalRead(_pins[i]);

        // if reading changed from last reading, reset debounce timer
        if (reading != _lastReading[i]) {
            _lastChangeTime[i] = millis();
            _debouncing[i] = true;
            _lastReading[i] = reading;
        }

        // check if enough time has passed since last change
        if (_debouncing[i] && (millis() - _lastChangeTime[i]) > DEBOUNCE_DELAY) {
            // time to finalize the stable state
            _debouncing[i] = false;
            _lastStableState[i] = reading;
        }
    }

    // now determine which button is pressed based on stable states
    // If a stable state is LOW, that means button is pressed
    // We'll do priority checking:
    if (_lastStableState[3] == HIGH) {
    return BTN_INTERRUPT;
    }
    else if (_lastStableState[0] == HIGH) {
        return BTN_SELECT;
    }
    else if (_lastStableState[1] == HIGH) {
        return BTN_FORWARD;
    }
    else if (_lastStableState[2] == HIGH) {
        return BTN_BACKWARD;
    }


    return BTN_NONE;
}

button_t ButtonReader::indexToButton(int idx) {
    // just a helper if you need it, currently not used
    switch(idx) {
        case 0: return BTN_SELECT;
        case 1: return BTN_FORWARD;
        case 2: return BTN_BACKWARD;
        case 3: return BTN_INTERRUPT;
        default: return BTN_NONE;
    }
}
