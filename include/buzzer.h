#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
    public:
    explicit Buzzer(int buzzerpin) : BUZZER_PIN(buzzerpin) {
        pinMode(BUZZER_PIN, OUTPUT);
    }

    void bscroll(){
        // Play scroll sound at 988 Hz for 100 ms
        tone(BUZZER_PIN, 988, 100);
    }

    void bback (){
        // Play back sound at 740 Hz for 200 ms
        tone(BUZZER_PIN, 740, 200);
    }

    void bdot(){
        // Play Morse code dot at 830 Hz for 60 ms
        tone(BUZZER_PIN, 830, 60);
    }

    void bdash(){
        // Play Morse code dash at 830 Hz for 180 ms
        tone(BUZZER_PIN, 830, 180);
    }

    void bselect(){
        // Play select sound at 1244 Hz for 200 ms
        tone(BUZZER_PIN, 1244, 200);
    }
    private:
    const int BUZZER_PIN;
};



#endif // BUZZER_H