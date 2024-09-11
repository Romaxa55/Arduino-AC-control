#include "EEPROMHandler.h"
#include "config.h"

// Конструктор инициализации начального адреса для EEPROM
EEPROMHandler::EEPROMHandler(uint8_t startAddress) : eepromAddress(startAddress) {}

void EEPROMHandler::saveSignal(const uint8_t* signal, uint8_t length) {
    if (length > MAX_EEPROM_SIZE) length = MAX_EEPROM_SIZE; // Ограничиваем длину до максимума

    for (uint8_t i = 0; i < length; ++i) {
        EEPROM.update(eepromAddress + i, signal[i]); // Записываем каждый байт
    }
}

// Функция для чтения сигнала из EEPROM с использованием битовых сдвигов
void EEPROMHandler::readSignal(uint8_t* buffer, uint8_t length) {
if (length > MAX_EEPROM_SIZE) length = MAX_EEPROM_SIZE; // Ограничиваем длину до максимума

    for (uint8_t i = 0; i < length; ++i) {

        buffer[i] = EEPROM.read(eepromAddress + i);
    }
}

// Оптимизированная функция вывода содержимого EEPROM в HEX формате
void EEPROMHandler::printEEPROM() const {
    Serial.println(F("EEPROM Content:"));

    const uint16_t eepromSize = MAX_EEPROM_SIZE; // Используем максимальный размер 200 байт
    const uint8_t bytesPerLine = 16;  // Количество байт на строку для вывода

    for (uint16_t i = 0; i < eepromSize; ++i) {
        if (i % bytesPerLine == 0) {  // Переход на новую строку каждые 16 байт
            Serial.print(F("\n0x"));
            Serial.print(i, HEX);
            Serial.print(F(": "));
        }
        uint8_t value = EEPROM.read(i);  // Читаем значение из EEPROM
        if (value < 0x10) Serial.print('0'); // Добавляем ведущий ноль для значений от 0x0 до 0xF
        Serial.print(value, HEX);
        Serial.print(F(" "));
    }
    Serial.println();
}

// Оптимизированная функция очистки EEPROM
void EEPROMHandler::clearEEPROM() {
    const uint16_t eepromSize = MAX_EEPROM_SIZE; // Используем максимальный размер 200 байт

    for (uint16_t i = 0; i < eepromSize; ++i) {
        EEPROM.update(i, 0xFF); // Используем EEPROM.update() для уменьшения износа памяти
    }
    Serial.println(F("EEPROM cleared."));
}
