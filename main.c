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

uint16_t setValue(){
    uint16_t value = 0;
    while(1){
        PORTD = value;
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
    Setting mode, brightness, volume;
    initializeSetting(&mode, 0x0000);
    initializeSetting(&brightness, 0x0001);
    initializeSetting(&volume, 0x0002);
    bool writeError = false;
    TRISD = PORTD = 0x00;
    TRISC0 = TRISC1 = 0;
    while(1){
        RC0 = RC1 = 0;
        if(getInput() == 0){
            RC0 = 1;
            uint16_t choice = setValue();
            RC0 = 0;
            RC1 = 1;
            uint16_t newValue = setValue();
            switch(choice){
                case 0:
                    writeError = writeSetting(&mode, newValue);
                    PORTD = readSetting(&mode);
                    break;
                case 1:
                    writeError = writeSetting(&brightness, newValue);
                    PORTD = readSetting(&brightness);
                    break;
                case 2:
                    writeError = writeSetting(&volume, newValue);
                    PORTD = readSetting(&volume);
                    break;
            }
        }
    }
    return;
}
