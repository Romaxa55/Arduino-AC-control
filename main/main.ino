#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include "config.h"
#include <IRremote.hpp>  // Включаем библиотеку IRremote только в main

// Определение глобальных объектов
DHT11Reader dhtReader(DHT_DATA_PIN, DHT_POWER_PIN); // Создаем объект класса с указанием пинов
ErrorIndicator errorIndicator(LED_PIN); // Создаем объект для управления ошибками
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN); // Создаем объект RGBLed с указанными пинами
ButtonHandler button(BUTTON_PIN); // Создаем объект для управления кнопкой на указанном пине
IRrecv irReceiver(IR_RECEIVE_PIN); // Инициализация объекта IrReceiver

// Функция для обработки ИК сигналов
void handleIRSignals(IRrecv& irReceiver) {
    if (irReceiver.decode()) {
        Serial.println(); // пустая строка
        Serial.println(); // две пустые строки
        irReceiver.printIRResultShort(&Serial);

        // Проверка переполнения буфера
        if (irReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            Serial.println(F("Попробуйте увеличить значение \"RAW_BUFFER_LENGTH\" до " STR(RAW_BUFFER_LENGTH) " в " __FILE__));
        } else {
            if (irReceiver.decodedIRData.protocol == UNKNOWN) {
                Serial.println(F("Получен шум или неизвестный (или еще не включенный) протокол"));
            }
            Serial.println();
            irReceiver.printIRSendUsage(&Serial);
            Serial.println();
            Serial.println(F("Результат в тиках (50 мкс) - с ведущим промежутком"));
            irReceiver.printIRResultRawFormatted(&Serial, false); // Вывод в формате RAW
            Serial.println(F("Результат в микросекундах - с ведущим промежутком"));
            irReceiver.printIRResultRawFormatted(&Serial, true);  // Вывод в формате RAW
            Serial.println();
            Serial.print(F("Результат в 8-битных тиках (50 мкс) - с компенсацией MARK_EXCESS_MICROS="));
            Serial.println(MARK_EXCESS_MICROS);
            irReceiver.compensateAndPrintIRResultAsCArray(&Serial, false); // Вывод в формате массива uint8_t
            Serial.print(F("Результат в массиве микросекунд - с компенсацией MARK_EXCESS_MICROS="));
            Serial.println(MARK_EXCESS_MICROS);
            irReceiver.compensateAndPrintIRResultAsCArray(&Serial, true); // Вывод в формате массива uint16_t
            irReceiver.printIRResultAsCVariables(&Serial);  // Вывод адреса и данных в виде переменных
            Serial.println();

            irReceiver.compensateAndPrintIRResultAsPronto(&Serial);
        }
        irReceiver.resume(); // Готовим к следующему ИК кадру
    }
}

void setup() {
#ifdef DEBUG
    Serial.begin(BOD);  // Устанавливаем более низкую скорость передачи данных, соответствующую пониженной частоте
    while (!Serial)
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
#endif

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Отключаем встроенный светодиод для экономии энергии

    // dhtReader.disableModules(); // Отключаем ненужные модули для экономии энергии
    dhtReader.initialize(); // Инициализируем датчик
    delayFunc(50);

    // Проверка доступности датчика
    if (!dhtReader.isSensorAvailable()) {
        errorIndicator.setError(SENSOR_ERROR); // Устанавливаем ошибку датчика, если он недоступен
        rgbLed.turnOnColor("red"); // Включаем красный цвет на RGB светодиоде, если ошибка
    }

    // Проверяем память
    eepromHandler.printEEPROM();

    irReceiver.begin(IR_RECEIVE_PIN);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    delayFunc(50);  // Задержка для завершения инициализации
}

void loop() {
    handleIRSignals(irReceiver);  // Обработка ИК сигналов
    button.update(); // Обновляем состояние кнопки и выполняем действия
    dhtReader.run(); // Запускаем процесс опроса датчика

    // Отслеживаем и выводим свободную память
#ifdef DEBUG
    Serial.print(F("Free memory: "));
    Serial.println(freeMemory());
#endif
}

