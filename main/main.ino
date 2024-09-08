#include "DHT11Reader.h"

#define DHT11_PIN 2 // Пин, к которому подключен датчик DHT11

DHT11Reader dhtReader(DHT11_PIN); // Создаем объект класса с инициализацией

void setup() {
    Serial.begin(9600); // Инициализируем сериальный порт
}

void loop() {
    dhtReader.printData(); // Вызываем метод для чтения и вывода данных
    delay(2000); // Задержка между измерениями
}
