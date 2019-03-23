#include <STC15F2K60S2.h>
#include <intrins.h>

void cls_buzz()
{
	P2 = (P2 &= 0x1f) | 0xa0;
	P0 &= 0xaf; //Disable P04 P06
	P2 &= 0x1f;
}

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char dspbuf[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char dspcom = 0;

void display()
{
	P2 = (P2 &= 0x1f) | 0xc0;
	P0 = 0x00;
	P2 &= 0x1f;
	P2 = (P2 &= 0x1f) | 0xe0;
	P0 = tab[dspbuf[dspcom]];
	P2 &= 0x1f;
	P2 = (P2 &= 0x1f) | 0xc0;
	P0 = (1 << dspcom);
	P2 &= 0x1f;
	if (++dspcom == 8)
		dspcom = 0;
}

unsigned int distant()
{
	unsigned int distance, t = 0;
	unsigned char i = 300; //发送8个脉冲
	TH1 = 0;
	TL1 = 0;
	do
	{
		P10 = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();
		P10 = 0;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();
	} while (i--);
	TR1 = 1; //启动计时
	while ((P11 == 1) && (TF1 == 0))
		;	//等待收到脉冲
	TR1 = 0; //关闭计时

	//发生溢出
	if (TF1 == 1)
	{
		TF1 = 0;
		distance = 999; //无返回
	}
	else
	{
		/**  计算时间  */
		t = TH1;
		t <<= 8;
		t |= TL1;
		distance = (unsigned int)(t * 0.017); //计算距离
	}
	return distance;
}

void Timer0Init(void) //2毫秒@11.0592MHz
{
	AUXR &= 0x7F; //定时器时钟12T模式
	TMOD &= 0xF0; //设置定时器模式
	TL0 = 0xCD;   //设置定时初值
	TH0 = 0xF8;   //设置定时初值
	TF0 = 0;	  //清除TF0标志
	TR0 = 1;	  //定时器0开始计时
}

unsigned int flag = 0;
void main()
{
	unsigned int tmp;
	cls_buzz();
	Timer0Init();
	ET0 = 1;
	EA = 1;
	while (1)
	{
		if (flag)
		{
			tmp = distant();
			flag = 0;
		}
		dspbuf[7] = tmp % 10;
		dspbuf[6] = tmp % 100 / 10;
		dspbuf[5] = tmp / 100;
	}
}

void tr0_interrupt() interrupt 1{
	display();
	flag = 1;
}
