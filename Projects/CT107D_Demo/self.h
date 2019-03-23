#ifndef _SELF_H
#define _SELF_H

#include <STC15F2K60S2.H>

extern unsigned int time_data[];
extern unsigned char dspbuf[];

void cls_buzz();

float Get_Temp();
void init_rtc();
void get_rtc();
void Delay50us();
void EEPROM_Write(unsigned char addr, unsigned char dat);
unsigned char EEPROM_Read(unsigned char addr);
void display();
int read_keyboard();
int read_btn();
int read_btn_long();

#endif
