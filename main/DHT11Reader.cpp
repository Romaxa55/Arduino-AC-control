#include "DHT11Reader.h"
#include "config.h"

// Константа для времени сна в миллисекундах (здесь 8 секунд)
const uint8_t SLEEP_DURATION = WDTO_8S; // Возможные значения: WDTO_15MS, WDTO_30MS, WDTO_60MS, WDTO_120MS, WDTO_250MS, WDTO_500MS, WDTO_1S, WDTO_2S, WDTO_4S, WDTO_8S

// Конструктор с инициализацией пинов
DHT11Reader::DHT11Reader(uint8_t dataPin, uint8_t powerPin)
        : dht11(dataPin), temperature(0), humidity(0), powerPin(powerPin), sensorAvailable(false) {
    pinMode(powerPin, OUTPUT); // Настраиваем пин управления питанием как выход
    digitalWrite(powerPin, LOW); // Отключаем питание датчика при инициализации
}

// Метод для инициализации датчика
void DHT11Reader::initialize() {
    Serial.println("Initializing DHT11 sensor...");
    powerOn();
    delay(200); // Ждем 200 мс для стабилизации датчика

    if (readData()) {
        sensorAvailable = true; // Если чтение успешно, датчик доступен
        Serial.println("DHT11 sensor initialized successfully.");
    } else {
        sensorAvailable = false; // Если чтение не удалось, помечаем датчик как недоступный
        Serial.println("DHT11 sensor is not available at startup.");
    }
    powerOff();
}

// Метод для включения питания датчика
void DHT11Reader::powerOn() {
    digitalWrite(powerPin, HIGH); // Включаем питание
    delay(200); // Ждем 200 мс для стабилизации датчика
}

// Метод для отключения питания датчика
void DHT11Reader::powerOff() {
    digitalWrite(powerPin, LOW); // Выключаем питание
}

// Приватный метод для чтения данных с датчика
bool DHT11Reader::readData() {
    powerOn(); // Включаем питание перед считыванием данных
    delay(2000); // Ждем 2 секунды для стабилизации перед чтением

    int result = dht11.readTemperatureHumidity(temperature, humidity);
    powerOff(); // Отключаем питание после считывания данных

    if (result != 0) {
        Serial.println("Failed to read from DHT11 sensor.");
        return false; // Возвращаем false, если чтение не удалось
    }

    // Применяем калибровку температуры
    temperature -= 5;

    Serial.print("Temperature (corrected): ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    return true; // Возвращаем true, если чтение успешно
}

// Метод для чтения данных и вывода их в Serial
void DHT11Reader::readAndPrintData() {
    if (!sensorAvailable) { // Проверяем, доступен ли датчик
        Serial.println("Skipping data read; sensor is not available.");
        return;
    }

    Serial.println("Reading data from DHT11...");
    if (!readData()) {
        Serial.println("Error reading data from DHT11.");
    }
}

// Метод для перехода в режим сна
void DHT11Reader::enterSleepMode() {
    Serial.println("Entering sleep mode...");
    delay(500); // Ждем 500 мс перед входом в режим сна

    // Настраиваем Watchdog Timer для пробуждения
    wdt_enable(SLEEP_DURATION); // Устанавливаем время сна

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Используем режим максимального энергосбережения
    sleep_enable(); // Разрешаем режим сна

    noInterrupts(); // Отключаем прерывания для безопасного входа в режим сна
    sleep_cpu(); // Переводим микроконтроллер в режим сна
}

// Метод для отключения неиспользуемых модулей
void DHT11Reader::disableModules() {
    ADCSRA &= ~(1 << ADEN); // Отключаем АЦП (ADC) для экономии энергии

    power_spi_disable(); // Отключаем модуль SPI
    power_twi_disable(); // Отключаем модуль TWI (I2C)

    power_timer1_disable(); // Отключаем таймеры, если они не нужны
    power_timer2_disable();
}

// Геттеры для получения температуры и влажности
int DHT11Reader::getTemperature() const {
    return temperature;
}

int DHT11Reader::getHumidity() const {
    return humidity;
}

// Сеттеры для установки температуры и влажности (если нужно)
void DHT11Reader::setTemperature(int temp) {
    temperature = temp;
}

void DHT11Reader::setHumidity(int hum) {
    humidity = hum;
}

// Метод для проверки доступности датчика
bool DHT11Reader::isSensorAvailable() {
    return sensorAvailable;
}

