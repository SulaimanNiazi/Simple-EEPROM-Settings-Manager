/*
 * File:   main.c
 * Author: SulaimanNiazi
 *
 * Created on February 26, 2025, 1:19 AM
 */

#define _XTAL_FREQ 20000000
#include <xc.h>
#include <stdbool.h>

void divideInto(uint16_t value, uint8_t *addressH, uint8_t *addressL){
    *addressH = (uint8_t)value>>8;
    *addressL = (uint8_t)(value & 0x00FF);
}
void writeEEPROM(uint16_t address, uint16_t data){
    divideInto(address, &EEADRH, &EEADR);
    divideInto(data, &EEDATH, &EEDATA);
    while(WR);      // waiting for previous write cycle to complete 
    EEPGD = 0;      //EEPGD bit is set to low to point to EEPROM 
    WREN = 1; 
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA; 
    WR = 1;         // starting write 
    GIE = 1;
    WREN = 0; 
    while(!EEIF);
    EEIF = 0;
}
uint16_t readEEPROM(uint16_t address){
    divideInto(address, &EEADRH, &EEADR);
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    return EEDATH | EEDATA;
}

struct setting{
    uint16_t data, address;
};

struct setting newSetting(uint16_t address){
    struct setting *config;
    config->address = address;
    config->data = readEEPROM(config->address);
    return *config;
}
bool setSetting(struct setting*config, uint16_t value){
    writeEEPROM(config->address, value);
    config->data = readEEPROM(config->address);
    return config->data==value;
}

uint16_t getInput(){
    while(1){
        if(RB0){            //change/select setting
            __delay_ms(10);
            if(RB0){
                while(RB0);
                return 0;
            }
        }
        if(RB1){            //increment
            __delay_ms(10);
            if(RB1){
                while(RB1);
                return 1;
            }
        }
        if(RB2){            //decrement
            __delay_ms(10);
            if(RB2){
                while(RB2);
                return 2;
            }
        }
    }
}

uint16_t setValue(){
    uint16_t value = 0;
    while(1){
        switch(getInput()){
            case 0:
                return value; 
                break;
            case 1:
                if(value==2){
                    value = 0;
                }
                else{
                    value++;
                }
                break;
            case 2:
                if(value == 0){
                    value = 2;
                }
                else{
                    value--;
                }
                break;
        }
    }
}

void main(){
    struct setting mode = newSetting(0x0000), brightness = newSetting(0x0001), volume = newSetting(0x0002);
    bool writeError = false;
    TRISB = 0xFF;
    while(1){
        if(getInput() == 0){
            uint16_t choice = setValue();
            uint16_t newValue = setValue();
            switch(choice){
                case 0:
                    writeError = setSetting(&mode, newValue);
                    break;
                case 1:
                    writeError = setSetting(&brightness, newValue);
                    break;
                case 2:
                    writeError = setSetting(&volume, newValue);
                    break;
            }
        }
    }
    return;
}
