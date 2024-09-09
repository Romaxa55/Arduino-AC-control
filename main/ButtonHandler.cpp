#include "ButtonHandler.h"
#include "config.h" // Подключаем конфигурационный файл

ButtonHandler::ButtonHandler(uint8_t pin) : buttonPin(pin), buttonPressTime(0), buttonPressed(false), actionTriggered(false) {
    pinMode(buttonPin, INPUT_PULLUP); // Настраиваем кнопку на вход с подтяжкой к питанию
    shortPressAction = nullptr;
    mediumPressAction = nullptr;
    longPressAction = nullptr;
}

void ButtonHandler::update() {
    if (digitalRead(buttonPin) == LOW) { // Кнопка нажата
        if (!buttonPressed) { // Начало нажатия
            buttonPressed = true;
            buttonPressTime = millis(); // Записываем время начала нажатия
            actionTriggered = false; // Сбрасываем флаг выполнения действия
        }

        unsigned long pressDuration = millis() - buttonPressTime; // Рассчитываем продолжительность нажатия

        if (pressDuration >= 10000 && !actionTriggered) { // Если держим 10 секунд
            if (longPressAction) longPressAction();
            actionTriggered = true;
        } else if (pressDuration >= 5000 && !actionTriggered) { // Если держим 5 секунд
            if (mediumPressAction) mediumPressAction();
            actionTriggered = true;
        }
    } else { // Кнопка отпущена
        if (buttonPressed && !actionTriggered) { // Если кнопка была нажата и действие не выполнено
            unsigned long pressDuration = millis() - buttonPressTime; // Рассчитываем продолжительность нажатия
            if (pressDuration < 5000) { // Короткое нажатие (меньше 5 секунд)
                if (shortPressAction) shortPressAction();
            }
        }
        buttonPressed = false; // Сбрасываем состояние кнопки
    }
}

void ButtonHandler::setShortPressAction(void (*action)()) {
    shortPressAction = action;
}

void ButtonHandler::setMediumPressAction(void (*action)()) {
    mediumPressAction = action;
}

void ButtonHandler::setLongPressAction(void (*action)()) {
    longPressAction = action;
}
