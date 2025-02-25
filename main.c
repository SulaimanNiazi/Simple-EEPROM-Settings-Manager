/*
 * File:   main.c
 * Author: SulaimanNiazi
 *
 * Created on February 26, 2025, 1:19 AM
 */

#define _XTAL__FREQ 20000000
#include <xc.h>

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

void main(){
    TRISB0 = 0;
    RB0 = 0;
    writeEEPROM(0x0000,0xFFFF);
    uint16_t letter = readEEPROM(0x0000);
    RB0 = letter == 0xFFFF;
    writeEEPROM(0x0002, letter);
    while(1){
        
    }
    return;
}
