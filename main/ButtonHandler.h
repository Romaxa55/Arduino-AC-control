#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h>

// Класс ButtonHandler для управления действиями по нажатию кнопки
class ButtonHandler {
public:
    // Конструктор класса, принимает пин кнопки
    ButtonHandler(uint8_t pin);

    // Метод обновления состояния кнопки, вызывается в основном цикле программы
    void update();

private:
    uint8_t buttonPin;            // Пин кнопки
    uint32_t buttonPressTime;     // Время начала нажатия кнопки
    uint8_t buttonPressed : 1;    // Флаг состояния кнопки (нажата или нет)
    uint8_t actionTriggered : 1;  // Флаг выполнения действия (для предотвращения повторных срабатываний)

    uint32_t lastDebounceTime;    // Время последнего изменения состояния кнопки
    uint16_t debounceDelay;       // Задержка для устранения дребезга кнопки

    // Метод для индикации длительности нажатия кнопки с помощью светодиодов
    void indicatePressDuration(uint32_t currentMillis);

    // Методы для обработки различных типов нажатий кнопки
    void handleShortPress();   // Обработка короткого нажатия (менее 5 секунд)
    void handleMediumPress();  // Обработка среднего нажатия (от 5 до 10 секунд)
    void handleLongPress();    // Обработка долгого нажатия (более 10 секунд)

    // Метод для выполнения сброса устройства с использованием Watchdog Timer
    void resetDevice();

    // Вспомогательные методы для управления светодиодами и логирования
    void switchColor(const char* color, uint16_t duration = 0); // Включение светодиода определенного цвета на заданное время
    void toggleLed(const char* color, uint16_t interval, uint16_t duration); // Мигание светодиодом определенного цвета
    void flashLed(const char* color, uint16_t interval, uint16_t duration); // Быстрое мигание светодиодом для "прошивки"
    void logDebug(const __FlashStringHelper* message); // Логирование отладочных сообщений
    void processButtonRelease(uint32_t pressDuration); // Обработка действий при отпускании кнопки
};

#endif // BUTTONHANDLER_H
