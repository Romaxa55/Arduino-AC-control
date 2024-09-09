#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG  // Определяем макрос DEBUG для включения отладки

// Подключаем только необходимые заголовочные файлы
#include "RGBLed.h"
#include "DHT11Reader.h"
#include "ErrorIndicator.h"
#include "ButtonHandler.h"
#include "EEPROMHandler.h"

// Определяем пины и константы с использованием constexpr для оптимизации памяти
constexpr uint8_t LED_PIN = 13;          // Встроенный светодиод на плате Arduino
constexpr uint8_t DHT_DATA_PIN = 3;      // Пин данных DHT11
constexpr uint8_t DHT_POWER_PIN = 2;     // Пин управления питанием DHT11
constexpr uint8_t RGB_RED_PIN = 4;       // Пин для красного цвета RGB светодиода
constexpr uint8_t RGB_GREEN_PIN = 5;     // Пин для зеленого цвета RGB светодиода
constexpr uint8_t RGB_BLUE_PIN = 6;      // Пин для синего цвета RGB светодиода
constexpr uint8_t BUTTON_PIN = 7;        // Пин для кнопки
constexpr uint16_t BOD = 9600;           // Скорость серийного порта

// Объявляем внешние объекты
extern DHT11Reader dhtReader;
extern ErrorIndicator errorIndicator;
extern RGBLed rgbLed;
extern ButtonHandler button;
extern EEPROMHandler eepromHandler;

#endif // CONFIG_H
