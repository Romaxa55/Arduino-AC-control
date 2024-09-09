#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h>

class ButtonHandler {
public:
    ButtonHandler(uint8_t pin); // Конструктор, принимает пин кнопки
    void update(); // Метод для обновления состояния кнопки
    void setShortPressAction(void (*action)()); // Устанавливает действие при коротком нажатии
    void setMediumPressAction(void (*action)()); // Устанавливает действие при среднем нажатии
    void setLongPressAction(void (*action)()); // Устанавливает действие при длинном нажатии

private:
    uint8_t buttonPin; // Пин кнопки
    unsigned long buttonPressTime; // Время начала нажатия
    bool buttonPressed; // Состояние кнопки
    bool actionTriggered; // Флаг выполнения действия

    // Указатели на функции для различных действий
    void (*shortPressAction)();
    void (*mediumPressAction)();
    void (*longPressAction)();
};

#endif // BUTTONHANDLER_H
