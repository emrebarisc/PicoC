#include "SSD1306.h"

int main(void)
{
	SSD1306_Init();
	SSD1306_WriteString(0, 0, "SSD1306 Test");

	return 1;
}