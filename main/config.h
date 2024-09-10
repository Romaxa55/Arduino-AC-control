#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG  // Определяем макрос DEBUG для включения отладки

// Макрос для отладочного вывода
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#endif

// Подключаем необходимые заголовочные файлы
#include "RGBLed.h"          // Управление RGB светодиодом
#include "DHT11Reader.h"     // Управление датчиком DHT11
#include "ErrorIndicator.h"  // Управление индикатором ошибок
#include "ButtonHandler.h"   // Обработка нажатий кнопки
#include "EEPROMHandler.h"   // Управление EEPROM
#include <stdint.h>          // Подключаем библиотеку для использования intptr_t

// Определяем пины и константы с использованием constexpr для оптимизации памяти
constexpr uint8_t LED_PIN = 13;          // Встроенный светодиод на плате Arduino
constexpr uint8_t DHT_DATA_PIN = 3;      // Пин данных DHT11
constexpr uint8_t DHT_POWER_PIN = 2;     // Пин управления питанием DHT11
constexpr uint8_t RGB_RED_PIN = 4;       // Пин для красного цвета RGB светодиода
constexpr uint8_t RGB_GREEN_PIN = 5;     // Пин для зеленого цвета RGB светодиода
constexpr uint8_t RGB_BLUE_PIN = 6;      // Пин для синего цвета RGB светодиода
constexpr uint8_t BUTTON_PIN = 7;        // Пин для кнопки
constexpr uint16_t BOD = 9600;           // Скорость серийного порта

// Определяем тип указателя на функцию для задержки
typedef void (*DelayFuncPtr)(unsigned long);
constexpr DelayFuncPtr delayFunc = delay; // Используем указатель на стандартную функцию delay

// Функция для измерения свободной памяти
#ifdef DEBUG
inline intptr_t freeMemory() {
    extern int __heap_start, *__brkval;
    uint8_t v;
    return (intptr_t)&v - (__brkval == 0 ? (intptr_t)&__heap_start : (intptr_t)__brkval);
}
#endif

// Объявляем внешние объекты, которые будут использоваться в других модулях
extern DHT11Reader dhtReader;           // Объект для работы с датчиком DHT11
extern ErrorIndicator errorIndicator;   // Объект для управления индикатором ошибок
extern RGBLed rgbLed;                   // Объект для управления RGB светодиодом
extern ButtonHandler button;            // Объект для обработки нажатий кнопки
extern EEPROMHandler eepromHandler;     // Объект для управления EEPROM

#endif // CONFIG_H
