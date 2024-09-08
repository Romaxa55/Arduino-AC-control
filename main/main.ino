#include "DHT11Reader.h"
#include <avr/power.h> // Подключаем библиотеку для управления тактовой частотой
#include "config.h"
#include "ErrorIndicator.h"

#define LED_PIN 13         // Встроенный светодиод на плате Arduino
#define DHT_DATA_PIN 3     // Пин данных DHT11
#define DHT_POWER_PIN 2    // Пин управления питанием DHT11
#define BOD 9600    // Скорость серийного порта

CustomArduino arduino;
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN); // Создаем объект класса с указанием пинов
ErrorIndicator errorIndicator(LED_PIN); // Создаем объект для управления ошибками

void setup() {
    // Устанавливаем пониженную тактовую частоту для экономии энергии
//    clock_prescale_set(clock_div_8); // Устанавливаем тактовую частоту в 1/8 от стандартной (2 МГц вместо 16 МГц)

#ifdef DEBUG
    Serial.begin(BOD);  // Устанавливаем более низкую скорость передачи данных, соответствующую пониженной частоте
    arduino.delay(100);  // Небольшая задержка для стабилизации перед инициализацией Serial
    Serial.println("Setup complete. Start app."); // Выводим сообщение о завершении setup
#endif

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Отключаем встроенный светодиод для экономии энергии

    dhtReader.disableModules(); // Отключаем ненужные модули для экономии энергии
    dhtReader.initialize(); // Инициализируем датчик
    arduino.delay(200);

    // Проверка доступности датчика
    if (!dhtReader.isSensorAvailable()) {
        errorIndicator.setError(SENSOR_ERROR); // Устанавливаем ошибку датчика, если он недоступен
    }
    arduino.delay(200);  // Задержка для завершения инициализации
}

void loop() {
#ifdef DEBUG
    Serial.println("Start app");
#endif
    dhtReader.readAndPrintData(); // Читаем и выводим данные с датчика

#ifdef DEBUG
    Serial.println("Going to sleep...");
#endif
    arduino.delay(200);  // Задержка перед сном

    dhtReader.enterSleepMode();  // Переходим в режим сна (и затем произойдет сброс)
}
