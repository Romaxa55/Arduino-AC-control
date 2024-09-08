#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>  // Убедись, что библиотека DHT11 установлена

class DHT11Reader {
public:
    // Конструктор с инициализацией датчика
    DHT11Reader(uint8_t pin);

    // Метод для получения и вывода температуры и влажности
    void printData();

private:
    DHT11 dht11; // Экземпляр датчика
    int temperature; // Используем int, так как метод библиотеки требует int
    int humidity;    // Используем int, так как метод библиотеки требует int

    // Приватный метод для чтения данных с датчика
    bool readData();
};

#endif
