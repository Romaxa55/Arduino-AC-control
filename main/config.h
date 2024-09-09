#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG  // Определяем макрос DEBUG для включения отладки

#include "RGBLed.h"         // Подключаем заголовок для RGB светодиода
#include "DHT11Reader.h"    // Подключаем заголовок для работы с датчиком DHT11
#include "ErrorIndicator.h" // Подключаем заголовок для индикатора ошибок
#include "ButtonHandler.h"  // Подключаем заголовок для управления кнопкой
#include "EEPROMHandler.h"

// Определяем пины и константы с использованием const
const uint8_t LED_PIN = 13;          // Встроенный светодиод на плате Arduino
const uint8_t DHT_DATA_PIN = 3;      // Пин данных DHT11
const uint8_t DHT_POWER_PIN = 2;     // Пин управления питанием DHT11
const uint8_t RGB_RED_PIN = 4;       // Пин для красного цвета RGB светодиода
const uint8_t RGB_GREEN_PIN = 5;     // Пин для зеленого цвета RGB светодиода
const uint8_t RGB_BLUE_PIN = 6;      // Пин для синего цвета RGB светодиода
const uint8_t BUTTON_PIN = 7;        // Пин для кнопки
const uint32_t BOD = 9600;           // Скорость серийного порта

// Объявляем внешние объекты
extern DHT11Reader dhtReader;
extern ErrorIndicator errorIndicator;
extern RGBLed rgbLed;
extern ButtonHandler button;
extern EEPROMHandler eepromHandler;

#endif // CONFIG_H
