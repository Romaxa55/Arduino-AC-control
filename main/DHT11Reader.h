#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

class DHT11Reader {
public:
    DHT11Reader(uint8_t dataPin, uint8_t powerPin); // Конструктор класса
    void initialize(); // Инициализация датчика
    void run(); // Запуск процесса опроса
    void disableModules(); // Отключение неиспользуемых модулей
    bool isSensorAvailable() const; // Проверка доступности датчика

    int getTemperature() const; // Геттер для температуры
    int getHumidity() const;    // Геттер для влажности

private:
    DHT11 dht11;               // Объект датчика DHT11
    int8_t temperature;        // Температура, экономия памяти с использованием int8_t
    uint8_t humidity;          // Влажность

    uint8_t powerPin;          // Пин управления питанием

    struct {
        bool sensorAvailable : 1; // Флаг доступности датчика (битовое поле)
    } flags;

    unsigned long lastReadTime; // Время последнего чтения
    static constexpr unsigned long readInterval = 60000; // Интервал опроса

    void managePower(bool on); // Управление питанием датчика
    bool readData(); // Чтение данных с датчика
};

#endif // DHT11READER_H
