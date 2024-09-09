#ifndef EEPROMHANDLER_H
#define EEPROMHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMHandler {
public:
    EEPROMHandler(int startAddress);

    void saveSignal(uint16_t* signal, int length);
    void readSignal(uint16_t* buffer, int length);
    void printEEPROM();
    void clearEEPROM(); // Метод для очистки EEPROM

private:
    int eepromAddress; // Начальный адрес для хранения данных в EEPROM
};

#endif // EEPROMHANDLER_H
