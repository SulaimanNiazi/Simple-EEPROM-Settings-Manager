#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

void divideInto(uint16_t value, uint8_t *addressH, uint8_t *addressL);
void writeEEPROM(uint16_t address, uint16_t data);
uint16_t readEEPROM(uint16_t address);

#endif // EEPROM_H