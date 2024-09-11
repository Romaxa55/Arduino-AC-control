#ifndef CONFIG_H
#define CONFIG_H

// ---------------------------------------------
// Конфигурация отладки
// ---------------------------------------------
#define DEBUG  // Определяем макрос DEBUG для включения отладки

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#endif

#ifdef DEBUG
// Функция для измерения свободной памяти
inline intptr_t freeMemory() {
    extern int __heap_start, *__brkval;
    uint8_t v;
    return (intptr_t)&v - (__brkval == 0 ? (intptr_t)&__heap_start : (intptr_t)__brkval);
}
#endif

// ---------------------------------------------
// Конфигурация пинов
// ---------------------------------------------
constexpr uint8_t LED_PIN = 13;          // Встроенный светодиод на плате Arduino
constexpr uint8_t DHT_DATA_PIN = 3;      // Пин данных DHT11
constexpr uint8_t DHT_POWER_PIN = 2;     // Пин управления питанием DHT11
constexpr uint8_t RGB_RED_PIN = 4;       // Пин для красного цвета RGB светодиода
constexpr uint8_t RGB_GREEN_PIN = 5;     // Пин для зеленого цвета RGB светодиода
constexpr uint8_t RGB_BLUE_PIN = 6;      // Пин для синего цвета RGB светодиода
constexpr uint8_t BUTTON_PIN = 7;        // Пин для кнопки
constexpr uint8_t IR_RECEIVE_PIN = 8;    // Пин для приема ИК
constexpr uint8_t IR_SEND_PIN = 9;       // Пин для отправки ИК

// ---------------------------------------------
// Конфигурация IR и задержек
// ---------------------------------------------
constexpr uint16_t BOD = 9600;  // Скорость серийного порта
constexpr uint8_t MARK_EXCESS_MICROS = 20;  // Корректировка временного интервала для обработки ИК сигналов

// Определяем тип указателя на функцию для задержки
using DelayFuncPtr = void (*)(unsigned long);
constexpr DelayFuncPtr delayFunc = delay; // Используем указатель на стандартную функцию delay

// ---------------------------------------------
// Настройки буфера для IR
// ---------------------------------------------
constexpr uint16_t DEFAULT_RAW_BUFFER_LENGTH = 200;
constexpr uint16_t EXTENDED_RAW_BUFFER_LENGTH = 730;

#if !((defined(RAMEND) && RAMEND <= 0x4FF) || (defined(RAMSIZE) && RAMSIZE < 0x4FF))
#define RAW_BUFFER_LENGTH EXTENDED_RAW_BUFFER_LENGTH
#else
#define RAW_BUFFER_LENGTH DEFAULT_RAW_BUFFER_LENGTH
#endif

// ---------------------------------------------
// Макросы и вспомогательные функции
// ---------------------------------------------
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// ---------------------------------------------
// Подключаемые библиотеки
// ---------------------------------------------
#include "RGBLed.h"          // Управление RGB светодиодом
#include "DHT11Reader.h"     // Управление датчиком DHT11
#include "ErrorIndicator.h"  // Управление индикатором ошибок
#include "ButtonHandler.h"   // Обработка нажатий кнопки
#include "EEPROMHandler.h"   // Управление EEPROM
#include <stdint.h>          // Подключаем библиотеку для использования intptr_t

// ---------------------------------------------
// Внешние объекты
// ---------------------------------------------
extern DHT11Reader dhtReader;           // Объект для работы с датчиком DHT11
extern ErrorIndicator errorIndicator;   // Объект для управления индикатором ошибок
extern RGBLed rgbLed;                   // Объект для управления RGB светодиодом
extern ButtonHandler button;            // Объект для обработки нажатий кнопки
extern EEPROMHandler eepromHandler;     // Объект для управления EEPROM

#endif // CONFIG_H
