#include "config.h"

// Конструктор класса
RGBLed::RGBLed(int rPin, int gPin, int bPin) {
    redPin = rPin;
    greenPin = gPin;
    bluePin = bPin;

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

// Метод для установки цвета
void RGBLed::setColor(int redValue, int greenValue, int blueValue) {
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
}

// Метод для включения красного цвета
void RGBLed::red() {
    setColor(255, 0, 0);
}

// Метод для включения зеленого цвета
void RGBLed::green() {
    setColor(0, 255, 0);
}

// Метод для включения синего цвета
void RGBLed::blue() {
    setColor(0, 0, 255);
}

// Метод для включения белого цвета
void RGBLed::white() {
    setColor(255, 255, 255);
}

// Метод для выключения светодиода
void RGBLed::off() {
    setColor(0, 0, 0);
}
