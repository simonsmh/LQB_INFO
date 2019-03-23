#include <STC15F2K60S2.h>

void cls_buzz()
{
    P2 = (P2 & 0x1f) | 0xa0;
    P0 = 0xaf;
    P2 &= 0x1f;
}

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char dspbuf[] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char dspcom = 0;

void display()
{
    P2 = (P2 & 0x1f) | 0xc0;
    P0 = 0x00;
    P2 &= 0x1f;
    P2 = (P2 & 0x1f) | 0xc0;
    P0 = 1 << dspcom;
    P2 &= 0x1f;
    P2 = (P2 & 0x1f) | 0xe0;
    P0 = tab[dspbuf[dspcom]];
    P2 &= 0x1f;
    if (++dspcom == 8)
        dspcom = 0;
}

void buf(long int a, unsigned char b, unsigned char c)
{
    char i;
    for (i = c; i >= b; i--)
    {
        dspbuf[i] = a % 10;
        a /= 10;
    }
}

void Timer0Init(void) //2毫秒@11.0592MHz
{
    AUXR &= 0x7F; //定时器时钟12T模式
    TMOD &= 0xF0; //设置定时器模式
    TL0 = 0xCD;   //设置定时初值
    TH0 = 0xF8;   //设置定时初值
    TF0 = 0;      //清除TF0标志
    TR0 = 1;      //定时器0开始计时
}

unsigned int key_press;
unsigned char keyboard()
{
    char i, j;
    unsigned char column, row;
    unsigned long sum = 0;
    //column row 0bxxxx
    P3 = 0x0f;
    P42 = 0;
    P44 = 0;
    if (!P30 || !P31 || !P32 || !P33)
        key_press++;
    else
        key_press = 0;

    if (key_press == 3)
    {
        column = ~(P3 & 0x0f);
        P3 = 0xf0;
        P42 = 1;
        P44 = 1;
        row = ~((((((P44 * 2) | P42) * 2) | P35) * 2) | P34); //Affected with P4
        //scan
        for (i = 3; i >= 0; i--)
        {
            for (j = 3; j >= 0; j--)
            {
                if (((column >> i) & 1) && ((row >> j) & 1))
                {
                    sum = (i + 1) + 4 * (j);
                    break;
                }
            }
        }
    }
    return sum;
}

unsigned long int tmp;
void main()
{
    cls_buzz();
    Timer0Init();
    ET0 = 1;
    EA = 1;

    tmp = 0;
    while (1)
    {
        tmp += keyboard();
        buf(tmp, 0, 7);
    }
}

void tr0_interrupt() interrupt 1
{
    display();
}
