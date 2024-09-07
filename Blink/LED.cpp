#include "LED.h"

LED::LED(uint8_t pin) : ledPin(pin), isOn(false) {
    pinMode(ledPin, OUTPUT);
}

void LED::on() {
    digitalWrite(ledPin, HIGH);
    isOn = true;
}

void LED::off() {
    digitalWrite(ledPin, LOW);
    isOn = false;
}

void LED::toggle() {
    isOn ? off() : on();
}

void LED::blink(uint16_t duration) {
    on();
    delay(duration);
    off();
    delay(duration);
}
