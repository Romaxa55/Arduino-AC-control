#include "DHTModule.h"

DHTModule::DHTModule(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DHTModule::begin() {
    dht.begin();
}

float DHTModule::readTemperature() {
    return dht.readTemperature();
}

float DHTModule::readHumidity() {
    return dht.readHumidity();
}
