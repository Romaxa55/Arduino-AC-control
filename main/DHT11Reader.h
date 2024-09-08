#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>  // Используем библиотеку для работы с DHT11
#include "config.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>  // Подключаем библиотеку для работы с Watchdog Timer

class DHT11Reader {
public:
    DHT11Reader(uint8_t dataPin, uint8_t powerPin);
    void initialize();
    bool isSensorAvailable();
    void readAndPrintData();
    void enterSleepMode();
    void disableModules();
    bool sensorAvailable;

    // Геттеры для получения температуры и влажности
    int getTemperature() const;
    int getHumidity() const;

    // Сеттеры для установки температуры и влажности
    void setTemperature(int temp);
    void setHumidity(int hum);


private:
    DHT11 dht11;  // Объект библиотеки DHT11 для работы с датчиком
    int temperature;
    int humidity;
    uint8_t powerPin;
    void powerOn();
    void powerOff();
    bool readData();
};

#endif // DHT11READER_H
