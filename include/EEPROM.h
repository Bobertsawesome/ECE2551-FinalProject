#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <avr/io.h>

class EEPROM{
    public:
    static uint8_t read(uint16_t addr){
        // Wait for previous write operation to complete
        while(EECR & (1 << EEPE));

        // Set EEPROM address registers (16-bit address)
        EEAR = addr;

        // Start EEPROM read by setting EERE bit
        EECR |= (1 << EERE);

        // Return data from EEPROM data register
        return EEDR;
    }

    static void write(uint16_t addr, uint8_t data){
        // Wait for previous write operation to complete
        while(EECR & (1 << EEPE));

        // Set EEPROM address registers (16-bit address)
        EEAR = addr;

        // Set data to be written in EEPROM data register
        EEDR = data;

        // Set master write enable bit (EEMPE)
        EECR |= (1 << EEMPE);

        // Start EEPROM write by setting EEPE bit (must be within 4 clock cycles of EEMPE)
        EECR |= (1 << EEPE);
    }
};

#endif