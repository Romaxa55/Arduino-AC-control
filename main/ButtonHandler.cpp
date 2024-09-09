#include "ButtonHandler.h"
#include "config.h"
#include <avr/wdt.h>

ButtonHandler::ButtonHandler(uint8_t pin)
        : buttonPin(pin), buttonPressTime(0), buttonPressed(0), actionTriggered(0),
          lastDebounceTime(0), debounceDelay(50) {
    pinMode(buttonPin, INPUT_PULLUP);
}

void ButtonHandler::update() {
    uint32_t currentMillis = millis();

    if (digitalRead(buttonPin) == LOW) {
        if (!buttonPressed) {
            buttonPressed = 1;
            buttonPressTime = currentMillis;
            actionTriggered = 0;
#ifdef DEBUG
            Serial.println(F("Button pressed."));
#endif
        }

        indicatePressDuration(currentMillis);

    } else {
        if (buttonPressed) {
            uint32_t pressDuration = currentMillis - buttonPressTime;

            if (pressDuration < 5000 && !actionTriggered) {
#ifdef DEBUG
                Serial.println(F("Short press detected."));
#endif
                handleShortPress();
            } else if (pressDuration >= 5000 && pressDuration < 10000 && !actionTriggered) {
#ifdef DEBUG
                Serial.println(F("Medium press detected."));
#endif
                handleMediumPress();
            } else if (pressDuration >= 10000 && !actionTriggered) {
#ifdef DEBUG
                Serial.println(F("Long press detected."));
#endif
                handleLongPress();
            }

            buttonPressed = 0;
            actionTriggered = 1;
        }
    }
}

void ButtonHandler::indicatePressDuration(uint32_t currentMillis) {
    uint32_t pressDuration = currentMillis - buttonPressTime;

    if (pressDuration < 5000) {
        rgbLed.green();
    } else if (pressDuration >= 5000 && pressDuration < 10000) {
        rgbLed.off();
        for (uint8_t i = 0; i < 3; i++) {
            rgbLed.blue();
            delay(100);
            rgbLed.off();
            delay(100);
        }
    } else if (pressDuration >= 10000) {
        rgbLed.red();
    }
}

void ButtonHandler::handleShortPress() {
#ifdef DEBUG
    Serial.println(F("Handling short press: turning on green LED."));
#endif
    rgbLed.green();
    delay(50);
    rgbLed.off();
#ifdef DEBUG
    Serial.println(F("Short press handled: green LED turned off."));
#endif
}

void ButtonHandler::handleMediumPress() {
#ifdef DEBUG
    Serial.println(F("Handling medium press: entering programming mode."));
#endif
    uint32_t startMillis = millis();
    uint32_t currentMillis = millis();

    while (currentMillis - startMillis < 30000) {
        rgbLed.blue();
        delay(500);
        rgbLed.off();
        delay(500);
        currentMillis = millis();
    }

#ifdef DEBUG
    Serial.println(F("Exiting programming mode."));
#endif
}

void ButtonHandler::handleLongPress() {
#ifdef DEBUG
    Serial.println(F("Handling long press: clearing EEPROM and cycling through LEDs."));
#endif

    indicateStartOfClearing();
    eepromHandler.clearEEPROM();
    indicateClearingCompleted();

    resetDevice();
}

void ButtonHandler::indicateStartOfClearing() {
    rgbLed.red();
}

void ButtonHandler::indicateClearingCompleted() {
    rgbLed.blue();
    delay(1000);
    rgbLed.white();
    delay(3000);
    rgbLed.off();
    delay(300);
}

void ButtonHandler::resetDevice() {
#ifdef DEBUG
    Serial.println(F("Resetting device."));
#endif
    wdt_enable(WDTO_15MS);
    while (true);
}
