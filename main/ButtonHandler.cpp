#include "ButtonHandler.h"
#include "config.h"  // Подключаем конфигурационный файл для доступа к глобальным объектам
#include <avr/wdt.h> // Подключаем библиотеку для работы с Watchdog Timer

ButtonHandler::ButtonHandler(uint8_t pin)
        : buttonPin(pin), buttonPressTime(0), buttonPressed(false), actionTriggered(false),
          lastDebounceTime(0), debounceDelay(50) { // Устанавливаем задержку для устранения дребезга
    pinMode(buttonPin, INPUT_PULLUP); // Настраиваем кнопку на вход с подтяжкой к питанию
}

void ButtonHandler::update() {
    unsigned long currentMillis = millis();

    if (digitalRead(buttonPin) == LOW) { // Кнопка нажата
        if (!buttonPressed) { // Начало нажатия
            buttonPressed = true;
            buttonPressTime = currentMillis; // Записываем время начала нажатия
            actionTriggered = false; // Сбрасываем флаг выполнения действия
#ifdef DEBUG
            Serial.println("Button pressed.");
#endif
        }

        // Индикация времени нажатия кнопки
        indicatePressDuration(currentMillis);

    } else { // Кнопка отпущена
        if (buttonPressed) { // Если кнопка была нажата, но теперь отпущена
            unsigned long pressDuration = currentMillis - buttonPressTime;

            // Выбираем действие на основе времени удержания кнопки
            if (pressDuration < 5000 && !actionTriggered) { // Короткое нажатие (меньше 5 секунд)
#ifdef DEBUG
                Serial.println("Short press detected.");
#endif
                handleShortPress();
            } else if (pressDuration >= 5000 && pressDuration < 10000 && !actionTriggered) { // Среднее нажатие
#ifdef DEBUG
                Serial.println("Medium press detected.");
#endif
                handleMediumPress();
            } else if (pressDuration >= 10000 && !actionTriggered) { // Длинное нажатие
#ifdef DEBUG
                Serial.println("Long press detected.");
#endif
                handleLongPress();
            }

            buttonPressed = false; // Сбрасываем состояние кнопки
            actionTriggered = true; // Отмечаем, что действие выполнено
        }
    }
}

void ButtonHandler::indicatePressDuration(unsigned long currentMillis) {
    unsigned long pressDuration = currentMillis - buttonPressTime;

    if (pressDuration < 5000) {
        // Зеленый светодиод загорается на короткое время
        rgbLed.green();
    } else if (pressDuration >= 5000 && pressDuration < 10000) {
        // Синий светодиод мигает три раза быстро
        rgbLed.off();
        for (int i = 0; i < 3; i++) {
            rgbLed.blue();
            delay(100);
            rgbLed.off();
            delay(100);
        }
    } else if (pressDuration >= 10000) {
        // Красный светодиод загорается на длительное время
        rgbLed.red();
    }
}

void ButtonHandler::handleShortPress() {
#ifdef DEBUG
    Serial.println("Handling short press: turning on green LED.");
#endif
    rgbLed.green(); // Зеленый светодиод загорается
    delay(50); // Ожидаем 1 секунду
    rgbLed.off();
#ifdef DEBUG
    Serial.println("Short press handled: green LED turned off.");
#endif
}

void ButtonHandler::handleMediumPress() {
#ifdef DEBUG
    Serial.println("Handling medium press: entering programming mode.");
#endif
    unsigned long startMillis = millis();
    unsigned long currentMillis = millis();

    // Мигание синим светодиодом каждую секунду в течение 30 секунд
    while (currentMillis - startMillis < 30000) { // 30 секунд
        rgbLed.blue();  // Включаем синий светодиод
        delay(500);     // Светодиод горит 0.5 секунды
        rgbLed.off();   // Выключаем светодиод
        delay(500);     // Светодиод выключен 0.5 секунды

        currentMillis = millis(); // Обновляем текущее время
    }

#ifdef DEBUG
    Serial.println("Exiting programming mode.");
#endif
    // Здесь можно вставить код для обработки сигналов приемника в будущем
}

void ButtonHandler::handleLongPress() {
#ifdef DEBUG
    Serial.println("Handling long press: clearing EEPROM and cycling through LEDs.");
#endif

    indicateStartOfClearing();
    eepromHandler.clearEEPROM();
    indicateClearingCompleted();

    resetDevice();
}

// Метод для индикации начала очистки
void ButtonHandler::indicateStartOfClearing() {
    rgbLed.red();
}

// Метод для индикации завершения очистки
void ButtonHandler::indicateClearingCompleted() {
    rgbLed.blue();
    delay(1000);
    rgbLed.white();
    delay(3000);
    rgbLed.off();
    delay(300);
}

void ButtonHandler::resetDevice() {
#ifdef DEBUG
    Serial.println("Resetting device.");
#endif
    wdt_enable(WDTO_15MS); // Включаем сторожевой таймер на 15 миллисекунд
    while (true);          // Ждем сброса
}
