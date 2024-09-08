#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLed {
private:
    int redPin;    // Пин для красного цвета
    int greenPin;  // Пин для зеленого цвета
    int bluePin;   // Пин для синего цвета

public:
    // Конструктор класса
    RGBLed(int rPin, int gPin, int bPin) {
        redPin = rPin;
        greenPin = gPin;
        bluePin = bPin;

        // Устанавливаем пины как выходы
        pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
    }

    // Метод для установки цвета
    void setColor(int redValue, int greenValue, int blueValue) {
        analogWrite(redPin, redValue);
        analogWrite(greenPin, greenValue);
        analogWrite(bluePin, blueValue);
    }

    // Метод для включения красного цвета
    void red() {
        setColor(255, 0, 0); // Максимальная яркость красного
    }

    // Метод для включения зеленого цвета
    void green() {
        setColor(0, 255, 0); // Максимальная яркость зеленого
    }

    // Метод для включения синего цвета
    void blue() {
        setColor(0, 0, 255); // Максимальная яркость синего
    }

    // Метод для выключения светодиода
    void off() {
        setColor(0, 0, 0); // Выключаем все цвета
    }
};

#endif // RGBLED_H
