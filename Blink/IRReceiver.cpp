#include "IRReceiver.h"

IRReceiver::IRReceiver(uint8_t pin) : recvPin(pin), irrecv(pin) {
    // Конструктор инициализация
}

void IRReceiver::begin() {
    irrecv.enableIRIn(); // Включаем прием ИК
}

uint32_t IRReceiver::receive() {
    if (irrecv.decode(&results)) {
        uint32_t value = results.value; // Получаем код команды
        irrecv.resume(); // Готовимся к следующему приему
        return value;    // Возвращаем полученное значение
    }
    return 0; // Возвращаем 0, если ничего не принято
}
