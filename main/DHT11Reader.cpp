#include "DHT11Reader.h"
#include "config.h"
#include <avr/wdt.h>

DHT11Reader::DHT11Reader(uint8_t dataPin, uint8_t powerPin)
: dht11(dataPin), temperature(0), humidity(0), powerPin(powerPin), lastReadTime(0) {
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);
    flags.sensorAvailable = false; // Устанавливаем флаг
}

void DHT11Reader::initialize() {
    Serial.println(F("Initializing DHT11 sensor..."));
    powerOn();
    delay(200);

    if (readData()) {
        flags.sensorAvailable = true;
        Serial.println(F("DHT11 sensor initialized successfully."));
    } else {
        flags.sensorAvailable = false;
        Serial.println(F("DHT11 sensor is not available at startup."));
    }
    powerOff();
}

void DHT11Reader::run() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastReadTime >= readInterval) {
        lastReadTime = currentMillis;
        Serial.println(F("Reading data from DHT11..."));
        if (flags.sensorAvailable && !readData()) {
            Serial.println(F("Error reading data from DHT11."));
        }
    }
}

void DHT11Reader::powerOn() {
    digitalWrite(powerPin, HIGH);
    delay(200);
}

void DHT11Reader::powerOff() {
    digitalWrite(powerPin, LOW);
}

bool DHT11Reader::readData() {
    powerOn();
    delay(2000);

    int temp, hum; // Создаем временные переменные типа int для хранения данных

    int result = dht11.readTemperatureHumidity(temp, hum); // Используем переменные правильного типа
    powerOff();

    if (result != 0) {
        Serial.println(F("Failed to read from DHT11 sensor."));
        return false;
    }

    temperature = static_cast<int8_t>(temp - 5); // Коррекция температуры и приведение к типу int8_t
    humidity = static_cast<uint8_t>(hum); // Приведение к типу uint8_t

    Serial.print(F("Temperature (corrected): "));
    Serial.print(temperature);
    Serial.print(F(" °C, Humidity: "));
    Serial.print(humidity);
    Serial.println(F(" %"));

    return true;
}

void DHT11Reader::disableModules() {
    ADCSRA &= ~(1 << ADEN);

    power_spi_disable();
    power_twi_disable();

    power_timer1_disable();
    power_timer2_disable();
}

int DHT11Reader::getTemperature() const {
    return temperature;
}

int DHT11Reader::getHumidity() const {
    return humidity;
}

bool DHT11Reader::isSensorAvailable() const {
    return flags.sensorAvailable;
}
