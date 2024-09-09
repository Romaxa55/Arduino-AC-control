#ifndef EEPROMHANDLER_H
#define EEPROMHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMHandler {
public:
    EEPROMHandler(uint8_t startAddress);

    void saveSignal(const uint16_t* signal, uint8_t length);
    void readSignal(uint16_t* buffer, uint8_t length);
    void printEEPROM() const;
    void clearEEPROM();

private:
    uint8_t eepromAddress; // Адрес EEPROM для хранения данных

    // Вспомогательные функции для сдвигов
    inline uint8_t getLowByte(uint16_t value) const { return value & 0xFF; } // Возвращаем младший байт
    inline uint8_t getHighByte(uint16_t value) const { return (value >> 8) & 0xFF; } // Возвращаем старший байт
};

#endif // EEPROMHANDLER_H
