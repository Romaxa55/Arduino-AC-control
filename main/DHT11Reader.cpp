#include "DHT11Reader.h"

// Конструктор с инициализацией датчика
DHT11Reader::DHT11Reader(uint8_t pin) : dht11(pin), temperature(0), humidity(0) {}

// Приватный метод для чтения данных с датчика
bool DHT11Reader::readData() {
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    return result == 0; // Возвращает true, если чтение успешно
}

// Метод для вывода данных в Serial
void DHT11Reader::printData() {
    if (readData()) {
        Serial.print(F("Temperature: "));
        Serial.print(temperature);
        Serial.print(F(" °C\tHumidity: "));
        Serial.print(humidity);
        Serial.println(F(" %"));
    } else {
        Serial.println(F("Failed to read from DHT11 sensor."));
    }
}
