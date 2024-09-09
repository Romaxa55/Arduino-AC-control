#ifndef ERRORINDICATOR_H
#define ERRORINDICATOR_H

#include <Arduino.h>

// Определение различных типов ошибок
enum ErrorType : uint8_t {
    NO_ERROR,
    SENSOR_ERROR,
    INITIALIZATION_ERROR,
    SLEEP_ERROR
};

class ErrorIndicator {
public:
    ErrorIndicator(uint8_t ledPin);

    void setError(ErrorType errorType); // Установка типа ошибки
    void indicateError(); // Запуск индикации текущей ошибки

private:
    uint8_t ledPin;        // Пин для управления светодиодом
    ErrorType currentError; // Текущий тип ошибки

    // Оптимизированная универсальная функция для мигания
    void blink(uint8_t shortBlinks, uint8_t longBlinks, uint8_t repeats, uint16_t shortDelay, uint16_t longDelay, uint16_t pauseDelay);
};

#endif // ERRORINDICATOR_H
