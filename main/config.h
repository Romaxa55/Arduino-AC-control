// config.h
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG  // Определяем макрос DEBUG для включения отладки
//#define USE_CUSTOM_DELAY  // Определяем макрос для использования кастомного delay

#include "CustomArduino.h"  // Подключаем CustomArduino.h перед использованием extern

// Объявляем объект arduino как внешнюю переменную
extern CustomArduino arduino;

#endif // CONFIG_H
