#include "EEPROMHandler.h"
#include "config.h"

// Конструктор инициализации начального адреса для EEPROM
EEPROMHandler::EEPROMHandler(uint8_t startAddress) : eepromAddress(startAddress) {}

// Функция для сохранения сигнала в EEPROM с использованием битовых сдвигов
void EEPROMHandler::saveSignal(const uint16_t* signal, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        uint8_t lowByte = getLowByte(signal[i]);   // Младший байт
        uint8_t highByte = getHighByte(signal[i]); // Старший байт

        // Сохраняем младший и старший байт по адресу
        EEPROM.update(eepromAddress + (i << 1), lowByte); // i * 2 заменено на битовый сдвиг (i << 1)
        EEPROM.update(eepromAddress + (i << 1) + 1, highByte);
    }
}

// Функция для чтения сигнала из EEPROM с использованием битовых сдвигов
void EEPROMHandler::readSignal(uint16_t* buffer, uint8_t length) {
for (uint8_t i = 0; i < length; ++i) {
uint8_t lowByte, highByte;

EEPROM.get(eepromAddress + (i << 1), lowByte); // Читаем младший байт
EEPROM.get(eepromAddress + (i << 1) + 1, highByte); // Читаем старший байт

// Восстанавливаем 16-битное значение из двух байтов
buffer[i] = (static_cast<uint16_t>(highByte) << 8) | lowByte;
}
}

// Оптимизированная функция вывода содержимого EEPROM в HEX формате
void EEPROMHandler::printEEPROM() const {
    Serial.println(F("EEPROM Content:"));

    // Ограничим количество данных, которые будут выведены
    const uint16_t eepromSize = EEPROM.length(); // Получаем максимальную длину EEPROM
    const uint8_t bytesPerLine = 16;  // Устанавливаем количество байт на строку для вывода

    // Убедимся, что не выходим за пределы EEPROM
    for (uint16_t i = 0; i < eepromSize; ++i) {
        if (i % bytesPerLine == 0) {  // Переход на новую строку каждые 16 байт
            Serial.print(F("\n0x"));
            Serial.print(i, HEX);
            Serial.print(F(": "));
        }
        uint8_t value;
        EEPROM.get(i, value);  // Читаем значение из EEPROM
        if (value < 0x10) Serial.print('0'); // Добавляем ведущий ноль для значений от 0x0 до 0xF
        Serial.print(value, HEX);
        Serial.print(F(" "));
    }
    Serial.println();
}

// Оптимизированная функция очистки EEPROM
void EEPROMHandler::clearEEPROM() {
    for (uint8_t i = 0; i < EEPROM.length(); ++i) {
        EEPROM.update(i, 0xFF); // Используем EEPROM.update() для уменьшения износа памяти
    }
    Serial.println(F("EEPROM cleared."));
}
