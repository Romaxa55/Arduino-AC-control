#ifndef DHT11READER_H
#define DHT11READER_H

#include <Arduino.h>
#include <DHT11.h>  // Используем библиотеку для работы с DHT11
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>  // Подключаем библиотеку для работы с Watchdog Timer

class DHT11Reader {
public:
    DHT11Reader(uint8_t dataPin, uint8_t powerPin); // Конструктор с инициализацией пинов
    void initialize(); // Метод для инициализации датчика
    void run(); // Метод для запуска процесса опроса датчика
    void readAndPrintData(); // Метод для чтения данных и вывода их в Serial
    void disableModules(); // Метод для отключения неиспользуемых модулей
    bool isSensorAvailable(); // Метод для проверки доступности датчика
    bool sensorAvailable; // Публичная переменная для хранения состояния датчика

    // Геттеры для получения температуры и влажности
    int getTemperature() const;
    int getHumidity() const;

    // Сеттеры для установки температуры и влажности
    void setTemperature(int temp);
    void setHumidity(int hum);

private:
    DHT11 dht11;  // Объект библиотеки DHT11 для работы с датчиком
    int temperature; // Переменная для хранения температуры
    int humidity; // Переменная для хранения влажности
    uint8_t powerPin; // Пин управления питанием датчика

    unsigned long lastReadTime; // Время последнего чтения данных
    const unsigned long readInterval = 60000; // Интервал опроса датчика в миллисекундах

    void powerOn(); // Метод для включения питания датчика
    void powerOff(); // Метод для отключения питания датчика
    bool readData(); // Приватный метод для чтения данных с датчика
    void update(); // Метод для неблокирующего опроса
};

#endif // DHT11READER_H
