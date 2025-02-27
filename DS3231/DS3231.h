#ifndef __DS3231_H__
#define __DS3231_H__

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define DS3231_ADDRESS 0x68
#define DS3231_I2C i2c1
#define DS3231_SDA 18
#define DS3231_SCL 19

void DS3231_Init();
void DS3231_SetTime(uint8_t hour, uint8_t min, uint8_t sec, uint8_t date, uint8_t month, uint8_t year, uint8_t day);
void DS3231_GetTime();
void DS3231_PrintTime();

extern int DS3231_second;
extern int DS3231_minute;
extern int DS3231_hour;
extern int DS3231_day;
extern int DS3231_date;
extern int DS3231_month;
extern int DS3231_year;

#endif