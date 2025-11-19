#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include "LiquidCrystal.h"

// Button enumeration for LCD keypad shield
typedef enum {LEFT, RIGHT, UP, DOWN, SELECT, NONE} Button;

class LCD : public LiquidCrystal {
public:
    // Constructor: Initialize LCD with standard pin configuration
    // RS=8, Enable=9, D4=4, D5=5, D6=6, D7=7
    LCD() : LiquidCrystal(8, 9, 4, 5, 6, 7), BUTTON_PIN(A0), lastButtonTime_(0), DEBOUNCE_DELAY(50) {
        pinMode(BUTTON_PIN, INPUT);
    }

    // Read button press from analog pin with debouncing
    Button getButtonPress() {
        // Read analog value from button voltage divider
        int analogValue = analogRead(BUTTON_PIN);

        // Get current time for debounce checking
        unsigned long currentTime = millis();

        // Check if enough time has passed since last button read (debounce)
        if (currentTime - lastButtonTime_ < DEBOUNCE_DELAY) {
            return NONE; // Still in debounce period
        }

        // Map analog value to button based on voltage divider ranges
        Button pressed = NONE;
        if (analogValue < 50) {
            pressed = RIGHT;  // ~0V
        } else if (analogValue < 250) {
            pressed = UP;     // ~0.71V
        } else if (analogValue < 450) {
            pressed = DOWN;   // ~1.61V
        } else if (analogValue < 650) {
            pressed = LEFT;   // ~2.47V
        } else if (analogValue < 900) {
            pressed = SELECT; // ~3.62V
        } else {
            pressed = NONE;   // ~5V (no button pressed)
        }

        // Update last button time if a button was actually pressed
        if (pressed != NONE) {
            lastButtonTime_ = currentTime;
        }

        return pressed;
    }

private:
    const int BUTTON_PIN;           // Analog pin for button reading (A0)
    unsigned long lastButtonTime_;  // Last time a button was detected
    const unsigned long DEBOUNCE_DELAY; // Debounce delay in milliseconds
};

#endif
