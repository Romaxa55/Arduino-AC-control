#include "config.h"
#include <IRremote.hpp>  // Включаем библиотеку IRremote только в main

// Определение глобальных объектов
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN);
ErrorIndicator errorIndicator(LED_PIN);
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
ButtonHandler button(BUTTON_PIN);
IRrecv irReceiver(IR_RECEIVE_PIN);
EEPROMHandler eepromHandler(0); // Начинаем запись с адреса 0

void handleIRSignals(IRrecv& irReceiver) {
    if (irReceiver.decode()) {
        IRRawbufType* rawData = irReceiver.decodedIRData.rawDataPtr->rawbuf;
        uint8_t rawDataLen = irReceiver.decodedIRData.rawlen;

        // Преобразование сырых данных в массив uint8_t
        uint8_t signalData[rawDataLen];
        for (uint8_t i = 0; i < rawDataLen; i++) {
            signalData[i] = static_cast<uint8_t>(rawData[i]); // Преобразуем в uint8_t
        }

        // Запись сигнала в EEPROM
        eepromHandler.saveSignal(signalData, rawDataLen);

        Serial.println("Данные сигнала записаны в EEPROM.");
        irReceiver.resume();  // Готовим приемник к следующему сигналу
    }
}

void setup() {
#ifdef DEBUG
    Serial.begin(BOD);
    while (!Serial);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
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
    irReceiver.begin(IR_RECEIVE_PIN);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    delayFunc(50);
}

void loop() {
    handleIRSignals(irReceiver);
    button.update();
    dhtReader.run();

// #ifdef DEBUG
//     Serial.print(F("Free memory: "));
//     Serial.println(freeMemory());
// #endif
}
