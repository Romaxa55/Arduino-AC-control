#include "LED.h"
#include <Arduino.h>

LED::LED(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT); // Настраиваем пин как выход
    isOn = false; // Начальное состояние - выключено
}

void LED::on() {
    digitalWrite(ledPin, HIGH); // Включаем светодиод
    isOn = true;
}

void LED::off() {
    digitalWrite(ledPin, LOW); // Выключаем светодиод
    isOn = false;
}

void LED::toggle() {
    if (isOn) {
        off(); // Если включен, выключаем
    } else {
        on(); // Если выключен, включаем
    }
}

void LED::blink(int duration) {
    on();
    delay(duration);
    off();
    delay(duration);
}
