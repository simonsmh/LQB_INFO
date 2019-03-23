#include "STC15F2K60S2.h"
#include "self.h"

unsigned char temperature_flag = 0;
float temperature = 0;
int time_data[] = {50, 59, 23, 0, 0, 0, 0};
int current_data[] = {0, 0, 0, 0, 0, 0, 0};
int alarm_data[] = {0, 0, 0, 0, 0, 0, 0};
unsigned char dspbuf[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void Timer0Init(void) //2000微秒@11.0592MHz
{
	AUXR |= 0x80; //定时器时钟1T模式
	TMOD &= 0xF0; //设置定时器模式
	TL0 = 0x9A;   //设置定时初值
	TH0 = 0xA9;   //设置定时初值
	TF0 = 0;	  //清除TF0标志
	TR0 = 1;	  //定时器0开始计时
}

void buf(unsigned long t, char a, char b)
{
	char i;
	for (i = b; i >= a; i--)
	{
		dspbuf[i] = t % 10;
		t /= 10;
	}
	// for (i = a; i <= b; i++)
	// {
	// 	if (dspbuf[i] == 0)
	// 		dspbuf[i] = 10;
	// 	else
	// 		break;
	// }
}
unsigned int counter = 0;
char status_1 = 0;
char status_2 = 0;
char current = 0;
char i;
void main(void)
{
	cls_buzz();
	init_rtc();
	Timer0Init();
	//Timer1Init();
	EA = 1;
	ET0 = 1;
	//ET1 = 1;

	while (1)
	{
		//Temp
		if (temperature_flag)
		{
			temperature_flag = 0;
			//TR0 = 0;
			temperature = Get_Temp();
			//TR0 = 1;
		}

		//Time
		get_rtc();

		if (status_2 == 0)
		{
			current = 0;
			//Default
			dspbuf[2] = 11;
			dspbuf[5] = 11;
			if (status_1 == 0)
			{
				buf(time_data[2], 0, 1);
				buf(time_data[1], 3, 4);
				buf(time_data[0], 6, 7);
			}else{
				if (status_1 == 1)
				{
					current = 3;
					if (++counter >= 500)
					{
						dspbuf[0] = 10;
						dspbuf[1] = 10;
						if (counter >= 1000)
							counter = 0;
					}
					else
					{
						buf(current_data[2], 0, 1);
					}
					buf(current_data[1], 3, 4);
					buf(current_data[0], 6, 7);
			}
			else if (status_1 == 2)
			{
				current = 2;
				if (++counter >= 500)
				{
					dspbuf[3] = 10;
					dspbuf[4] = 10;
					if (counter >= 1000)
						counter = 0;
				}
				else
				{
					buf(current_data[1], 3, 4);
				}
				buf(current_data[2], 0, 1);
				buf(current_data[0], 6, 7);
			}
			else if (status_1 == 3)
			{
				current = 1;
				if (++counter >= 500)
				{
					dspbuf[6] = 10;
					dspbuf[7] = 10;
					if (counter >= 1000)
						counter = 0;
				}
				else
				{
					buf(current_data[0], 6, 7);
				}
				buf(current_data[2], 0, 1);
				buf(current_data[1], 3, 4);
			}
			}
		}
		else
		{
			dspbuf[2] = 11;
			dspbuf[5] = 11;
			if (status_2 == 1)
			{
				current = 3;
				if (++counter >= 500)
				{
					dspbuf[0] = 10;
					dspbuf[1] = 10;
					if (counter >= 1000)
						counter = 0;
				}
				else
				{
					buf(alarm_data[2], 0, 1);
				}
				buf(alarm_data[1], 3, 4);
				buf(alarm_data[0], 6, 7);
			}
			else if (status_2 == 2)
			{
				current = 2;
				if (++counter >= 500)
				{
					dspbuf[3] = 10;
					dspbuf[4] = 10;
					if (counter >= 1000)
						counter = 0;
				}
				else
				{
					buf(alarm_data[1], 3, 4);
				}
				buf(alarm_data[2], 0, 1);
				buf(alarm_data[0], 6, 7);
			}
			else if (status_2 == 3)
			{
				current = 1;
				if (++counter >= 500)
				{
					dspbuf[6] = 10;
					dspbuf[7] = 10;
					if (counter >= 1000)
						counter = 0;
				}
				else
				{
					buf(alarm_data[0], 6, 7);
				}
				buf(alarm_data[2], 0, 1);
				buf(alarm_data[1], 3, 4);
			}
		}

		switch (read_btn())
		{
		case 1:
			if (++status_1 == 1)
			{
				for (i = 0; i <= 6; i++)
					current_data[i] = time_data[i];
			}
			else if (status_1 == 4)
			{
				status_1 = 0;
				for (i = 0; i <= 6; i++)
				{
					time_data[i] = current_data[i];
				}
				init_rtc();
			}
			//buf(1, 0, 0);
			break;
		case 2:
			if (++status_2 == 4)
				status_2 = 0;
			//buf(2, 0, 0);
			break;
		case 3:
			switch (status_1)
			{
				case 3:
					if (++current_data[current - 1] >= 60)
					{
						if (++current_data[current] >= 60)
						{
							if (++current_data[current + 1] >= 24)
							{
								current_data[current + 2]++;
								current_data[current + 1] = 0;
							}
							current_data[current] = 0;
						}
						current_data[current - 1] = 0;
					}
					break;

				case 2:
					if (++current_data[current - 1] >= 60)
					{
						if (++current_data[current] >= 24)
						{
								current_data[current + 1]++;
								current_data[current] = 0;
						}
						current_data[current - 1] = 0;
					}
					break;

				case 1:
					if (++current_data[current - 1] >= 24)
					{
						current_data[current]++;
						current_data[current - 1] = 0;
					}
					break;

				default:
					break;
			}

			switch (status_2)
			{
			case 3:
				if (++alarm_data[current - 1] >= 60)
				{
					if (++alarm_data[current] >= 60)
					{
						if (++alarm_data[current + 1] >= 24)
						{
							alarm_data[current + 2]++;
							alarm_data[current + 1] = 0;
						}
						alarm_data[current] = 0;
					}
					alarm_data[current - 1] = 0;
				}
				break;

			case 2:
				if (++alarm_data[current - 1] >= 60)
				{
					if (++alarm_data[current] >= 24)
					{
						alarm_data[current + 1]++;
						alarm_data[current] = 0;
					}
					alarm_data[current - 1] = 0;
				}
				break;

			case 1:
				if (++alarm_data[current - 1] >= 24)
				{
					alarm_data[current]++;
					alarm_data[current - 1] = 0;
				}
				break;

			default:
				break;
			}

			//buf(3, 0, 0);
			break;
		case 4:
			switch (status_1)
			{
			case 3:
				if (--current_data[current - 1] < 0)
				{
					if (--current_data[current] < 0)
					{
						if (--current_data[current + 1] < 0)
						{
							current_data[current+2]--;
							current_data[current + 1] = 23;
						}
						current_data[current] = 59;
					}
					current_data[current - 1] = 59;
				}
				break;

			case 2:
				if (--current_data[current-1] < 0)
				{
					if (--current_data[current] < 0)
					{
						current_data[current+1]--;
						current_data[current] = 23;
					}
					current_data[current-1] = 59;
				}
				break;

			case 1:
				if (--current_data[current - 1] < 0)
				{
					current_data[current]--;
					current_data[current-1] = 23;
				}
				break;

			default:
				break;
			}

			switch (status_2)
			{
			case 1:
				if (++alarm_data[current - 1] >= 60)
				{
					if (++alarm_data[current] >= 60)
					{
						if (++alarm_data[current + 1] >= 24)
						{
							alarm_data[current + 2]++;
							alarm_data[current + 1] = 0;
						}
						alarm_data[current] = 0;
					}
					alarm_data[current - 1] = 0;
				}
				break;

			case 2:
				if (++alarm_data[current - 1] >= 60)
				{
					if (++alarm_data[current] >= 24)
					{
						alarm_data[current + 1]++;
						alarm_data[current] = 0;
					}
					alarm_data[current - 1] = 0;
				}
				break;

			case 3:
				if (++alarm_data[current - 1] >= 24)
				{
					alarm_data[current]++;
					alarm_data[current - 1] = 0;
				}
				break;

			default:
				break;
			}

			if ((!status_1) && (!status_2)){
				while (read_btn_long() == 4)
				{
					buf(0, 0, 4);
					buf((unsigned long int)(temperature), 5, 6);
					dspbuf[7] = 12;
				}
			}
			//buf(4, 0, 0);
			break;
		default:
			//buf(0, 0, 0);
			break;
		}
	};
}

unsigned int o = 0, p = 0, q = 0, r = 0;
void isr_timer_0(void) interrupt 1 //默认中断优先级 1
{
	display();

	if (++r >= 80)
	{
		temperature_flag = 1;
		r = 0;
	}
}
