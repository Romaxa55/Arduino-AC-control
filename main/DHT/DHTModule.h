#ifndef DHTMODULE_H
#define DHTMODULE_H

#include <DHT11.h>

class DHTModule {
public:
    DHTModule(uint8_t pin, uint8_t type);
    void begin();
    float readTemperature();
    float readHumidity();

private:
    DHT dht;
};

#endif
