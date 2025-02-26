#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t address;
    uint16_t data;
} Setting;

bool writeSetting(Setting*, uint16_t);
uint16_t readSetting(Setting*);
void initializeSetting(Setting*,uint16_t);

#endif // SETTINGS_H