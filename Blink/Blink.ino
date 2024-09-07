#include "LED.h"
#include "IRReceiver.h"

LED led1(13);          // Экземпляр класса LED для пина 13
IRReceiver irReceiver(11); // Экземпляр класса IRReceiver для пина 11 (подключите ИК-приемник к этому пину)

void setup() {
    Serial.begin(9600);
    Serial.println(F("LED control program with IR started."));
    irReceiver.begin(); // Инициализируем ИК-приемник
}

void loop() {
    uint32_t receivedCommand = irReceiver.receive(); // Получаем команду с пульта

    if (receivedCommand) {
        Serial.print(F("Received IR command: "));
        Serial.println(receivedCommand, HEX); // Печатаем команду в шестнадцатеричном формате

        // Простая обработка команд - можно добавить свои условия
        if (receivedCommand == 0x20DF10EF) { // Пример кода для включения светодиода
            led1.on();
        } else if (receivedCommand == 0x20DF906F) { // Пример кода для выключения светодиода
            led1.off();
        } else {
            led1.toggle(); // Переключаем состояние светодиода по любой другой команде
        }
    }

    delay(100); // Небольшая задержка для стабилизации
}
