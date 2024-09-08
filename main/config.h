#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG  // Определяем макрос DEBUG для включения отладки
//#define USE_CUSTOM_DELAY  // Определяем макрос для использования кастомного delay

#include "CustomArduino.h"  // Подключаем CustomArduino.h перед использованием extern
#include "RGBLed.h"         // Подключаем заголовок для RGB светодиода
#include "DHT11Reader.h"    // Подключаем заголовок для работы с датчиком DHT11
#include "ErrorIndicator.h" // Подключаем заголовок для индикатора ошибок

// Объявляем объект arduino как внешнюю переменную
extern CustomArduino arduino;

// Определяем пины и константы
#define LED_PIN 13           // Встроенный светодиод на плате Arduino
#define DHT_DATA_PIN 3       // Пин данных DHT11
#define DHT_POWER_PIN 2      // Пин управления питанием DHT11
#define RGB_RED_PIN 4        // Пин для красного цвета RGB светодиода
#define RGB_GREEN_PIN 5      // Пин для зеленого цвета RGB светодиода
#define RGB_BLUE_PIN 6       // Пин для синего цвета RGB светодиода
#define BOD 9600             // Скорость серийного порта

// Определения ошибок для индикатора ошибок (удалено, т.к. есть в ErrorIndicator.h)

#endif // CONFIG_H
