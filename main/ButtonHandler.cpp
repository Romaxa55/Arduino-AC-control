#include "ButtonHandler.h"
#include "config.h"
#include <avr/wdt.h>

// Константы для различных временных интервалов
const uint16_t SHORT_PRESS_DURATION = 5000;   // Короткое нажатие - менее 5 секунд
const uint16_t MEDIUM_PRESS_DURATION = 10000; // Среднее нажатие - от 5 до 10 секунд
const uint16_t LONG_PRESS_DURATION = 30000;   // Длинное нажатие - более 10 секунд

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

            if (pressDuration < SHORT_PRESS_DURATION && !actionTriggered) {
#ifdef DEBUG
                Serial.println(F("Short press detected."));
#endif
                handleShortPress();
            } else if (pressDuration >= SHORT_PRESS_DURATION && pressDuration < MEDIUM_PRESS_DURATION && !actionTriggered) {
#ifdef DEBUG
                Serial.println(F("Medium press detected."));
#endif
                handleMediumPress();
            } else if (pressDuration >= MEDIUM_PRESS_DURATION && !actionTriggered) {
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

    if (pressDuration < SHORT_PRESS_DURATION) {
        // Включаем зеленый, выключаем остальные
        rgbLed.turnOnColor("green");
        rgbLed.turnOffColor("blue");
        rgbLed.turnOffColor("red");
    } else if (pressDuration >= SHORT_PRESS_DURATION && pressDuration < MEDIUM_PRESS_DURATION) {
        // Включаем синий, выключаем остальные
        rgbLed.turnOffColor("green");
        rgbLed.turnOnColor("blue");
        rgbLed.turnOffColor("red");
    } else if (pressDuration >= MEDIUM_PRESS_DURATION) {
        // Включаем красный, выключаем остальные
        rgbLed.turnOffColor("green");
        rgbLed.turnOffColor("blue");
        rgbLed.turnOnColor("red");

        // Сразу вызываем функцию для долгого нажатия
        handleLongPress();
    }
}

void ButtonHandler::handleShortPress() {
#ifdef DEBUG
    Serial.println(F("Handling short press: turning on green LED."));
#endif
    rgbLed.turnOnColor("green");
    uint32_t startMillis = millis();
    while (millis() - startMillis < 50) {
        // Неблокирующая задержка
    }
    rgbLed.off();
}

void ButtonHandler::handleMediumPress() {
#ifdef DEBUG
    Serial.println(F("Handling medium press: toggling blue LED."));
#endif
    uint32_t startMillis = millis(); // Начальное время
    bool ledOn = false;

    while (millis() - startMillis < 30000) { // Проверяем общее время с начала
        static uint32_t lastToggleTime = 0;

        if (millis() - lastToggleTime >= 500) { // Проверяем каждые 500 мс
            ledOn = !ledOn;
            if (ledOn) {
                rgbLed.turnOnColor("blue");
            } else {
                rgbLed.turnOffColor("blue");
            }
            lastToggleTime = millis(); // Обновляем последнее время переключения
        }
    }

    // Выключаем все светодиоды после выхода из "режима программирования"
    rgbLed.off();
}

void ButtonHandler::handleLongPress() {
#ifdef DEBUG
    Serial.println(F("Handling long press: clearing EEPROM and cycling through LEDs."));
#endif

    // Выключаем все светодиоды перед началом долгого нажатия
    rgbLed.off();

    // Включаем только красный светодиод для индикации начала процесса
    rgbLed.turnOnColor("red");

    eepromHandler.clearEEPROM();

    rgbLed.turnOnColor("blue");

#ifdef DEBUG
    Serial.println(F("Simulating flashing for firmware process..."));
#endif

    // Симуляция процесса "прошивки" путем быстрого мигания светодиода
    uint32_t startMillis = millis();
    while (millis() - startMillis < 4000) { // "Прошиваем" в течение 4 секунд
        rgbLed.turnOnColor("blue");
        delay(50);  // Включение на 50 миллисекунд
        rgbLed.turnOffColor("blue");
        delay(50);  // Выключение на 50 миллисекунд
    }

    // Выключаем все светодиоды перед сбросом устройства
    rgbLed.off();

#ifdef DEBUG
    Serial.println(F("Resetting device now..."));
#endif

    resetDevice();
}

void ButtonHandler::resetDevice() {
#ifdef DEBUG
    Serial.println(F("Resetting device."));
#endif
    wdt_enable(WDTO_15MS);
    while (true);
}
