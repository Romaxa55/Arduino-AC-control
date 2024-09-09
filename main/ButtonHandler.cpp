#include "ButtonHandler.h"
#include "config.h"
#include <avr/wdt.h>

// Константы для различных временных интервалов нажатий
const uint16_t SHORT_PRESS_DURATION = 5000;   // Короткое нажатие - менее 5 секунд
const uint16_t MEDIUM_PRESS_DURATION = 10000; // Среднее нажатие - от 5 до 10 секунд
const uint16_t LONG_PRESS_DURATION = 30000;   // Длинное нажатие - более 10 секунд

// Конструктор класса ButtonHandler
ButtonHandler::ButtonHandler(uint8_t pin)
        : buttonPin(pin), buttonPressTime(0), buttonPressed(false), actionTriggered(false),
          lastDebounceTime(0), debounceDelay(50) {
    pinMode(buttonPin, INPUT_PULLUP); // Настройка пина кнопки как вход с подтяжкой к питанию
}

// Метод обновления состояния кнопки
void ButtonHandler::update() {
    uint32_t currentMillis = millis(); // Получаем текущее время

    // Проверяем состояние кнопки (нажата или нет)
    if (digitalRead(buttonPin) == LOW) { // Кнопка нажата
        if (!buttonPressed) { // Первое нажатие
            buttonPressed = true;
            buttonPressTime = currentMillis; // Запоминаем время нажатия
            actionTriggered = false; // Сбрасываем флаг выполнения действия
            logDebug(F("Button pressed.")); // Логируем отладочное сообщение
        }

        indicatePressDuration(currentMillis); // Обновляем индикацию состояния нажатия

    } else if (buttonPressed) { // Кнопка отпущена
        processButtonRelease(currentMillis - buttonPressTime); // Определяем действие на основе длительности нажатия
        buttonPressed = false; // Сбрасываем состояние кнопки
    }
}

// Метод для индикации текущего состояния нажатия кнопки
void ButtonHandler::indicatePressDuration(uint32_t currentMillis) {
    uint32_t pressDuration = currentMillis - buttonPressTime; // Определяем длительность нажатия

    if (pressDuration < SHORT_PRESS_DURATION) {
        // Включаем зеленый светодиод, выключаем остальные
        rgbLed.turnOnColor("green");
        rgbLed.turnOffColor("blue");
        rgbLed.turnOffColor("red");
    } else if (pressDuration < MEDIUM_PRESS_DURATION) {
        // Включаем синий светодиод, выключаем остальные
        rgbLed.turnOffColor("green");
        rgbLed.turnOnColor("blue");
        rgbLed.turnOffColor("red");
    } else {
        // Включаем красный светодиод, выключаем остальные
        rgbLed.turnOffColor("green");
        rgbLed.turnOffColor("blue");
        rgbLed.turnOnColor("red");
        handleLongPress(); // Сразу выполняем действие для долгого нажатия
    }
}

// Метод для обработки короткого нажатия кнопки
void ButtonHandler::handleShortPress() {
    logDebug(F("Handling short press: turning on green LED."));
    switchColor("green", 50); // Включаем зеленый светодиод на 50 миллисекунд
}

// Метод для обработки среднего нажатия кнопки
void ButtonHandler::handleMediumPress() {
    logDebug(F("Handling medium press: toggling blue LED."));
    toggleLed("blue", 500, 30000); // Мигание синим светодиодом каждые 500 миллисекунд в течение 30 секунд
}

// Метод для обработки долгого нажатия кнопки
void ButtonHandler::handleLongPress() {
    logDebug(F("Handling long press: clearing EEPROM and simulating flashing process."));

    eepromHandler.clearEEPROM(); // Очищаем EEPROM

    logDebug(F("Simulating flashing for firmware process..."));
    flashLed("blue", 50, 4000); // Эффект "прошивки" синим светодиодом в течение 4 секунд

    resetDevice(); // Сбрасываем устройство
}

// Метод для сброса устройства с использованием Watchdog Timer
void ButtonHandler::resetDevice() {
    logDebug(F("Resetting device."));
    wdt_enable(WDTO_15MS); // Активируем Watchdog Timer для сброса устройства через 15 миллисекунд
    while (true); // Ждем сброса
}

// Вспомогательная функция для включения светодиода указанного цвета
void ButtonHandler::switchColor(const char* color, uint16_t duration) {
    rgbLed.off(); // Выключаем все светодиоды
    rgbLed.turnOnColor(color); // Включаем светодиод указанного цвета
    if (duration > 0) delay(duration); // Если задана длительность, ждем указанное время
    rgbLed.off(); // Выключаем светодиоды после указанного времени
}

// Вспомогательная функция для мигания светодиодом указанного цвета
void ButtonHandler::toggleLed(const char* color, uint16_t interval, uint16_t duration) {
    uint32_t startMillis = millis();
    bool ledOn = false;

    while (millis() - startMillis < duration) { // Пока длительность не превышена
        if (millis() % interval == 0) { // Каждые 'interval' миллисекунд
            ledOn = !ledOn;
            ledOn ? rgbLed.turnOnColor(color) : rgbLed.turnOffColor(color); // Переключаем светодиод
        }
    }

    rgbLed.off(); // Выключаем светодиоды по окончании мигания
}

// Вспомогательная функция для быстрого мигания светодиодом (эффект "прошивки")
void ButtonHandler::flashLed(const char* color, uint16_t interval, uint16_t duration) {
    uint32_t startMillis = millis();
    while (millis() - startMillis < duration) { // Пока длительность не превышена
        rgbLed.turnOnColor(color);
        delay(interval); // Включаем светодиод на короткое время
        rgbLed.turnOffColor(color);
        delay(interval); // Выключаем светодиод на короткое время
    }
    rgbLed.off();
}

// Вспомогательная функция для логирования отладочных сообщений
void ButtonHandler::logDebug(const __FlashStringHelper* message) {
#ifdef DEBUG
    Serial.println(message);
#endif
}

// Вспомогательная функция для определения действия при отпускании кнопки
void ButtonHandler::processButtonRelease(uint32_t pressDuration) {
    if (pressDuration < SHORT_PRESS_DURATION && !actionTriggered) {
        logDebug(F("Short press detected."));
        handleShortPress();
    } else if (pressDuration < MEDIUM_PRESS_DURATION && !actionTriggered) {
        logDebug(F("Medium press detected."));
        handleMediumPress();
    } else if (pressDuration >= MEDIUM_PRESS_DURATION && !actionTriggered) {
        logDebug(F("Long press detected."));
        // Убираем вызов handleLongPress(), так как он вызывается в indicatePressDuration()
    }
    actionTriggered = true; // Отмечаем, что действие выполнено
}
