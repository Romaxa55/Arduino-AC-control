#include "LED.h"

LED led1(13); // Экземпляр класса LED для пина 13

void setup() {
    Serial.begin(9600);
    Serial.println(F("LED control program started.")); // Используем F() для строк
}

void loop() {
    Serial.println(F("LED is ON"));
    led1.on();
    delay(1000);

    Serial.println(F("LED is OFF"));
    led1.off();
    delay(1000);

    Serial.println(F("LED is blinking"));
    led1.blink(500);

    led1.toggle();
    delay(1000);
}
