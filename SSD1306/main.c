#include "SSD1306.h"

int main(void)
{
	SSD1306_Init();
	SSD1306_DrawString(0, 0, "SSD1306 Test", 1);

	while(1)
	{

	}

	return 1;
}
