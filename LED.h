#ifndef LED_H
#define LED_H

class LED {
public:
    LED(int pin); // Конструктор, который принимает пин светодиода
    void on();    // Метод включения светодиода
    void off();   // Метод выключения светодиода
    void toggle(); // Метод переключения состояния
    void blink(int duration); // Метод мигания светодиода

private:
    int ledPin;   // Пин светодиода
    bool isOn;    // Текущее состояние светодиода
};

#endif
