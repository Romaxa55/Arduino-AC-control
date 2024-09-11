#include "config.h"
#include <IRremote.hpp>  // Включаем библиотеку IRremote только в main

// Определение глобальных объектов
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN);
ErrorIndicator errorIndicator(LED_PIN);
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
ButtonHandler button(BUTTON_PIN);
IRrecv irReceiver(IR_RECEIVE_PIN);

// Функция для обработки ИК сигналов
void handleIRSignals(IRrecv& irReceiver) {
    if (irReceiver.decode()) {
        Serial.println(F("\n\n"));  // Пустые строки

        irReceiver.printIRResultShort(&Serial);

        // Проверка переполнения буфера
        if (irReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            Serial.println(F("Попробуйте увеличить значение \"RAW_BUFFER_LENGTH\" в " __FILE__));
        } else {
            if (irReceiver.decodedIRData.protocol == UNKNOWN) {
                Serial.println(F("Получен шум или неизвестный протокол"));
            }
            Serial.println();
            irReceiver.printIRSendUsage(&Serial);
            Serial.println();
            Serial.println(F("Результат в тиках (50 мкс) - с ведущим промежутком"));
            irReceiver.printIRResultRawFormatted(&Serial, false);
            Serial.println(F("Результат в микросекундах - с ведущим промежутком"));
            irReceiver.printIRResultRawFormatted(&Serial, true);
            Serial.println();
            Serial.print(F("Результат в 8-битных тиках - с компенсацией MARK_EXCESS_MICROS="));
            Serial.println(MARK_EXCESS_MICROS);
            irReceiver.compensateAndPrintIRResultAsCArray(&Serial, false);
            Serial.print(F("Результат в массиве микросекунд - с компенсацией MARK_EXCESS_MICROS="));
            Serial.println(MARK_EXCESS_MICROS);
            irReceiver.compensateAndPrintIRResultAsCArray(&Serial, true);
            irReceiver.printIRResultAsCVariables(&Serial);
            Serial.println();
            irReceiver.compensateAndPrintIRResultAsPronto(&Serial);
        }
        irReceiver.resume();  // Готовим к следующему ИК кадру
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

#ifdef DEBUG
    Serial.print(F("Free memory: "));
    Serial.println(freeMemory());
#endif
}
