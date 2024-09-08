#include "DHTModule.h"

#define DHTPIN 2      // Пин, к которому подключен DHT11
#define DHTTYPE DHT11 // Тип датчика DHT11

DHTModule dhtModule(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dhtModule.begin();
}

void loop() {
    float temp = dhtModule.readTemperature();
    float humidity = dhtModule.readHumidity();

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C ");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    delay(2000); // Задержка между измерениями
}
