#include <STC15F2K60S2.h>

void cls_buzz(){
    P2 = (P2 & 0x1f) | 0xa0;
    P0 = 0xaf;
    P2 &= 0x1f;
}

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char dspbuf[] = {1, 2, 3, 4, 5, 6, 7, 8};
unsigned char dspcom = 0;

void display(){
    //消隐
    P2 = (P2 & 0x1f) | 0xc0;
    P0 = 0x00;
    P2 &= 0x1f;
    //位选
    P2 = (P2 & 0x1f) | 0xe0;
    P0 = tab[dspcom[dspbuf]];
    P2 &= 0x1f;
    //段选
    P2 = (P2 & 0x1f) | 0xc0;
    P0 = 1 << dspcom;
    P2 &= 0x1f;
    if (++dspcom == 8)
        dspcom = 0;
}

void Timer0Init(void) //2毫秒@11.0592MHz
{
    AUXR |= 0x80; //定时器时钟1T模式
    TMOD &= 0xF0; //设置定时器模式
    TL0 = 0x9A;   //设置定时初值
    TH0 = 0xA9;   //设置定时初值
    TF0 = 0;      //清除TF0标志
    TR0 = 1;      //定时器0开始计时
}

void main(){
    cls_buzz();
    ET0 = 1;
    EA = 1;
    Timer0Init();
    while(1);
}

void tr0_interrupt() interrupt 1
{
    display();
}
