#include "RGBLed.h"
#include "config.h"

// Конструктор класса
RGBLed::RGBLed(uint8_t rPin, uint8_t gPin, uint8_t bPin)
: redPin(rPin), greenPin(gPin), bluePin(bPin),
redState(false), greenState(false), blueState(false) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

// Метод для установки цвета
void RGBLed::setColor(uint8_t redValue, uint8_t greenValue, uint8_t blueValue) {
analogWrite(redPin, redValue);
analogWrite(greenPin, greenValue);
analogWrite(bluePin, blueValue);
}

// Метод для выключения всех светодиодов
void RGBLed::off() {
    setColor(0, 0, 0);
    redState = greenState = blueState = false;
}

// Метод для включения заданного цвета
void RGBLed::turnOnColor(const char* color) {
    if (strcmp(color, "red") == 0 && !redState) {
        redState = true;
    } else if (strcmp(color, "green") == 0 && !greenState) {
        greenState = true;
    } else if (strcmp(color, "blue") == 0 && !blueState) {
        blueState = true;
    }
    updateLED();
}

// Метод для выключения заданного цвета
void RGBLed::turnOffColor(const char* color) {
    if (strcmp(color, "red") == 0 && redState) {
        redState = false;
    } else if (strcmp(color, "green") == 0 && greenState) {
        greenState = false;
    } else if (strcmp(color, "blue") == 0 && blueState) {
        blueState = false;
    }
    updateLED();
}

// Приватный метод для обновления состояния светодиода
void RGBLed::updateLED() {
    setColor(redState ? 255 : 0, greenState ? 255 : 0, blueState ? 255 : 0);
}
