#ifndef IRRECEIVER_H
#define IRRECEIVER_H

#include <Arduino.h>
#include <IRremote.h>  // Подключаем библиотеку IRremote

class IRReceiver {
public:
    IRReceiver(uint8_t pin); // Конструктор для приема пина
    void begin();            // Инициализация приемника
    uint32_t receive();      // Метод для приема и возвращения команды

private:
    uint8_t recvPin;        // Пин для ИК-приемника
    IRrecv irrecv;          // Экземпляр приемника
    decode_results results; // Структура для хранения результатов
};

#endif
