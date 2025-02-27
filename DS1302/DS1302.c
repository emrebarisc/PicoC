#include "DS1302.h"

#include <stdio.h>
#include <string.h>

#include "SSD1306.h"
#include "Font.h"

uint8_t DS1302_second = 0;
uint8_t DS1302_minute = 0;
uint8_t DS1302_hour = 0;
uint8_t DS1302_date = 0;
uint8_t DS1302_month = 0;
uint8_t DS1302_day = 0;
uint8_t DS1302_year = 0;

#define CE_HIGH() gpio_put(DS1302_CE_PIN, 1)
#define CE_LOW() gpio_put(DS1302_CE_PIN, 0)
#define CLK_HIGH() gpio_put(DS1302_CLK_PIN, 1)
#define CLK_LOW() gpio_put(DS1302_CLK_PIN, 0)
#define IO_HIGH() gpio_put(DS1302_IO_PIN, 1)
#define IO_LOW() gpio_put(DS1302_IO_PIN, 0)

void DS1302_WriteByte(uint8_t value)
{
    gpio_set_dir(DS1302_IO_PIN, GPIO_OUT);

    for (int i = 0; i < 8; i++)
    {
        CLK_LOW();
        if (value & 0x01)
        {
            IO_HIGH();
        }
        else
        {
            IO_LOW();
        }
        CLK_HIGH();
        value >>= 1;
        sleep_us(1);
    }
}

uint8_t DS1302_ReadByte()
{
    gpio_set_dir(DS1302_IO_PIN, GPIO_IN);

    uint8_t value = 0;
    for (int i = 0; i < 8; i++)
    {
        CLK_LOW();
        sleep_us(1);
        CLK_HIGH();
        if (gpio_get(DS1302_IO_PIN))
        {
            value |= (1 << i);
        }
    }
    return value;
}

void DS1302_WriteRegister(uint8_t reg, uint8_t value)
{
	CE_HIGH();
	sleep_us(1);
	DS1302_WriteByte(reg | 0b10000000);
	DS1302_WriteByte(value);
	CE_LOW();
	sleep_us(1);
}

uint8_t DS1302_ReadRegister(uint8_t reg)
{
    uint8_t value;
    CE_HIGH();
    DS1302_WriteByte(reg | 0b10000001);
    gpio_set_dir(DS1302_IO_PIN, GPIO_IN);
    value = DS1302_ReadByte();
    CE_LOW();
    return value;
}

uint8_t BCDToDec(uint8_t bcd)
{
    return ((bcd / 16) * 10) + (bcd % 16);
}

uint8_t DecToBCD(uint8_t dec)
{
    return ((dec / 10) * 16) + (dec % 10);
}

void DS1302_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    DS1302_WriteRegister(0x80, DecToBCD(seconds));
    DS1302_WriteRegister(0x82, DecToBCD(minutes));
    DS1302_WriteRegister(0x84, DecToBCD(hours));
    DS1302_WriteRegister(0x86, DecToBCD(date));
    DS1302_WriteRegister(0x88, DecToBCD(month));
    DS1302_WriteRegister(0x8C, DecToBCD(year));
    DS1302_WriteRegister(0x8A, DecToBCD(day));
}

void DS1302_GetTime()
{
    DS1302_second = BCDToDec(DS1302_ReadRegister(0x81) & 0x7F);
    DS1302_minute = BCDToDec(DS1302_ReadRegister(0x83));
    DS1302_hour = BCDToDec(DS1302_ReadRegister(0x85) & 0x3F);
    DS1302_date = BCDToDec(DS1302_ReadRegister(0x87));
    DS1302_month = BCDToDec(DS1302_ReadRegister(0x89));
    DS1302_year = BCDToDec(DS1302_ReadRegister(0x8D));
    DS1302_day = BCDToDec(DS1302_ReadRegister(0x8B) & 0x07);
}

void DS1302_PrintTime()
{
    static const char *days[] = 
	{
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
	};

    printf(sizeof(log), "%02d:%02d:%02d\n%02d/%02d/20%02d\n%s",
            DS1302_hour, DS1302_minute, DS1302_second, DS1302_date, DS1302_month, DS1302_year, days[DS1302_day]);
}

void DS1302_Init()
{
    gpio_init(DS1302_CE_PIN);
    gpio_init(DS1302_CLK_PIN);
    gpio_init(DS1302_IO_PIN);

    gpio_set_dir(DS1302_CE_PIN, GPIO_OUT);
    gpio_set_dir(DS1302_CLK_PIN, GPIO_OUT);
    gpio_set_dir(DS1302_IO_PIN, GPIO_OUT);

    CE_LOW();
    CLK_LOW();

	DS1302_WriteRegister(0x8E, 0x00);

    DS1302_GetTime();
}
