#ifndef LED_H
#define LED_H

#include <Arduino.h> // Перенесено в заголовок для компактности

class LED {
public:
    LED(uint8_t pin); // Используем более компактный тип
    void on();
    void off();
    void toggle();
    void blink(uint16_t duration); // Используем 16-битный тип

private:
    uint8_t ledPin;   // Используем компактный тип для пина
    bool isOn;        // Состояние светодиода
};

#endif
