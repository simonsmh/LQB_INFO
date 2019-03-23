#include <STC15F2K60S2.h>
#include <ds1302.h>

void cls_buzz()
{
    P2 = (P2 & 0x1f) | 0xa0;
    P0 = 0xaf;
    P2 &= 0x1f;
}

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char dspbuf[] = {0, 0, 10, 0, 0, 10, 0, 0};
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

int time_data[7] = {50, 59, 23, 0, 0, 0, 0};

void init_rtc(){
    unsigned char i, temp = 0x80;
    Write_Ds1302_Byte(0x8e, 0x00);
    for (i = 0; i < 7;i++){
        Write_Ds1302_Byte(temp, time_data[i]  + (time_data[i] / 10 * 6));
        temp += 2;
    }
    Write_Ds1302_Byte(0x8e, 0x81);
}

void get_rtc(){
    unsigned char i, temp = 0x81;
    for (i = 0; i < 7; i++)
    {
        time_data[i] = Read_Ds1302_Byte(temp);
        time_data[i] = time_data[i] % 16 + (time_data[i] / 16 * 10);
        temp += 2;
    }
}

void main(){
    cls_buzz();
    Timer0Init();
    init_rtc();
    ET0 = 1;
    EA = 1;

    while(1);
}

void tr0_interrupt() interrupt 1
{
    display();
    get_rtc();
    buf(time_data[2], 0, 1);
    buf(time_data[1], 3, 4);
    buf(time_data[0], 6, 7);
}
