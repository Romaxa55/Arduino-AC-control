#include "ErrorIndicator.h"
#include "config.h" // Подключаем конфигурационный файл

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
            blink(1, 0, 30, 200, 0, 800);  // Один короткий всплеск повторяется каждую секунду в течение 30 секунд
            break;
        case SENSOR_ERROR:
            blink(0, 5, 3, 0, 1000, 4000); // 5 длинных вспышек, повторяем каждую серию через 5 секунд
            break;
        case INITIALIZATION_ERROR:
            blink(3, 3, 3, 200, 1000, 3000); // Ошибка инициализации: 3 коротких, 3 длинных, 3 коротких
            break;
        case SLEEP_ERROR:
            blink(2, 2, 5, 200, 1000, 200); // Ошибка сна: 2 длинных, 2 коротких, 1 длинная
            break;
    }
}

// Оптимизированная универсальная функция для мигания с использованием битовых сдвигов
void ErrorIndicator::blink(uint8_t shortBlinks, uint8_t longBlinks, uint8_t repeats, uint16_t shortDelay, uint16_t longDelay, uint16_t pauseDelay) {
uint8_t shortDelayShifted = shortDelay >> 1; // Оптимизация: использование битового сдвига для деления задержки на 2
uint8_t longDelayShifted = longDelay >> 1;   // Оптимизация: деление на 2 с помощью битового сдвига

for (uint8_t repeat = 0; repeat < repeats; ++repeat) {
// Короткие вспышки
for (uint8_t i = 0; i < shortBlinks; ++i) {
digitalWrite(ledPin, HIGH);
delay(shortDelayShifted << 1);  // Восстанавливаем оригинальное значение сдвигом влево
digitalWrite(ledPin, LOW);
delay(shortDelayShifted << 1);  // Восстанавливаем оригинальное значение сдвигом влево
}
// Длинные вспышки
for (uint8_t i = 0; i < longBlinks; ++i) {
digitalWrite(ledPin, HIGH);
delay(longDelayShifted << 1);   // Восстанавливаем оригинальное значение сдвигом влево
digitalWrite(ledPin, LOW);
delay(shortDelayShifted << 1);  // Восстанавливаем оригинальное значение сдвигом влево
}
delay(pauseDelay); // Пауза перед следующей серией миганий
}
}
