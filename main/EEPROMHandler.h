#ifndef EEPROMHANDLER_H
#define EEPROMHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMHandler {
public:
    EEPROMHandler(int startAddress); // Конструктор

    void saveSignal(uint16_t* signal, int length);  // Сохранение сигнала в EEPROM
    void readSignal(uint16_t* buffer, int length);  // Чтение сигнала из EEPROM
    void printEEPROM();                             // Вывод содержимого EEPROM в HEX формате

private:
    int eepromAddress; // Начальный адрес в EEPROM
};

#endif // EEPROMHANDLER_H
