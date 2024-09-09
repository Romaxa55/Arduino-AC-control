#include "DHT11Reader.h"
#include "config.h"
#include <avr/wdt.h>

// Конструктор класса DHT11Reader
DHT11Reader::DHT11Reader(uint8_t dataPin, uint8_t powerPin)
: dht11(dataPin), temperature(0), humidity(0), powerPin(powerPin), lastReadTime(0) {
    pinMode(powerPin, OUTPUT);  // Устанавливаем пин управления питанием как выход
    digitalWrite(powerPin, LOW); // Выключаем питание датчика при инициализации
    flags.sensorAvailable = false; // Инициализируем флаг доступности датчика
}

// Метод инициализации датчика DHT11
void DHT11Reader::initialize() {
    DEBUG_PRINT(F("Initializing DHT11 sensor..."));
    managePower(true); // Включаем питание датчика
    delay(200); // Ждем стабилизации

    if (readData()) {
        flags.sensorAvailable = true;
        DEBUG_PRINT(F("DHT11 sensor initialized successfully."));
    } else {
        flags.sensorAvailable = false;
        DEBUG_PRINT(F("DHT11 sensor is not available at startup."));
    }
    managePower(false); // Отключаем питание датчика
}

// Метод управления питанием датчика с использованием битовых операций
void DHT11Reader::managePower(bool on) {
    digitalWrite(powerPin, on ? HIGH : LOW);
    if (on) _delay_ms(200); // Задержка после включения питания
}

// Метод запуска процесса опроса датчика
void DHT11Reader::run() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastReadTime >= readInterval) {
        lastReadTime = currentMillis;
        DEBUG_PRINT(F("Reading data from DHT11..."));
        if (flags.sensorAvailable && !readData()) {
            DEBUG_PRINT(F("Error reading data from DHT11."));
        }
    }
}

// Метод чтения данных с датчика
bool DHT11Reader::readData() {
    managePower(true); // Включаем питание датчика
    _delay_ms(2000); // Ждем стабилизации

    int temp, hum; // Создаем временные переменные для хранения данных

    int result = dht11.readTemperatureHumidity(temp, hum); // Чтение данных с датчика
    managePower(false); // Отключаем питание датчика

    if (result != 0) {
        DEBUG_PRINT(F("Failed to read from DHT11 sensor."));
        return false;
    }

    temperature = static_cast<int8_t>(temp - 5); // Коррекция температуры
    humidity = static_cast<uint8_t>(hum); // Приведение к типу uint8_t

    DEBUG_PRINT(F("Temperature (corrected): "));
    DEBUG_PRINT(temperature);
    DEBUG_PRINT(F(" °C, Humidity: "));
    DEBUG_PRINT(humidity);
    DEBUG_PRINT(F(" %"));

    return true;
}

void DHT11Reader::disableModules() {
    ADCSRA &= ~(1 << ADEN);

    power_spi_disable();
    power_twi_disable();

    power_timer1_disable();
    power_timer2_disable();
}

int DHT11Reader::getTemperature() const { return temperature; }
int DHT11Reader::getHumidity() const { return humidity; }
bool DHT11Reader::isSensorAvailable() const { return flags.sensorAvailable; }
