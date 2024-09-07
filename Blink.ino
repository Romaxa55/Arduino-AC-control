#include <Arduino.h>
#include "LED.h"

LED led1(13); // Создаем экземпляр класса LED для пина 13

void setup() {
    Serial.begin(9600); // Настраиваем последовательный порт для вывода
    Serial.println("LED control program started.");
}

void loop() {
    Serial.println("LED is ON");
    led1.on();
    delay(1000); // Задержка 1 секунда

    Serial.println("LED is OFF");
    led1.off();
    delay(1000); // Задержка 1 секунда

    Serial.println("LED is blinking");
    led1.blink(500); // Мигание светодиода с задержкой 500 мс

    led1.toggle(); // Переключаем состояние
    delay(1000);
}
