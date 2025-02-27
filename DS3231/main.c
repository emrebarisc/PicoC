#include "DS3231.h"

int main(void)
{
	DS3231_Init();
	DS3231_SetTime(13, 15, 0, 1, 1, 25, 0);
	DS3231_GetTime();

	DS3231_PrintTime();

	while(1){}

	return 1;
}