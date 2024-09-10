#ifndef ERRORINDICATOR_H
#define ERRORINDICATOR_H

#include <Arduino.h>

// Определение различных типов ошибок
enum ErrorType {
    NO_ERROR,
    SENSOR_ERROR,
    INITIALIZATION_ERROR,
    SLEEP_ERROR
};

class ErrorIndicator {
public:
    // Конструктор с указанием пина для индикатора
    ErrorIndicator(const uint8_t ledPin);

    // Установка типа ошибки
    void setError(ErrorType errorType);

    // Запуск индикации текущей ошибки
    void indicateError();

    // Методы мигания
    void blinkNoError();
    void blinkSensorError();
    void blinkInitializationError();
    void blinkSleepError();

private:
    const uint8_t ledPin;        // Пин для управления светодиодом
    ErrorType currentError; // Текущий тип ошибки
};

#endif // ERRORINDICATOR_H
