#include "config.h"

// Конструктор класса
CustomArduino::CustomArduino(unsigned long cpuFreq) {
    cpuFrequency = cpuFreq;  // Инициализация частоты
    delayCorrectionFactor = 8.0;  // Устанавливаем коэффициент коррекции, равный 8
}

// Обновленный метод delay с учетом деления на 8
void CustomArduino::delay(unsigned long ms) {
#ifdef USE_CUSTOM_DELAY  // Используем кастомную задержку, если макрос определен
    unsigned long adjustedMs = ms / delayCorrectionFactor; // Делим задержку на 8

    // Отладочный вывод
    Serial.print("Using custom delay... ");
    Serial.print("Original delay: ");
    Serial.print(ms);
    Serial.print(" ms, Adjusted delay: ");
    Serial.print(adjustedMs);
    Serial.println(" ms");

    // Цикл по миллисекундам
    for (unsigned long i = 0; i < adjustedMs; i++) {
        unsigned long start = micros();
        while (micros() - start < 1000UL) {  // 1 миллисекунда = 1,000 микросекунд
            // Пустой цикл ожидания
        }
    }
#else
    Serial.println("Using standard delay...");  // Отладочный вывод
    ::delay(ms);  // Используем стандартную функцию delay без коррекции
#endif
}
