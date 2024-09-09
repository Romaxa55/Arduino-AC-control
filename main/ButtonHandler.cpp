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
        rgbLed.blue();
        delay(300);  // Уменьшение количества вызовов и улучшение читаемости
        rgbLed.off();
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
}

void ButtonHandler::handleMediumPress() {
#ifdef DEBUG
    Serial.println(F("Handling medium press: entering programming mode."));
#endif
    uint32_t startMillis = millis();
    while (millis() - startMillis < 30000) {
        rgbLed.blue();
        delay(500);
        rgbLed.off();
        delay(500);
    }
}

void ButtonHandler::handleLongPress() {
#ifdef DEBUG
    Serial.println(F("Handling long press: clearing EEPROM and cycling through LEDs."));
#endif

    rgbLed.red();
    eepromHandler.clearEEPROM();
    rgbLed.blue();
    delay(1000);
    rgbLed.white();
    delay(3000);
    rgbLed.off();
    resetDevice();
}

void ButtonHandler::resetDevice() {
#ifdef DEBUG
    Serial.println(F("Resetting device."));
#endif
    wdt_enable(WDTO_15MS);
    while (true);
}
