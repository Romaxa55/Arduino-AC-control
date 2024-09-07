// MelodyPlayer.h
#ifndef MELODY_PLAYER_H
#define MELODY_PLAYER_H

#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_G7 3136
#define NOTE_A7 3520
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_E8 5274

class MelodyPlayer {
private:
    int pin;
    int *melody;
    int *noteDurations;
    int melodyLength;

public:
    MelodyPlayer(int outputPin, int *melodyArray, int *durationsArray, int length)
            : pin(outputPin), melody(melodyArray), noteDurations(durationsArray), melodyLength(length) {
        pinMode(pin, OUTPUT);
    }

    void play() {
        for (int thisNote = 0; thisNote < melodyLength; thisNote++) {
            int noteDuration = 1000 / noteDurations[thisNote];
            digitalWrite(pin, HIGH);  // Включаем светодиод
            delay(noteDuration);
            digitalWrite(pin, LOW);   // Выключаем светодиод
            delay(noteDuration / 1.3);
        }
    }
};

#endif
