#include "DS3231.h"

#include <stdio.h>
#include <string.h>

#include "SSD1306.h"
#include "Font.h"

int DS3231_second = 0;
int DS3231_minute = 0;
int DS3231_hour = 0;
int DS3231_day = 0;
int DS3231_date = 0;
int DS3231_month = 0;
int DS3231_year = 0;

uint8_t BCDToDEC(uint8_t val)
{
    return (val / 16 * 10) + (val % 16);
}

uint8_t DECToBCD(uint8_t val)
{
    return (val / 10 * 16) + (val % 10);
}

void DS3231_Init()
{
    i2c_init(DS3231_I2C, 100 * 1000);
    gpio_set_function(DS3231_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DS3231_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(DS3231_SDA);
    gpio_pull_up(DS3231_SCL);

    DS3231_GetTime();
}

void DS3231_SetTime(uint8_t hour, uint8_t min, uint8_t sec, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    uint8_t buf[8];
    buf[0] = 0x00;
    buf[1] = DECToBCD(sec);
    buf[2] = DECToBCD(min);
    buf[3] = DECToBCD(hour);
    buf[4] = DECToBCD(day);
    buf[5] = DECToBCD(date);
    buf[6] = DECToBCD(month);
    buf[7] = DECToBCD(year);
    i2c_write_blocking(DS3231_I2C, DS3231_ADDRESS, buf, 8, false);
}

void DS3231_GetTime()
{
    uint8_t reg = 0x00;
    uint8_t buf[7];
    i2c_write_blocking(DS3231_I2C, DS3231_ADDRESS, &reg, 1, true);
    i2c_read_blocking(DS3231_I2C, DS3231_ADDRESS, buf, 7, false);
    
    DS3231_second = BCDToDEC(buf[0] & 0x7F);
    DS3231_minute = BCDToDEC(buf[1]);
    DS3231_hour = BCDToDEC(buf[2] & 0x3F);
    DS3231_day = BCDToDEC(buf[3]);
    DS3231_date = BCDToDEC(buf[4]);
    DS3231_month = BCDToDEC(buf[5] & 0x1F);
    DS3231_year = BCDToDEC(buf[6]);
}

void DS3231_PrintTime()
{
    static const char *days[] = 
	{
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
	};

    printf(sizeof(log), "%02d:%02d:%02d\n%02d/%02d/20%02d\n%s",
            DS3231_hour, DS3231_minute, DS3231_second, DS3231_date, DS3231_month, DS3231_year, days[DS3231_day]);
}