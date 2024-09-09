#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

class DHT11Reader {
public:
    DHT11Reader(uint8_t dataPin, uint8_t powerPin); // Конструктор, принимающий пины данных и питания
    void initialize(); // Метод для инициализации датчика
    void run(); // Метод для запуска процесса опроса датчика
    void disableModules(); // Метод для отключения неиспользуемых модулей

    inline bool isSensorAvailable() const { return flags.sensorAvailable; } // Инлайн-метод для проверки доступности датчика

    inline int getTemperature() const { return temperature; } // Инлайн-метод для получения температуры
    inline int getHumidity() const { return humidity; } // Инлайн-метод для получения влажности

private:
    DHT11 dht11; // Объект библиотеки DHT11 для работы с датчиком
    int8_t temperature; // Температура, сохраненная как знаковое целое
    uint8_t humidity; // Влажность, сохраненная как беззнаковое целое
    uint8_t powerPin; // Пин для управления питанием датчика
    unsigned long lastReadTime; // Время последнего опроса датчика
    static constexpr unsigned long readInterval = 60000; // Интервал опроса датчика (миллисекунды)

    struct {
        bool sensorAvailable : 1; // Битовое поле для флага доступности датчика
    } flags;

    void managePower(bool on); // Метод для управления питанием датчика
    bool readData(); // Метод для чтения данных с датчика
};

#endif // DHT11READER_H
