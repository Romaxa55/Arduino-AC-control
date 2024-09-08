#include "DHT11Reader.h"
#include <avr/power.h> // Подключаем библиотеку для управления тактовой частотой
#include "config.h"  // Подключаем заголовочный файл с определением DEBUG

#define LED_PIN 13         // Встроенный светодиод на плате Arduino
#define DHT_DATA_PIN 2     // Пин данных DHT11
#define DHT_POWER_PIN 7    // Пин управления питанием DHT11
#define BOD 9600    // Скорость серийного порта

DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN); // Создаем объект класса с указанием пинов

void setup() {
    // Устанавливаем пониженную тактовую частоту для экономии энергии
    clock_prescale_set(clock_div_8); // Устанавливаем тактовую частоту в 1/8 от стандартной (2 МГц вместо 16 МГц)

#ifdef DEBUG
    Serial.begin(BOD);  // Устанавливаем более низкую скорость передачи данных, соответствующую пониженной частоте
    delay(100);  // Небольшая задержка для стабилизации перед инициализацией Serial
    Serial.println("Setup complete. Start app."); // Выводим сообщение о завершении setup
#endif

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Отключаем встроенный светодиод для экономии энергии

    dhtReader.disableModules(); // Отключаем ненужные модули для экономии энергии
    dhtReader.initialize(); // Инициализируем датчик
    delay(200);  // Задержка для завершения инициализации
}

void loop() {
#ifdef DEBUG
    Serial.println("Start app");
#endif
    dhtReader.readAndPrintData(); // Читаем и выводим данные с датчика

#ifdef DEBUG
    Serial.println("Going to sleep...");
#endif
    delay(1000);  // Задержка перед сном

    dhtReader.enterSleepMode();  // Переходим в режим сна (и затем произойдет сброс)
}
