#include "config.h"

// Определение глобальных объектов
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN);
ErrorIndicator errorIndicator(LED_PIN);
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
ButtonHandler button(BUTTON_PIN);
EEPROMHandler eepromHandler(0); // Начинаем запись с адреса 0


void setup() {
#ifdef DEBUG
    Serial.begin(BOD);
    while (!Serial);
#endif

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);  // Отключаем встроенный светодиод для экономии энергии

    dhtReader.initialize();
    delayFunc(50);

    if (!dhtReader.isSensorAvailable()) {
        errorIndicator.setError(SENSOR_ERROR);
        rgbLed.turnOnColor("red");
    }

    eepromHandler.printEEPROM();
    // Чтение сигнала из EEPROM

    delayFunc(50);
}

void loop() {
    button.update();
    dhtReader.run();

#ifdef DEBUG
    Serial.print(F("Free memory: "));
    Serial.println(freeMemory());
#endif
}
