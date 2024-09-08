#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>  // Убедись, что библиотека DHT11 установлена

class DHT11Reader {
public:
    // Конструктор с инициализацией и началом работы с датчиком
    DHT11Reader(uint8_t pin);

    // Метод для получения температуры и влажности и вывода их в Serial
    void printData();

private:
    DHT11 dht11; // Экземпляр датчика
    int temperature;
    int humidity;

    // Метод для чтения данных с датчика
    bool readData();
};

#endif
