#include <STC15F2K60S2.h>
#include <onewire.h>

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

double rd_temperature(void)
{
    unsigned char low, high;
    double temp;
    // Toggle Temperature Celsis Switch
    init_ds18b20();
    Write_DS18B20(0xcc);
    Write_DS18B20(0x44);
    // Wait Timing >= 15us
    Delay_OneWire(20);
    // Toggle Read Scratchpad
    init_ds18b20();
    Write_DS18B20(0xcc);
    Write_DS18B20(0xbe);
    // Get Low and High level of num
    low = Read_DS18B20();
    high = Read_DS18B20();
    // Deal with the num
    temp = (high << 8) | low;
    temp /= 16;
    return temp;
}

void buf(long int a, unsigned char b, unsigned char c){
    char i;
    for (i = c; i >= b;i--){
        dspbuf[i] = a % 10;
        a /= 10;
    }
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

unsigned char flag = 0;
double tmp;
void main(){
    cls_buzz();
    Timer0Init();
    ET0 = 1;
    EA = 1;
    while(1){
        if(flag)
        {
            tmp = rd_temperature();
            buf(tmp*1000, 2, 7);
            flag = 0;
        }
    };
}

void tr0_interrupt() interrupt 1
{
    display();
    flag = 1;
}
