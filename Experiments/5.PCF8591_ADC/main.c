#include <STC15F2K60S2.h>
#include <intrins.h>
#include <iic.h>

void cls_buzz(){
    P2 = (P2 & 0x1f) | 0xa0;
    P0 = 0xaf;
    P2 &= 0x1f;
}

unsigned char IIC_Read(unsigned char Slave, unsigned char Addr){
    unsigned char Data;
    IIC_Start();
    IIC_SendByte(Slave);
    IIC_WaitAck();
    IIC_SendByte(Addr);
    IIC_WaitAck();
    IIC_Start();
    IIC_SendByte(Slave+1);
    IIC_WaitAck();
    Data = IIC_RecByte();
    IIC_SendAck(0);
    IIC_Stop();
    return Data;
}

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char dspbuf[] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char dspcom = 0;

void display(){
    P2 = (P2 & 0x1f) | 0xc0;
    P0 = 0x00;
    P2 &= 0x1f;
    P2 = (P2 & 0x1f) | 0xc0;
    P0 = 1 << dspcom;
    P2 &= 0x1f;
    P2 = (P2 & 0x1f) | 0xe0;
    P0 = tab[dspbuf[dspcom]];
    P2 &= 0x1f;
    if(++dspcom==8)
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

unsigned char flag = 0;
void main(){
    unsigned char tmp;
    cls_buzz();
    Timer0Init();
    ET0 = 1;
    EA = 1;
    while (1)
    {
        if(flag){
            tmp = IIC_Read(0x90, 0x03);
            flag = 0;
        }
        dspbuf[7] = tmp % 10;
        dspbuf[6] = tmp % 100 / 10;
        dspbuf[5] = tmp / 100;
    }
}

void tr0_interrupt() interrupt 1
{
    display();
    flag = 1;
}
