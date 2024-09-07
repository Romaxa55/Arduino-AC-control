#include "MelodyPlayer.h"  // Подключаем файл класса

// Задаем мелодию и длительности нот
int melody[] = {
    NOTE_E7, NOTE_E7, 0, NOTE_E7,
    0, NOTE_C8, NOTE_E7, 0,
    NOTE_G7, 0, 0, 0,
    NOTE_G7, 0, 0, 0,
    NOTE_A7, 0, NOTE_A7, 0,
    NOTE_G7, NOTE_F7, NOTE_F7, NOTE_F7, NOTE_F7,
};

int noteDurations[] = {
    4, 4, 8, 4, 8, 4, 8, 4, 8, 4, 8, 8, 8, 4, 8, 4, 8, 8, 4, 8, 4, 8, 4, 8
};

MelodyPlayer player(LED_BUILTIN, melody, noteDurations, sizeof(melody) / sizeof(melody[0]));

void setup() {
    // Пусто, так как все уже инициализировано в классе
}

void loop() {
    player.play();
    delay(1000);  // Задержка перед повторным воспроизведением
}
