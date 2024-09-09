#include "config.h"

// Инициализация начального адреса для EEPROM
EEPROMHandler::EEPROMHandler(int startAddress) {
    eepromAddress = startAddress;
}

// Функция для сохранения сигнала в EEPROM
void EEPROMHandler::saveSignal(uint16_t* signal, int length) {
    for (int i = 0; i < length; i++) {
        EEPROM.put(eepromAddress + i * sizeof(uint16_t), signal[i]);
    }
}

// Функция для чтения сигнала из EEPROM
void EEPROMHandler::readSignal(uint16_t* buffer, int length) {
    for (int i = 0; i < length; i++) {
        EEPROM.get(eepromAddress + i * sizeof(uint16_t), buffer[i]);
    }
}

// Функция для вывода содержимого EEPROM в HEX формате
void EEPROMHandler::printEEPROM() {
    Serial.println("EEPROM Content:");
    for (int i = 0; i < EEPROM.length(); i++) {
        uint8_t value;
        EEPROM.get(i, value);
        if (i % 16 == 0) {
            Serial.println();
            Serial.print("0x");
            Serial.print(i, HEX);
            Serial.print(": ");
        }
        Serial.print(value, HEX);
        Serial.print(" ");
    }
    Serial.println();
}

// Функция для очистки EEPROM
void EEPROMHandler::clearEEPROM() {
    for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0xFF); // Записываем значение 0xFF, что соответствует очищенной ячейке памяти
    }
    Serial.println("EEPROM cleared.");
}
