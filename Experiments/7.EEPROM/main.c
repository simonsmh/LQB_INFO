#include <STC15F2K60S2.h>
#include <intrins.h>
#include <iic.h>

void cls_buzz()
{
    P2 = (P2 & 0x1f) | 0xa0;
    P0 = 0xaf;
    P2 &= 0x1f;
}

void Delay10us() //@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 25;
    while (--i)
        ;
}

void IIC_Write(unsigned char Slave, unsigned char Addr, unsigned char Data){
    EA = 0;
    IIC_Start();
    IIC_SendByte(Slave);
    IIC_WaitAck();
    IIC_SendByte(Addr);
    IIC_WaitAck();
    IIC_SendByte(Data);
    IIC_WaitAck();
    Delay10us();
    IIC_Stop();
    EA = 1;
}

unsigned char IIC_Read(unsigned char Slave, unsigned char Addr){
    unsigned char Data;
    EA = 0;
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
    EA = 1;
	  return Data;
}

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char dspbuf[] = {0,0,0,0,0,0,0,0};
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

void main(){
    unsigned char tmp;
    cls_buzz();
    Timer0Init();
    ET0 = 1;
    EA = 1;
    tmp = IIC_Read(0xa0,0x00);
    dspbuf[7] = tmp % 10;
    dspbuf[6] = tmp % 100 / 10;
    dspbuf[5] = tmp / 100;
    IIC_Write(0xa0, 0x00, ++tmp);
    while(1);
}

void tr0_interrupt() interrupt 1
{
    display();
}
