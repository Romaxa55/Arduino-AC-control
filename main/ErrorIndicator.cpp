#include "ErrorIndicator.h"

// Конструктор с инициализацией пина индикатора
ErrorIndicator::ErrorIndicator(uint8_t ledPin) : ledPin(ledPin), currentError(NO_ERROR) {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Отключаем светодиод при старте
}

// Установка типа ошибки
void ErrorIndicator::setError(ErrorType errorType) {
    currentError = errorType;
}

// Запуск индикации текущей ошибки
void ErrorIndicator::indicateError() {
    switch (currentError) {
        case NO_ERROR:
            blinkNoError();
            break;
        case SENSOR_ERROR:
            blinkSensorError();
            break;
        case INITIALIZATION_ERROR:
            blinkInitializationError();
            break;
        case SLEEP_ERROR:
            blinkSleepError();
            break;
    }
}

// Приватные методы для мигания в зависимости от типа ошибки
void ErrorIndicator::blinkNoError() {
    // Один короткий всплеск повторяется каждую секунду в течение 30 секунд
    for (int i = 0; i < 30; i++) {
        digitalWrite(ledPin, HIGH);
        arduino.delay(200); // Короткая вспышка - 0.2 секунды
        digitalWrite(ledPin, LOW);
        arduino.delay(800); // Интервал до следующего мигания - 0.8 секунды
    }
}

void ErrorIndicator::blinkSensorError() {
    // Сенсорная ошибка: 5 длинных вспышек, повторяем каждую серию через 5 секунд
    for (int repeat = 0; repeat < 3; repeat++) { // 3 серии по 5 вспышек (3 * 10 секунд = 30 секунд)
        for (int i = 0; i < 5; i++) {
            digitalWrite(ledPin, HIGH);
            arduino.delay(1000);   // Длинная вспышка - 1 секунда
            digitalWrite(ledPin, LOW);
            arduino.delay(200);   // Интервал между вспышками - 0.2 секунды
        }
        arduino.delay(4000); // Пауза перед следующей серией - 4 секунды
    }
}

void ErrorIndicator::blinkInitializationError() {
    // Ошибка инициализации: 3 коротких, 3 длинных, 3 коротких (повторяем каждую серию каждые 10 секунд)
    for (int repeat = 0; repeat < 3; repeat++) { // 3 серии по 10 секунд (3 * 10 секунд = 30 секунд)
        for (int i = 0; i < 3; i++) {
            digitalWrite(ledPin, HIGH);
            arduino.delay(200);  // Короткая вспышка - 0.2 секунды
            digitalWrite(ledPin, LOW);
            arduino.delay(200);  // Интервал между вспышками - 0.2 секунды
        }
        for (int i = 0; i < 3; i++) {
            digitalWrite(ledPin, HIGH);
            arduino.delay(1000);  // Длинная вспышка - 1 секунда
            digitalWrite(ledPin, LOW);
            arduino.delay(200);   // Интервал между вспышками - 0.2 секунды
        }
        for (int i = 0; i < 3; i++) {
            digitalWrite(ledPin, HIGH);
            arduino.delay(200);  // Короткая вспышка - 0.2 секунды
            digitalWrite(ledPin, LOW);
            arduino.delay(200);  // Интервал между вспышками - 0.2 секунды
        }
        arduino.delay(3000); // Пауза перед следующей серией - 3 секунды
    }
}

void ErrorIndicator::blinkSleepError() {
    // Ошибка сна: 2 длинных, 2 коротких, 1 длинная, повторяем каждую серию каждые 6 секунд
    for (int repeat = 0; repeat < 5; repeat++) { // 5 серий по 6 секунд (5 * 6 секунд = 30 секунд)
        for (int i = 0; i < 2; i++) {
            digitalWrite(ledPin, HIGH);
            arduino.delay(1000);  // Длинная вспышка - 1 секунда
            digitalWrite(ledPin, LOW);
            arduino.delay(200);   // Интервал между вспышками - 0.2 секунды
        }
        for (int i = 0; i < 2; i++) {
            digitalWrite(ledPin, HIGH);
            arduino.delay(200);   // Короткая вспышка - 0.2 секунды
            digitalWrite(ledPin, LOW);
            arduino.delay(200);   // Интервал между вспышками - 0.2 секунды
        }
        digitalWrite(ledPin, HIGH);
        arduino.delay(1000);  // Одна длинная вспышка - 1 секунда
        digitalWrite(ledPin, LOW);
        arduino.delay(1000); // Пауза перед повторением - 1 секунда
    }
}
