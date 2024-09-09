#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h>

class ButtonHandler {
public:
    ButtonHandler(uint8_t pin); // Конструктор, принимает пин кнопки
    void update(); // Метод для обновления состояния кнопки и выполнения действий

private:
    uint8_t buttonPin; // Пин кнопки
    unsigned long buttonPressTime; // Время начала нажатия
    bool buttonPressed; // Состояние кнопки
    bool actionTriggered; // Флаг выполнения действия

    unsigned long lastDebounceTime; // Последнее время изменения состояния кнопки
    unsigned long debounceDelay; // Задержка для устранения дребезга

    void indicatePressDuration(unsigned long currentMillis); // Метод для индикации времени нажатия
    void handleShortPress(); // Метод для обработки короткого нажатия
    void handleMediumPress(); // Метод для обработки среднего нажатия
    void handleLongPress(); // Метод для обработки длинного нажатия
    void indicateStartOfClearing(); // Метод для индикации начала очистки EEPROM
    void indicateClearingCompleted(); // Метод для индикации завершения очистки EEPROM
    void resetDevice(); // Метод для перезагрузки устройства
};

#endif // BUTTONHANDLER_H
