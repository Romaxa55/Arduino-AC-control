#include "DHT11Reader.h"
#include "config.h"
#include <avr/wdt.h> // Подключаем библиотеку для работы с Watchdog Timer


DHT11Reader::DHT11Reader(uint8_t dataPin, uint8_t powerPin)
        : dht11(dataPin), temperature(0), humidity(0), powerPin(powerPin), sensorAvailable(false), lastReadTime(0) {
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW); // Отключаем питание датчика при инициализации
}

void DHT11Reader::initialize() {
    Serial.println("Initializing DHT11 sensor...");
    powerOn();
    delay(200);

    if (readData()) {
        sensorAvailable = true;
        Serial.println("DHT11 sensor initialized successfully.");
    } else {
        sensorAvailable = false;
        Serial.println("DHT11 sensor is not available at startup.");
    }
    powerOff();
}

// Новый метод для запуска процесса опроса
void DHT11Reader::run() {
    // Просто вызываем update() для проверки и опроса
    update();
}

void DHT11Reader::powerOn() {
    digitalWrite(powerPin, HIGH);
    delay(200); // Ждем 200 мс для стабилизации датчика
}

void DHT11Reader::powerOff() {
    digitalWrite(powerPin, LOW);
}

bool DHT11Reader::readData() {
    powerOn();
    delay(2000); // Ждем 2 секунды для стабилизации перед чтением

    int result = dht11.readTemperatureHumidity(temperature, humidity);
    powerOff();

    if (result != 0) {
        Serial.println("Failed to read from DHT11 sensor.");
        return false;
    }

    temperature -= 5;

    Serial.print("Temperature (corrected): ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    return true;
}

void DHT11Reader::update() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastReadTime >= readInterval) { // Проверяем, прошло ли время для нового чтения
        lastReadTime = currentMillis; // Обновляем время последнего чтения
        Serial.println("Reading data from DHT11...");
        readAndPrintData();
    }
}

void DHT11Reader::readAndPrintData() {
    if (!sensorAvailable) {
        Serial.println("Skipping data read; sensor is not available.");
        return;
    }

    Serial.println("Reading data from DHT11...");
    if (!readData()) {
        Serial.println("Error reading data from DHT11.");
    }
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

void DHT11Reader::setTemperature(int temp) {
    temperature = temp;
}

void DHT11Reader::setHumidity(int hum) {
    humidity = hum;
}

bool DHT11Reader::isSensorAvailable() {
    return sensorAvailable;
}
