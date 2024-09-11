#include <Arduino.h>

// Определения пинов для приема и отправки ИК сигналов
#define IR_RECEIVE_PIN 8  // Пин 8 для приема ИК
#define IR_SEND_PIN    3  // Пин 3 для отправки ИК

// Определения буфера и корректировок времени
#if !defined(RAW_BUFFER_LENGTH)
#  if !((defined(RAMEND) && RAMEND <= 0x4FF) || (defined(RAMSIZE) && RAMSIZE < 0x4FF))
#define RAW_BUFFER_LENGTH 730  // Используем 16-битный буфер, если RECORD_GAP_MICROS > 20000
#  else
#define RAW_BUFFER_LENGTH 200  // Используем более короткий буфер по умолчанию
#  endif
#endif

#define MARK_EXCESS_MICROS 20  // Корректировка временного интервала для обработки ИК сигналов

/*
 * Вспомогательный макрос для получения определения макроса в виде строки
 */
#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif
