#include "DS1302.h"

int main(void)
{
	DS1302_Init();
	DS1302_SetTime(13, 15, 0, 1, 1, 25, 0);
	DS1302_GetTime();

	DS1302_PrintTime();

	while(1){}

	return 1;
}