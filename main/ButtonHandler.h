#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h> // Включаем библиотеку Arduino для использования базовых функций и типов данных

class ButtonHandler {
public:
    // Конструктор класса ButtonHandler, принимает пин кнопки
    ButtonHandler(uint8_t pin);

    // Метод обновления состояния кнопки, вызывается в основном цикле программы
    void update();

private:
    uint8_t buttonPin;            // Пин кнопки
    uint32_t buttonPressTime;     // Время начала нажатия кнопки
    bool buttonPressed;           // Флаг состояния кнопки (нажата или нет)
    bool actionTriggered;         // Флаг выполнения действия (короткое, среднее или долгое нажатие)

    uint32_t lastDebounceTime;    // Время последнего изменения состояния кнопки
    uint8_t debounceDelay;        // Задержка для устранения дребезга кнопки

    // Метод для индикации текущего состояния нажатия кнопки
    void indicatePressDuration(uint32_t currentMillis);

    // Методы для обработки различных типов нажатий кнопки
    void handleShortPress();  // Обработка короткого нажатия
    void handleMediumPress(); // Обработка среднего нажатия
    void handleLongPress();   // Обработка долгого нажатия

    // Метод для сброса устройства с помощью Watchdog Timer
    void resetDevice();

    // Вспомогательные методы для управления светодиодами
    void switchColor(const char* color, uint16_t duration = 0); // Переключение цвета светодиода
    void toggleLed(const char* color, uint16_t interval, uint16_t duration); // Мигание светодиодом
    void flashLed(const char* color, uint16_t interval, uint16_t duration);  // Быстрое мигание светодиодом (эффект "прошивки")

    // Вспомогательная функция для логирования отладочных сообщений
    void logDebug(const __FlashStringHelper* message);

    // Вспомогательная функция для обработки действий при отпускании кнопки
    void processButtonRelease(uint32_t pressDuration);
};

#endif // BUTTONHANDLER_H
