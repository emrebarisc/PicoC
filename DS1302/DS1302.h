#ifndef __DS1302_H__
#define __DS1302_H__

#include "pico/stdlib.h"

#define DS1302_CE_PIN   11
#define DS1302_IO_PIN   12
#define DS1302_CLK_PIN  13

void DS1302_WriteByte(uint8_t value);
uint8_t DS1302_ReadByte();
void DS1302_WriteRegister(uint8_t reg, uint8_t value);
uint8_t DS1302_ReadRegister(uint8_t reg);
uint8_t BCDToDec(uint8_t bcd);
uint8_t DecToBCD(uint8_t dec);
void DS1302_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t date, uint8_t month, uint8_t year, uint8_t day);
void DS1302_GetTime();
void DS1302_Init();
void DS1302_PrintTime();

extern uint8_t DS1302_second;
extern uint8_t DS1302_minute;
extern uint8_t DS1302_hour;
extern uint8_t DS1302_date;
extern uint8_t DS1302_month;
extern uint8_t DS1302_day;
extern uint8_t DS1302_year;

#endif