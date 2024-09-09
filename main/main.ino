#include "config.h"

// Определение глобальных объектов
CustomArduino arduino;
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN); // Создаем объект класса с указанием пинов
ErrorIndicator errorIndicator(LED_PIN); // Создаем объект для управления ошибками
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN); // Создаем объект RGBLed с указанными пинами
ButtonHandler button(BUTTON_PIN); // Создаем объект для управления кнопкой на указанном пине

void setup() {
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
        rgbLed.red(); // Включаем красный цвет на RGB светодиоде, если ошибка
    } 
    arduino.delay(200);  // Задержка для завершения инициализации
}

void loop() {
    button.update(); // Обновляем состояние кнопки и выполняем действия
    dhtReader.run(); // Запускаем процесс опроса датчика
}
