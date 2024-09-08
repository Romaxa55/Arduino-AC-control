// CustomArduino.h
#ifndef CUSTOM_ARDUINO_H
#define CUSTOM_ARDUINO_H

#include <Arduino.h>

class CustomArduino {
public:
    CustomArduino(unsigned long cpuFreq = 16000000UL);  // Конструктор с указанием частоты процессора
    void delay(unsigned long ms);  // Кастомный метод задержки

private:
    unsigned long cpuFrequency;  // Частота процессора
    float delayCorrectionFactor; // Коэффициент коррекции задержки
};

#endif // CUSTOM_ARDUINO_H
