#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h>

class ButtonHandler {
public:
    ButtonHandler(uint8_t pin);
    void update();

private:
    uint8_t buttonPin;
    uint32_t buttonPressTime;
    uint8_t buttonPressed : 1;
    uint8_t actionTriggered : 1;

    uint32_t lastDebounceTime;
    uint16_t debounceDelay;

    void indicatePressDuration(uint32_t currentMillis);
    void handleShortPress();
    void handleMediumPress();
    void handleLongPress();
    void resetDevice();
};

#endif // BUTTONHANDLER_H
