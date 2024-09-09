#include "config.h"

// Определение глобальных объектов
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN); // Создаем объект класса с указанием пинов
ErrorIndicator errorIndicator(LED_PIN); // Создаем объект для управления ошибками
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN); // Создаем объект RGBLed с указанными пинами
ButtonHandler button(BUTTON_PIN); // Создаем объект для управления кнопкой на указанном пине

// Функция для измерения свободной памяти
int freeMemory() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void setup() {
#ifdef DEBUG
    Serial.begin(BOD);  // Устанавливаем более низкую скорость передачи данных, соответствующую пониженной частоте
    delay(100);  // Небольшая задержка для стабилизации перед инициализацией Serial
    Serial.println("Setup complete. Start app."); // Выводим сообщение о завершении setup
#endif

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Отключаем встроенный светодиод для экономии энергии

    dhtReader.disableModules(); // Отключаем ненужные модули для экономии энергии
    dhtReader.initialize(); // Инициализируем датчик
    delay(200);

    // Проверка доступности датчика
    if (!dhtReader.isSensorAvailable()) {
        errorIndicator.setError(SENSOR_ERROR); // Устанавливаем ошибку датчика, если он недоступен
        rgbLed.red(); // Включаем красный цвет на RGB светодиоде, если ошибка
    } 
    
    // Проверяем память
    eepromHandler.printEEPROM();

    delay(200);  // Задержка для завершения инициализации
}

void loop() {
    button.update(); // Обновляем состояние кнопки и выполняем действия
    dhtReader.run(); // Запускаем процесс опроса датчика

    // Отслеживаем и выводим свободную память
    Serial.print("Free memory: ");
    Serial.println(freeMemory());
}
