/*
 * File:   main.c
 * Author: SulaimanNiazi
 *
 * Created on February 26, 2025, 1:19 AM
 */

#define _XTAL_FREQ 20000000
#include <xc.h>
#include <stdbool.h>
#include "./src/eeprom.h"
#include "./src/settings.h"

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

uint16_t setValue(uint16_t oldValue, uint16_t maxValue){
    uint16_t value = oldValue;
    while(1){
        PORTD = value;
        switch(getInput()){
            case 0:
                return value; 
                break;
            case 1:
                if(value == maxValue){
                    value = 0;
                }
                else{
                    value++;
                }
                break;
            case 2:
                if(value == 0){
                    value = maxValue;
                }
                else{
                    value--;
                }
                break;
        }
    }
}

void main(){
    Setting mode, brightness, volume;
    initializeSetting(&mode, 0x0000);
    initializeSetting(&brightness, 0x0001);
    initializeSetting(&volume, 0x0002);
    bool writeError = false;
    TRISD = PORTD = 0x00;
    TRISC0 = TRISC1 = 0;
    while(1){
        RC0 = RC1 = 0;          //Mode 0: Normal
        if(getInput() == 0){
            RC0 = 1;            //Mode 1: Select setting to edit
            uint16_t choice = setValue(0,2);
            RC0 = 0;            //Mode 2: Select new value
            RC1 = 1;
            uint16_t newValue;
            Setting *selectedSetting;
            switch(choice){
                case 0:
                    selectedSetting = &mode;
                    break;
                case 1:
                    selectedSetting = &brightness;
                    break;
                case 2:
                    selectedSetting = &volume;
                    break;
            }
            newValue = setValue(readSetting(selectedSetting), 255);
            writeError = writeSetting(selectedSetting, newValue);
            PORTD = readSetting(selectedSetting);
        }
    }
    return;
}
