#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLed {
public:
    RGBLed(int rPin, int gPin, int bPin); // Конструктор класса

    void setColor(int redValue, int greenValue, int blueValue); // Установка цвета
    void off(); // Выключение всех светодиодов
    void turnOnColor(const char* color); // Включение заданного цвета
    void turnOffColor(const char* color); // Выключение заданного цвета

private:
    int redPin;
    int greenPin;
    int bluePin;
    bool redState;   // Состояние красного светодиода
    bool greenState; // Состояние зеленого светодиода
    bool blueState;  // Состояние синего светодиода

    void updateLED(); // Приватный метод для обновления состояния светодиода
};

#endif // RGBLED_H
