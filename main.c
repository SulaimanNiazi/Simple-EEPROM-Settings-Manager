/*
 * File:   main.c
 * Author: SulaimanNiazi
 *
 * Created on February 26, 2025, 1:19 AM
 */

#define displayPort             PORTD
#define displayPortDIR          TRISD
#define change_select_pin       PORTBbits.RB0
#define change_select_pinDIR    TRISBbits.TRISB0
#define increment_pin           PORTBbits.RB1
#define increment_pinDIR        TRISBbits.TRISB1
#define decrement_pin           PORTBbits.RB2
#define decrement_pinDIR        TRISBbits.TRISB2
#define indicator_pin1          PORTCbits.RC0
#define indicator_pin1DIR       TRISCbits.TRISC0
#define indicator_pin2          PORTCbits.RC1
#define indicator_pin2DIR       TRISCbits.TRISC1

#define _XTAL_FREQ 20000000
#include <xc.h>
#include <stdbool.h>
#include "./src/eeprom.h"
#include "./src/settings.h"

uint16_t getInput(){
    while(1){
        if(change_select_pin){            //change/select setting
            __delay_ms(10);
            if(change_select_pin){
                while(change_select_pin);
                return 0;
            }
        }
        if(increment_pin){            //increment
            __delay_ms(10);
            if(increment_pin){
                while(increment_pin);
                return 1;
            }
        }
        if(decrement_pin){            //decrement
            __delay_ms(10);
            if(decrement_pin){
                while(decrement_pin);
                return 2;
            }
        }
    }
}

uint16_t setValue(uint16_t oldValue, uint16_t maxValue){
    uint16_t value = oldValue;
    while(1){
        displayPort = value;
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
    initializeSetting(&mode, 0x0001);
    initializeSetting(&brightness, 0x0003);
    initializeSetting(&volume, 0x0005);
    bool writeError = false;
    displayPortDIR = 0x00;
    indicator_pin1DIR = indicator_pin2DIR = 0;
    change_select_pinDIR = increment_pinDIR = decrement_pinDIR = 1;
    while(1){
        displayPort = 0x00;
        indicator_pin1 = indicator_pin2 = 0;          //Mode 0: Normal
        if(getInput() == 0){
            indicator_pin1 = 1;            //Mode 1: Select setting to edit
            uint16_t choice = setValue(0,2);
            indicator_pin1 = 0;            //Mode 2: Select new value
            indicator_pin2 = 1;
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
            newValue = setValue(selectedSetting->data, 255);
            writeError = writeSetting(selectedSetting, newValue);
            displayPort = readSetting(selectedSetting);
        }
    }
    return;
}
