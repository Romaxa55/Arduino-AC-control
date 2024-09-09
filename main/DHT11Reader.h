#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

class DHT11Reader {
public:
    DHT11Reader(uint8_t dataPin, uint8_t powerPin);
    void initialize();
    void run();
    void disableModules();
    bool isSensorAvailable() const;

    int getTemperature() const;
    int getHumidity() const;

private:
    DHT11 dht11;
    int8_t temperature; // Используем int8_t, так как значения температуры обычно лежат в пределах -128..127
    uint8_t humidity;   // Используем uint8_t, так как значения влажности лежат в пределах 0..100
    uint8_t powerPin;

    // Используем битовые поля для экономии памяти
    struct {
        bool sensorAvailable : 1; // Переменная состояния датчика
        unsigned int unused : 7;  // Заполняем оставшиеся биты до целого байта (необязательно)
    } flags;

    unsigned long lastReadTime;
    static constexpr unsigned long readInterval = 10000;

    void powerOn();
    void powerOff();
    bool readData();
};

#endif // DHT11READER_H
