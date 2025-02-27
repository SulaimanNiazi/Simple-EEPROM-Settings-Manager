#include "settings.h"
#include "eeprom.h"
#include <stdbool.h>

Setting userSettings;

void initializeSetting(Setting*config, uint16_t address) {
    config->address = address;
    config->data = readEEPROM(address);
}

uint16_t readSetting(Setting *config) {
    return config->data;
}

bool writeSetting(Setting *config, uint16_t data) {
    writeEEPROM(config->address, data);
    config->data = readEEPROM(config->address);
    return config->data == data;
}
