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
    // Debounce logic remains the same
    for (int i = 0; i < 4; i++) {
        int reading = digitalRead(_pins[i]);
        if (reading != _lastReading[i]) {
            _lastChangeTime[i] = millis();
            _debouncing[i] = true;
            _lastReading[i] = reading;
        }

        if (_debouncing[i] && (millis() - _lastChangeTime[i]) > DEBOUNCE_DELAY) {
            _debouncing[i] = false;
            // Before we update _lastStableState[i], store its old value for edge detection
            int oldState = _lastStableState[i];
            _lastStableState[i] = reading;

            // Check for transition from HIGH to LOW (not pressed to pressed)
            if (oldState == LOW && _lastStableState[i] == HIGH) {
                // This button just went from not pressed to pressed
                // Return the corresponding button immediately
                switch(i) {
                    case 0: return BTN_SELECT;
                    case 1: return BTN_FORWARD;
                    case 2: return BTN_BACKWARD;
                    case 3: return BTN_INTERRUPT;
                }
            }
        }
    }

    // If no transitions detected, return BTN_NONE
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
