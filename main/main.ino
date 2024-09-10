#include "config.h"

// Определение глобальных объектов
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN); // Создаем объект класса с указанием пинов
ErrorIndicator errorIndicator(LED_PIN); // Создаем объект для управления ошибками
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN); // Создаем объект RGBLed с указанными пинами
ButtonHandler button(BUTTON_PIN); // Создаем объект для управления кнопкой на указанном пине

void setup() {
#ifdef DEBUG
    Serial.begin(BOD);  // Устанавливаем более низкую скорость передачи данных, соответствующую пониженной частоте
    delayFunc(50);;  // Небольшая задержка для стабилизации перед инициализацией Serial
    Serial.println(F("Setup complete. Start app.")); // Выводим сообщение о завершении setup
#endif

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Отключаем встроенный светодиод для экономии энергии

    dhtReader.disableModules(); // Отключаем ненужные модули для экономии энергии
    dhtReader.initialize(); // Инициализируем датчик
    delayFunc(50);

    // Проверка доступности датчика
    if (!dhtReader.isSensorAvailable()) {
        errorIndicator.setError(SENSOR_ERROR); // Устанавливаем ошибку датчика, если он недоступен
        rgbLed.turnOnColor("red"); // Включаем красный цвет на RGB светодиоде, если ошибка
    }

    // Проверяем память
    eepromHandler.printEEPROM();

    delayFunc(50);  // Задержка для завершения инициализации
}

void loop() {
    button.update(); // Обновляем состояние кнопки и выполняем действия
    dhtReader.run(); // Запускаем процесс опроса датчика
    
    // Отслеживаем и выводим свободную память
#ifdef DEBUG
    Serial.print(F("Free memory: "));
    Serial.println(freeMemory());
#endif
}
