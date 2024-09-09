#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLed {
private:
    int redPin;    // Пин для красного цвета
    int greenPin;  // Пин для зеленого цвета
    int bluePin;   // Пин для синего цвета

public:
    RGBLed(int rPin, int gPin, int bPin); // Конструктор класса

    void setColor(int redValue, int greenValue, int blueValue); // Метод для установки цвета
    void red();   // Метод для включения красного цвета
    void green(); // Метод для включения зеленого цвета
    void blue();  // Метод для включения синего цвета
    void white(); // Метод для включения белого цвета
    void off();   // Метод для выключения светодиода
};

#endif // RGBLED_H
