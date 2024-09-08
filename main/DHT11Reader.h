#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>  // Библиотека для работы с датчиком DHT11
#include "config.h"  // Подключаем заголовочный файл с определением DEBUG
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>  // Подключаем библиотеку для работы с Watchdog Timer

class DHT11Reader {
public:
    // Конструктор с инициализацией датчика и управления питанием
    DHT11Reader(uint8_t dataPin, uint8_t powerPin);

    // Метод для инициализации датчика
    void initialize();

    // Метод для получения и вывода температуры и влажности
    void readAndPrintData();

    // Метод для перехода в режим сна
    void enterSleepMode();

    // Метод для отключения неиспользуемых модулей
    void disableModules();

    bool isSensorAvailable(); // Метод для проверки доступности датчика

private:
    DHT11 dht11;  // Экземпляр датчика
    int temperature;
    int humidity;
    uint8_t powerPin;  // Пин для управления питанием датчика
    bool sensorAvailable; // Флаг для проверки доступности датчика

    // Приватный метод для чтения данных с датчика
    bool readData();

    // Приватные методы для включения и отключения питания датчика
    void powerOn();
    void powerOff();
};

#endif // DHT11READER_H
