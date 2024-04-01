#include <reg51.h>

sbit BEEP=P2^5;

void delay(int mills) {
  int i, j;
	for (i = 0; i < mills; i++)
	{
	  for (j = 0; j < 120; j++);
	}
}

void delay_10us(unsigned int ten_us)
{
  while(ten_us--);
}

void main()
{
	unsigned int i = 150;
	unsigned int j = 200;
	unsigned int delay = j;
	float time = i / (float)delay;
	int flag = 0;
	int count = 0;
	while(1)
	{
	  while (i--)
		{
			BEEP = !BEEP;
			delay_10us(delay);
		}
		if (flag) {
			switch(delay)
			{
				case 250: delay = 200; break;
				case 200: delay = 150; break;
				case 150: delay = 110; break;
				case 110: delay = 250; count++; break;
			}
		}
		else {
			switch(delay)
			{
				case 200: delay = 150; break;
				case 150: delay = 100; break;
				case 100: delay = 60; break;
				case 60: delay = 200; count++; break;
			}
		}
		if (count >= 4) {
			count = 0;
			flag = !flag;
			delay = flag ? 250 : 200;
		}
		i = (unsigned int)(j * j / (float)delay * time);
		BEEP = 0;
	}
}