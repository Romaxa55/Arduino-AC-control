#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLed {
public:
    RGBLed(uint8_t rPin, uint8_t gPin, uint8_t bPin); // Конструктор класса с меньшими типами данных

    void setColor(uint8_t redValue, uint8_t greenValue, uint8_t blueValue); // Установка цвета с меньшими типами данных
    void off(); // Выключение всех светодиодов
    void turnOnColor(const char* color); // Включение заданного цвета
    void turnOffColor(const char* color); // Выключение заданного цвета

private:
    const uint8_t redPin;   // Используем uint8_t для пинов
    const uint8_t greenPin;
    const uint8_t bluePin;
    bool redState;   // Состояние красного светодиода
    bool greenState; // Состояние зеленого светодиода
    bool blueState;  // Состояние синего светодиода

    void updateLED(); // Приватный метод для обновления состояния светодиода
};

#endif // RGBLED_H
